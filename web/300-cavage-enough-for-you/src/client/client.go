package main

import (
	"bytes"
	"crypto/x509"
	"encoding/pem"
	"io/ioutil"
	"log"
	"net/http"
	"os"
	"time"
)

var (
	client    http.Client
	httpBool  bool = false
	socksBool bool = false
)

func clientfire(ep string) {

	host, ok := os.LookupEnv("SERVERIP")
	if !ok {
		log.Fatalln("environment var was not set")
	}

	privateKey := keypkcs8

	privBlock, _ := pem.Decode([]byte(privateKey))
	if privBlock == nil || privBlock.Type != "PRIVATE KEY" {
		log.Panicf("failed to decode PEM block containing private key")
	}

	priv, err := x509.ParsePKCS8PrivateKey(privBlock.Bytes)
	if err != nil {
		log.Panicf("Error parsing Public Key: %v", err)
	}

	timeout := time.Duration(5 * time.Minute)

	client = http.Client{Timeout: timeout,
		Transport: &http.Transport{},
	}

	request, err := http.NewRequest("GET", "http://"+host+":1337/"+ep, bytes.NewBufferString(""))
	if err != nil {
		log.Fatalln(err)
	}

	//tets, err := signer(request, priv, requestBody)
	tets, err := signer(request, priv)
	if err != nil {
		log.Fatalln(err)
	}
	log.Println(tets)

	resp, err := client.Do(tets)
	if err != nil {
		log.Fatalln(err)
	}
	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Fatalln(err)
	}
	log.Println(string(body))

}

func repete() {

	endpoints := [5]string{"flagp1", "flagp2", "flagp3", "flagp4", "flagp5"}

	for true {
		for _, endpoint := range endpoints {

			clientfire(endpoint)

		}
		time.Sleep(time.Second * 30)
	}
}

func main() {
	repete()
}
