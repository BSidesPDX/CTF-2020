package main

import (
	"encoding/base64"
	"encoding/json"
	"fmt"
	"log"
	"math/rand"
	"net"
	"net/http"
	"os"

	"github.com/gorilla/mux"
)

var (
	err                 error
	config              = LoadConfiguration("config.json")
	cwd, _              = os.Getwd()
	rules               = []byte(`1)cheat_to_win,2)dont_get_caught,3)never_admit,4)lawyer_up,5)buy_low,6)sell_high,7)everything_is_hackable,8)its_not_an_0_day_if_you_disclose_it,9)make_unverifiable_bold_claims`)
	WebserverPrivateKey = []byte(`-----BEGIN PRIVATE KEY-----
	MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQCpQ8VV1H1O6c5D
	8Fo/h0hMzjDtoG991q/d2NWFLHPhzKZ79bTzbfZQkyEKMujsEx3tLMZNxnaVGn5M
	flPebGC+tYOmovZNW6l7wwEcFBZFXXx4QmQhgWfSD/AwQaOIWw2rOijvzx5vYJuF
	W1GJbyPp3mDjNgzWzesD8Aal5MmlKmz3cJFVhcdQOesNzYhEttwVJER2uQ9xl74c
	YRoujbm1eKAJSG+i26Pj5CeRCZ2kL3xn76viUXr2gS2Sg03B2LKl6fNfKphdjw9E
	Js3Pji/H9USdc80UxjXC3midm6AGP2+fmrjQSBYW0kI4eU1IwfdnXJ2RaL9MhIMN
	JyzSt14hAgMBAAECggEADfJfmCriCFaLgF2VkhZ7hpiWv32wshW2d/kd3tNC2SAb
	t6sPNd+hpBH7bvOy7YDFvn0p+c6YhsCgF31xO6qCbjRWnKxgzw72cBQpSz78dsq1
	LtOJnJklDNHzYIaICvw1rB4msVvHjjXPmrVjiod11hdUtGQHustMyg5E/fZUBx/N
	fJsEOxRLepXoi4seAfVJ1i9yvKbQdhLD6iIJWco/1seKTDw43uy2O3xTkE8nEStH
	WQOU5BVNLOZSFZ6ulHIT041k0HflOGIGEte7tw77XoOpP7um3dnzpiQCEB9+M8op
	UQQ61VM8wCd4Z4CQWPk+ONyYV1zZR3ykMSDSOQ6yAQKBgQDRsQnXAdNP/vzurhXn
	Pq95aiCjx6p+rikBUZhHIw5WPVs7jdOPv1Mj78s9D8v0SRpAr4TJIjxHy7gZkTce
	9BBpe0XgD8jDGeOu2ekKIt4k4CV5gBggncPK0CvfVaN0c/j15KL6BBdw19L7IeJ8
	tZgNrEZVFHN/i+hWawkq4nL7aQKBgQDOpTE2b1uvHxw4m3d17TiCXHJT4QurFHDr
	NXQVnPZmE0LjWukQqgAZ7GQN73n+S2wPJL8uPSJqDizfGenBbcxx3BOPbeD+lyRu
	+bSKdrR6hsRtRtgjGg1YXCXSSEZggxZyX66+uVGK6pn9Lm/CFxIOzGY/9O/oskv5
	6xOb1CiN+QKBgGGz46nSp+r2HFP5uSruAkTINj0Zo08zRtfedN1wcBWusPumsZSg
	yNRNvpzM53MDPMA3B9/Pm9a4DSecidpaTetYDM7BjAGb5oJp9jNK28bCybM7BALu
	f3PYWxjMhkSUZMPtrCJiFan2Zc+tkiIZWqfERWEPDmG3hqH9bWAV8w1BAoGBAMYX
	RR3RkipFwF/jaJj7Vnhg9pfB29WcOsK+8xDk7q7bN/uKYnE/BenT2fYh4ugKlQPP
	ThWdNShFfm5AAP0TrDBZr8aGpnBnot1fMdqqAEiUeCfpCbhceP6DFx6FejF6eEIb
	xv+91pU8X3F82lVMmFrnRf15Z6HBiWOCHcH7lwTBAoGAJ2enLDc7aGxBSYvJHJlW
	UP8nGu8FbDtVaWJJyha12Q4bnPAQc2eElD7yTQFJ1ABuCDyHIj1WE/LkxYr8Wm0a
	xFkcjwjPBkD9CyVcG3EwwA47pyTTgSGQljxHt0hfLz/yc11K2nRQ18hQoufdKvuh
	LEHnsCZexdUfEQO2gnN7tLY=
	-----END PRIVATE KEY-----`)
	num = randStringBytes(128)
)

type httpHandlerFunc func(http.ResponseWriter, *http.Request)
type tcpKeepAliveListener struct {
	*net.TCPListener
}

type Config struct {
	Host string `json:"host"`
	Port string `json:"port"`
	IP   string `json:"ip"`
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

func handleRequests() {
	//load tls certs from tls_common
	fileServer := http.FileServer(http.Dir(cwd))
	router := mux.NewRouter().StrictSlash(true)
	router.Handle("/robots.txt", fileServer)
	router.PathPrefix("/static/").Handler(http.StripPrefix("/static/", http.FileServer(http.Dir("./static"))))
	router.Handle("/", fileServer)
	router.HandleFunc("/rulesforwinning/", rulesofwinning)
	router.HandleFunc("/security", security)

	//Server is loading config and hosting on provided config values.
	server := http.Server{
		Addr:    config.Host + ":" + config.Port,
		Handler: router,
	}

	fmt.Println("Starting server https://" + config.Host + ":" + config.Port)

	log.Panic(server.ListenAndServe())

}

const letterBytes = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

func randStringBytes(n int) string {
	b := make([]byte, n)
	for i := range b {
		b[i] = letterBytes[rand.Intn(len(letterBytes))]
	}
	return string(b)
}

func security(w http.ResponseWriter, r *http.Request) {
	rowHeader := r.Header.Get("Rules")
	rowEncoded := base64.StdEncoding.EncodeToString([]byte(num))
	if rowHeader == rowEncoded {
		fmt.Fprint(w, "Welcome to the Super Secure Admin Page the MTLS Private key is.\n")
		w.Write([]byte(WebserverPrivateKey))

		fmt.Fprint(w, "\nflag: BSidesPDX{H3ad3rs_ar3_n0t_S3cur1ty_C0ntr0ls\n")
		return

	}
	if rowHeader != "" {
		http.Error(w, "Unable to parse base64", http.StatusBadRequest)
		return
	}
	if r.Method != "GET" {
		http.Error(w, "Method is not supported.", http.StatusNotFound)
		return
	}

	w.Write([]byte(num))
	return
}

func rulesofwinning(w http.ResponseWriter, r *http.Request) {
	rowHeader := r.Header.Get("Rules")
	rowEncoded := base64.StdEncoding.EncodeToString(rules)
	if r.Method != "GET" {
		http.Error(w, "Method is not supported.", http.StatusNotFound)
		return
	}
	if rowHeader == rowEncoded {
		fmt.Fprint(w, "Got the super secure header figured out\n")
		return

	}
	if rowHeader != "" {
		fmt.Fprint(w, "Unable to parse base64")
		return
	}

	fmt.Fprint(w, "The Rules to Winning\n")

	fmt.Fprintf(w, "%s\n", rules)

	http.Error(w, "\n400 Bad Request 'Rules' header not found", http.StatusBadRequest)
	return
}

// main function to boot up everything
func main() {
	handleRequests()

}
