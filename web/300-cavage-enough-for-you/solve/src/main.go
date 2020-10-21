package main

import (
	"bytes"
	"crypto/x509"
	"encoding/pem"
	"flag"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"net/url"
	"os"
	"strings"
	"time"

	"golang.org/x/net/proxy"
)

//Payload struct is for determining the command that will be executed.
type Payload struct {
	Command string `json:"command"`
}

var (
	numArgs      = len(os.Args)
	sockProxy    string
	httpProxy    string
	ip           string
	proxyAddr    string
	client       http.Client
	defProxyPort      = "1080"
	httpBool     bool = false
	socksBool    bool = false
)

func main() {

	flag.StringVar(&httpProxy, "httpproxy", "", "Http Proxy to tunnel requests through")
	flag.StringVar(&sockProxy, "socks", "", "The SOCKS5 proxy to tunnel requests through")
	flag.StringVar(&ip, "host", "127.0.0.1", "Host you want to connect to.")

	flag.Parse()

	if httpProxy != "" {
		httpBool = true
	}
	if sockProxy != "" {
		socksBool = true
	}
	ip = strings.TrimSpace(ip)

	privateKey := keypkcs8

	privBlock, _ := pem.Decode([]byte(privateKey))
	if privBlock == nil || privBlock.Type != "PRIVATE KEY" {
		log.Panicf("failed to decode PEM block containing private key")
	}

	priv, err := x509.ParsePKCS8PrivateKey(privBlock.Bytes)
	if err != nil {
		log.Panicf("Error parsing Public Key: %v", err)
	}

	if len(os.Args) <= 1 {
		fmt.Println("No command provided ex:  ./Client -args command")
		os.Exit(1)
	}
	// Added Logging to Crook
	if _, err = os.Stat("/tmp/log/client"); os.IsNotExist(err) {
		os.MkdirAll("/tmp/log/Client", 0755)
	}
	logs, err := os.OpenFile("/tmp/log/Client/Client.log", os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		log.Println(err)

	}
	defer logs.Close()

	logger := log.New(logs, "", log.LstdFlags)
	timeout := time.Duration(5 * time.Minute)
	if httpBool == true {
		proxyAddr = strings.TrimSpace(httpProxy)
		if strings.ContainsAny(proxyAddr, ":") != true {
			proxyAddr = "http://" + proxyAddr + ":" + defProxyPort + "/"
		}
		proxyAddr, err := url.Parse(proxyAddr)
		if err != nil {
			log.Println(err)
		}
		fmt.Printf("Http Proxy was found, sending request over %s: \n", proxyAddr)
		client = http.Client{Timeout: timeout,
			Transport: &http.Transport{
				Proxy: http.ProxyURL(proxyAddr),
			},
		}
	} else if socksBool == true {
		proxyAddr = strings.TrimSpace(sockProxy)
		if strings.ContainsAny(proxyAddr, ":") != true {
			proxyAddr = proxyAddr + ":" + defProxyPort
		}
		dialer, err := proxy.SOCKS5("tcp", proxyAddr, nil, proxy.Direct)
		if err != nil {
			log.Fatalf("Cannot connect to the proxy:%s", err)
			os.Exit(1)
		}

		fmt.Printf("Socks proxy was found, sending requests over %s: \n", proxyAddr)
		client = http.Client{Timeout: timeout,
			Transport: &http.Transport{
				Dial: dialer.Dial,
			},
		}
	} else {
		client = http.Client{Timeout: timeout,
			Transport: &http.Transport{},
		}

	}
	//request, err := http.NewRequest("GET", "https://"+ip+"/hello", bytes.NewBuffer(requestBody))
	request, err := http.NewRequest("GET", "http://"+ip, bytes.NewBufferString(""))
	//request.Header.Set("Content-type", "application/json")
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
	fmt.Println(string(body))

	logger.Println(string(body))

}
