# SOCKING IT TO YA (Solution)

## Finding the Challenge

This challenge was hosted at http://socking-it-to-ya.bsidespdxctf.party ports open 8081 8082 1080 also we were give a private key at the end of 100

```
-----BEGIN PRIVATE KEY-----
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
	-----END PRIVATE KEY-----
```

## Solution
The Challenge drops you on a website that once again only has a few live links. One of the links directs you to another port `8081/security` with an SSL error. and the other downloads what looks like a PDF. There is also a port `1080` if you connect to it you get an authentication error .

First Download the "rules.pdf" if we run file on it we find out that it is in fact a jpg. If we run steghide on the rules.jpg we find out that there is a secret.txt file inside

`steghide extract -sf The_rules.pdf`

Inside the secret.txt we find that there are some credentials.

`Username:Jorge`
`Password:82a07cc1b6cc1d05e594aeb3354da513438dc9695d3d15f6a70adf3697ba4fef`

Now that we have the credentials for the proxy if we try to connect to the security page we still get the client certificate warning.

There is a hint on the main page about whats going on here. The server is doing mutual TLS. Well we are given a private key to start the challenge so by grabbing the public certificate from the port `8081` using openssl 
`openssl s_client -connect socking-it-to-ya.bsidespdxctf.party:8081`

```
-----BEGIN CERTIFICATE-----
MIIDrTCCApWgAwIBAgIURD387nezQwUSYH7yw4x1iL6o0ecwDQYJKoZIhvcNAQEL
BQAwZjELMAkGA1UEBhMCVVMxDzANBgNVBAgMBk9yZWdvbjERMA8GA1UEBwwIUG9y
dGxhbmQxDzANBgNVBAoMBmJzaWRlczEOMAwGA1UECwwFIFVuaXQxEjAQBgNVBAMM
CWxvY2FsaG9zdDAeFw0yMDEwMTUwNDA0MjFaFw0zMDEwMTMwNDA0MjFaMGYxCzAJ
BgNVBAYTAlVTMQ8wDQYDVQQIDAZPcmVnb24xETAPBgNVBAcMCFBvcnRsYW5kMQ8w
DQYDVQQKDAZic2lkZXMxDjAMBgNVBAsMBSBVbml0MRIwEAYDVQQDDAlsb2NhbGhv
c3QwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCpQ8VV1H1O6c5D8Fo/
h0hMzjDtoG991q/d2NWFLHPhzKZ79bTzbfZQkyEKMujsEx3tLMZNxnaVGn5MflPe
bGC+tYOmovZNW6l7wwEcFBZFXXx4QmQhgWfSD/AwQaOIWw2rOijvzx5vYJuFW1GJ
byPp3mDjNgzWzesD8Aal5MmlKmz3cJFVhcdQOesNzYhEttwVJER2uQ9xl74cYRou
jbm1eKAJSG+i26Pj5CeRCZ2kL3xn76viUXr2gS2Sg03B2LKl6fNfKphdjw9EJs3P
ji/H9USdc80UxjXC3midm6AGP2+fmrjQSBYW0kI4eU1IwfdnXJ2RaL9MhIMNJyzS
t14hAgMBAAGjUzBRMB0GA1UdDgQWBBTrwbx4sPf2VZC30xDN+oekavTxHTAfBgNV
HSMEGDAWgBTrwbx4sPf2VZC30xDN+oekavTxHTAPBgNVHRMBAf8EBTADAQH/MA0G
CSqGSIb3DQEBCwUAA4IBAQCJjBP2vjE1LCnNsBeK0OmnCkyd26DiTJy5MRKG7SEb
bDjPX3l0ark/JQXjwgSwnPDPJ2GgMcnZD6l2xLvmkCAlX0K44HvPqjpKx6+K/2hB
/mkXMHtX/Zj6BQxawEsP3iQWt5gdwgWUFczdLyi9zc/1drq45N7NTBunx9MeriEi
eMlVoeqf4sR3LlSG6HWz/lIATxd/qCYXHGWufNDcrAtDPtG/m49VLnpXYQ+ZgtZY
3pqzjLGUwAb/EqVRWt9N24f35ene5JzSE4670+lErAG8mBtUbN2yNf36IP7thLVP
ofBLvPq2RyeAtbIXt/AmJ339Xq3b7gODwWgU85XXaacm
-----END CERTIFICATE-----
```

Now if we do a curl to the server through the proxy to `socking-it-to-ya.bsidespdxctf.party:8081/security/` we are given the flag and some awesome ascii art :)


`curl -k -x socks5://Jorge:82a07cc1b6cc1d05e594aeb3354da513438dc9695d3d15f6a70adf3697ba4fef@socking-it-to-ya.bsidespdxctf.party:1080 --key key.pem --cert localhost.pem https://localhost:8081/security`

```
Welcome to the new and improved Super Secure Admin Page.


flag: BSidesPDX{MTLS_1S_SUP3R_C00L_S0_1S_Wh1t3_L1sts}
```

