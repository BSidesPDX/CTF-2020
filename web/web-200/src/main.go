package main

import (
	"crypto/tls"
	"crypto/x509"
	"encoding/json"
	"fmt"
	"log"
	"net"
	"net/http"
	"os"
	"strings"

	"github.com/gorilla/mux"
)

var (
	err    error
	config = LoadConfiguration("config.json")
	cwd, _ = os.Getwd()
)

type httpHandlerFunc func(http.ResponseWriter, *http.Request)
type tcpKeepAliveListener struct {
	*net.TCPListener
}

type Config struct {
	Host     string `json:"host"`
	Port     string `json:"port"`
	HttpPort string `json:"httpPort"`
	IP       string `json:"ip"`
}

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
func check(next httpHandlerFunc) httpHandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		err = whitelisting(r, config.IP)
		if err != nil {
			w.WriteHeader(http.StatusUnauthorized)
			w.Write([]byte("401 - Unauthorized"))
			return
		}
		next(w, r)
	}
}

func redirect(next httpHandlerFunc) httpHandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		// remove/add not default ports from req.Host
		host := strings.Split(r.Host, ":")[0]
		target := "https://" + host + ":" + config.Port + r.URL.Path
		if len(r.URL.RawQuery) > 0 {
			target += "?" + r.URL.RawQuery
		}
		log.Printf("redirect to: %s", target)
		http.Redirect(w, r, target,
			// see comments below and consider the codes 308, 302, or 301
			http.StatusTemporaryRedirect)
	}
}

func handleRequests() {
	//load tls certs from tls_common
	cert, err := tls.X509KeyPair(WebserverCertificate, WebserverPrivateKey)
	if err != nil {
		log.Fatalln("cant find certs")
	}
	caCertPool := x509.NewCertPool()
	caCertPool.AppendCertsFromPEM(WebserverCertificate)
	//Implementation of MTLS
	tlsConfig := &tls.Config{
		Certificates: []tls.Certificate{cert},
		ClientCAs:    caCertPool,
		ClientAuth:   tls.RequireAndVerifyClientCert,
	}

	fileServer := http.FileServer(http.Dir(cwd))
	router := mux.NewRouter().StrictSlash(true)

	router.HandleFunc("/security", check(security))

	//Http router for the rules
	router2 := mux.NewRouter().StrictSlash(true)
	router2.Handle("/robots.txt", fileServer)
	router2.PathPrefix("/static/").Handler(http.StripPrefix("/static/", http.FileServer(http.Dir("./static"))))
	router2.HandleFunc("/rulesforwinning/", rulesofwinning)
	router2.HandleFunc("/security", redirect(security)).Methods("GET")
	router2.Handle("/", fileServer)

	//Server is loading config and hosting on provided config values.
	server := http.Server{
		Addr:      config.Host + ":" + config.Port,
		Handler:   router,
		TLSConfig: tlsConfig,
	}
	httpServer := http.Server{
		Addr:    config.Host + ":" + config.HttpPort,
		Handler: router2,
	}

	fmt.Println("Starting server https://" + config.Host + ":" + config.Port)
	go server.ListenAndServeTLS("", "")

	go Proxy()

	fmt.Println("Starting server http://" + config.Host + ":" + config.HttpPort)
	httpServer.ListenAndServe()

}

func security(w http.ResponseWriter, r *http.Request) {

	fmt.Fprint(w, "Welcome to the new and improved Super Secure Admin Page.\n")
	w.Write([]byte(Asciivold))

	fmt.Fprint(w, "\n\n\nflag: BSidesPDX{MTLS_1S_SUP3R_C00L_S0_1S_Wh1t3_L1sts}\n")

	return
}

func rulesofwinning(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("COntent-Disposition", "attachment; filename=The_rules.pdf")
	w.Header().Set("Content-Type", r.Header.Get("Content-Type"))
	http.ServeFile(w, r, cwd+"/static/images/The_rules.pdf")
	return
}

// main function to boot up everything
func main() {
	handleRequests()

}
