package main

import (
	"log"
	"net/http"

	"github.com/spacemonkeygo/httpsig"
)

// IsSignatureValid is a function used to check the HTTP sig and compare it to the pub key.
func IsSignatureValid(r *http.Request) error {

	r.Header.Set("Host", r.Host)

	var getter httpsig.KeyGetter = keystore

	verifier := httpsig.NewVerifier(getter)

	verifier.SetRequiredHeaders([]string{"(request-target)", "host", "date", "expire"})
	err = verifier.Verify(r)
	if err != nil {
		log.Printf("IsSignatureValid(%v) (%s)", &r, err.Error())
		return err
	}
	return err
}
func isAdminKey(r *http.Request) error {

	r.Header.Set("Host", r.Host)

	var getter httpsig.KeyGetterFunc = keystore.GetKey
	//var getter httpsig.KeyGetter = keystore
	getter.GetKey("admin")
	verifier := httpsig.NewVerifier(getter)

	verifier.SetRequiredHeaders([]string{"(request-target)", "host", "date"})
	err = verifier.Verify(r)
	if err != nil {
		log.Printf("IsSignatureValid(%v) (%s)", &r, err.Error())
		return err
	}
	return err
}
