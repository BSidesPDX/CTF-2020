package main

import (
	"crypto/x509"
	"encoding/json"
	"encoding/pem"
	"fmt"
	"log"
	"net"
	"net/http"
	"os"
	"time"

	"github.com/gorilla/mux"
	"github.com/spacemonkeygo/httpsig"
)

var (
	err    error
	config = LoadConfiguration("config.json")
)

type tcpKeepAliveListener struct {
	*net.TCPListener
}

var keystore = httpsig.NewMemoryKeyStore()
var flag = [5]string{"BSidesPDX", "{HTTP_CAVAG3_", "S1GnaTur3s_Ar", "3_R3a11y_", "c001}"}

func adminkeyload() {

	adminkeydecode, _ := pem.Decode([]byte(sigpubkeyadmin))
	if adminkeydecode == nil || adminkeydecode.Type != "PUBLIC KEY" {
		log.Panicf("failed to decode PEM block containing private key")
	}
	pub, err := x509.ParsePKIXPublicKey(adminkeydecode.Bytes)
	if err != nil {
		log.Fatal(err)
	}
	kid := "admin"
	keystore.SetKey(kid, pub)

}

type Key struct {
	KID    string `json:"kid"`
	Pubkey string `json:"rsapub"`
}
type Config struct {
	Host string `json:"host"`
	Port string `json:"port"`
	IP   string `json:"ip"`
}

// Locading the configfile
func LoadConfiguration(file string) Config {
	var config Config
	configFile, err := os.Open(file)
	defer configFile.Close()
	if err != nil {
		fmt.Println(err.Error())
	}
	jsonParser := json.NewDecoder(configFile)
	jsonParser.Decode(&config)
	return config
}

//For submitting new keys to the keystore
func newKey(w http.ResponseWriter, r *http.Request) {
	if r.Method != "POST" {
		w.WriteHeader(http.StatusMethodNotAllowed)
		w.Write([]byte("Only POST requests allowed"))
	}

	var keyreq Key
	jsonParser := json.NewDecoder(r.Body)
	err = jsonParser.Decode(&keyreq)
	if err != nil {
		w.WriteHeader(http.StatusBadRequest)
		w.Write([]byte("Error decoding json"))
		return
	}

	pubkeydecode, _ := pem.Decode([]byte(keyreq.Pubkey))
	if pubkeydecode == nil || pubkeydecode.Type != "PUBLIC KEY" {
		log.Panicf("failed to decode PEM block containing private key")
		w.WriteHeader(http.StatusBadRequest)
		w.Write([]byte("Could not parse Public Key"))
		return
	}

	pub, err := x509.ParsePKIXPublicKey(pubkeydecode.Bytes)
	if err != nil {
		log.Fatal(err)
	}
	if keyreq.KID == "admin" {
		w.WriteHeader(http.StatusBadRequest)
		w.Write([]byte("Invalid KID"))
		return
	}

	keystore.SetKey(keyreq.KID, pub)

	fmt.Fprintf(w, "\nKey Loaded\n")
	fmt.Fprintf(w, "\nOther Endpoints you have access to are the following\n\n /hello\n/logs\n/ascii\n ")

	return
}

func handleRequests() {
	//load tls certs from tls_common

	router := mux.NewRouter().StrictSlash(true)

	//Server is loading config and hosting on provided config values.
	server := http.Server{
		Addr:    config.Host + ":" + config.Port,
		Handler: router,
	}
	router.HandleFunc("/", handleIndex)
	router.HandleFunc("/addkey", newKey).Methods("POST")
	router.HandleFunc("/hello", requestLogger(checkSecurity(hello)))
	router.HandleFunc("/logs", checkSecurity(logreader))
	router.HandleFunc("/flagp1", requestLogger(checkAdmin(flagp1)))
	router.HandleFunc("/flagp2", requestLogger(checkAdmin(flagp2)))
	router.HandleFunc("/flagp3", requestLogger(checkAdmin(flagp3)))
	router.HandleFunc("/flagp4", requestLogger(checkAdmin(flagp4)))
	router.HandleFunc("/flagp5", requestLogger(checkAdmin(flagp5)))
	router.HandleFunc("/ascii", requestLogger(checkSecurity(ascii)))

	fmt.Println("Starting server https://" + config.Host + ":" + config.Port)

	adminkeyload()
	log.Panic(server.ListenAndServe())

}

