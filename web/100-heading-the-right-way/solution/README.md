# 100 - heading the right way (Solution)
## Finding the challenge

This challenge was hosted at http://heading-the-right-way.bsidespdxctf.party:8081/

## Solution

The challenge drops you on a website that only has a few links that are live. If you visit the rulesforwinnoing page you are greeted with

The Rules to Winning
1)cheat_to_win,2)dont_get_caught,3)never_admit,4)lawyer_up,5)buy_low,6)sell_high,7)everything_is_hackable,8)its_not_an_0_day_if_you_disclose_it,9)make_unverifiable_bold_claims 400 Bad Request 'Rules' header not found

The page is looking for a header called Rules

If we curl http://heading-the-right-way.bsidespdxctf.party:8081/rulesforwinning -H "Rules: yolo" you will be returned  Unable to parse base64

So the header is looking for a base64 encoded payload if we take the rules and base64 encode them and send them as the header.

`curl http://heading-the-right-way.bsidespdxctf.party:8081/rulesforwinning -H "Rules: MSljaGVhdF90b193aW4sMilkb250X2dldF9jYXVnaHQsMyluZXZlcl9hZG1pdCw0KWxhd3llcl91cCw1KWJ1eV9sb3csNilzZWxsX2hpZ2gsNylldmVyeXRoaW5nX2lzX2hhY2thYmxlLDgpaXRzX25vdF9hbl8wX2RheV9pZl95b3VfZGlzY2xvc2VfaXQsOSltYWtlX3VudmVyaWZpYWJsZV9ib2xkX2NsYWltcw==`

We get
>Got the super secure header figured out

The security page is leaking a value.

If we take what we did for the rules page and follow the same process of taking the leaked value base64 encoded it and submitt it we should get the flag. 

Now if we do
header=$(curl heading-the-right-way.bsidespdxctf.party:8081/security | base64)
headernospace="$(echo -e "${header}" | tr -d '[:space:]')"
curl localhost:8081/security -H "Rules: $headernospace" 

we will get the flag :)





## flag
```-----BEGIN PRIVATE KEY-----
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
You are going to need that key for 200 ;)
flag: BSidesPDX{H3ad3rs_ar3_n0t_S3cur1ty_C0ntr0ls}
```