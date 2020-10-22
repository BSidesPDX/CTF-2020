package main

import (
	"crypto"
	"log"
	"net/http"
	"time"

	"github.com/spacemonkeygo/httpsig"
)

func signer(r *http.Request, privateKey crypto.PrivateKey) (*http.Request, error) {

	Date := time.Now()
	expire := Date.Add(time.Minute * 2)
	r.Header.Set("Date", Date.String())
	r.Header.Set("Host", r.Host)
	r.Header.Set("expire", expire.String())
	r.Header.Set("user-agent", "yolo")

	signer := httpsig.NewSigner("admin", privateKey, httpsig.RSASHA256, []string{"(request-target)", "Host", "Date", "Content-Type", "expire"})

	err := signer.Sign(r)
	if err != nil {
		log.Fatalln(err)
	}

	return r, nil

}
