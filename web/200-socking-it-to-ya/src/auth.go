package main

import (
	"errors"
	"net"
	"net/http"

	"github.com/cloudflare/cfssl/whitelist"
)

func whitelisting(req *http.Request, ip string) error {

	whiteList := whitelist.NewBasic()
	whiteList.Add(net.ParseIP(ip))

	hostHTTPIP, err := whitelist.HTTPRequestLookup(req)
	if err != nil {
		return err
	}

	httpCheck := whiteList.Permitted(hostHTTPIP)

	if httpCheck != true {
		err = errors.New("Not in the list")
		return err
	}
	return nil

}