func handleIndex(w http.ResponseWriter, r *http.Request) {
	http.ServeFile(w, r, "index.html")
}
func flagp1(w http.ResponseWriter, r *http.Request) {
	w.WriteHeader(http.StatusAccepted)
	fmt.Fprint(w, flag[0])
	return
}
func flagp2(w http.ResponseWriter, r *http.Request) {
	w.WriteHeader(http.StatusAccepted)
	fmt.Fprint(w, flag[1])
	return
}
func flagp3(w http.ResponseWriter, r *http.Request) {
	w.WriteHeader(http.StatusAccepted)
	fmt.Fprint(w, flag[2])
	return
}
func flagp4(w http.ResponseWriter, r *http.Request) {
	w.WriteHeader(http.StatusAccepted)
	fmt.Fprint(w, flag[3])
	return
}
func flagp5(w http.ResponseWriter, r *http.Request) {
	w.WriteHeader(http.StatusAccepted)
	fmt.Fprint(w, flag[4])
	return
}
func ascii(w http.ResponseWriter, r *http.Request) {
	w.WriteHeader(http.StatusAccepted)
	w.Write([]byte(Asciibender))

}
func isJSON(str string) bool {
	var js json.RawMessage
	return json.Unmarshal([]byte(str), &js) == nil
}

func hello(w http.ResponseWriter, r *http.Request) {
	w.WriteHeader(http.StatusAccepted)
	w.Write([]byte("hello"))
	return
}

func logreader(w http.ResponseWriter, r *http.Request) {
	http.ServeFile(w, r, "webrequests.log")
}

func checkSecurity(next http.HandlerFunc) http.HandlerFunc {
	return http.HandlerFunc(func(res http.ResponseWriter, req *http.Request) {
		err = IsSignatureValid(req)
		if err != nil {
			res.WriteHeader(http.StatusForbidden)
			res.Write([]byte("403 - Forbidden"))
			return

		}

		next(res, req)
	})
}

func checkAdmin(next http.HandlerFunc) http.HandlerFunc {
	return http.HandlerFunc(func(res http.ResponseWriter, req *http.Request) {
		err = isAdminKey(req)
		if err != nil {
			res.WriteHeader(http.StatusForbidden)
			res.Write([]byte("403 - Forbidden"))
			return
		}
		date := time.Now()
		datestr := date.String()
		expire := req.Header.Get("expire")
		log.Println(expire)
		log.Println(datestr)
		if datestr > expire {
			res.WriteHeader(http.StatusUnauthorized)
			res.Write([]byte("401 - Signature Expired"))
			return

		}

		r := req.Header.Get("user-agent")
		if r == "yolo" {
			res.WriteHeader(http.StatusAccepted)
			res.Write([]byte("yolo"))
			return
		}

		next(res, req)
	})
}
func requestLogger(next http.HandlerFunc) http.HandlerFunc {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		start := time.Now()

		next.ServeHTTP(w, r)

		// log request by who(IP address)
		requesterIP := r.RemoteAddr

		log.Printf(
			"%s\t\t%s\t\t%s\t\t%s\t\t%v\t\t%s",
			r.Method,
			r.Host+r.URL.Path,
			r.RequestURI,
			requesterIP,
			time.Since(start),
			r.Header)

	})
}

// main function to boot up everything
func main() {
	fileName := "webrequests.log"
	logFile, err := os.OpenFile(fileName, os.O_WRONLY|os.O_CREATE|os.O_APPEND, 0666)
	if err != nil {
		log.Println(err)
	}
	defer logFile.Close()
	log.SetOutput(logFile)

	handleRequests()

}
