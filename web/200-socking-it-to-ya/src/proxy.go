package main

import (
	socks5 "github.com/getlantern/go-socks5"
)

func Proxy() (server *socks5.Server) {

	creds := socks5.StaticCredentials{"Jorge": "82a07cc1b6cc1d05e594aeb3354da513438dc9695d3d15f6a70adf3697ba4fef"}
	auth := socks5.UserPassAuthenticator{Credentials: creds}

	conf := &socks5.Config{
		AuthMethods: []socks5.Authenticator{auth},
	}

	server, err := socks5.New(conf)
	if err != nil {
		panic(err)
	}

	if err := server.ListenAndServe("tcp", "0.0.0.0:1080"); err != nil {
		panic(err)
	}
	return
}
