# 300 Cavage enough for you (Solution)

## Finding the Challenge

You are given an api on port 1337 at http://cavage-enough-for-you.bsidespdxctf.party:1337 with the following on the page 
```
Super legit api
	/addkey Methods   POST	


	To add a Key you need to submit a kid and public key
	Example
	{
	"kid":"yolo",
	"rsapub":"-----BEGIN PUBLIC KEY-----"
	}
```

## Solution

The first thing you need to do is to upload a public key to the api

`openssl genrsa -out key.pem 2048`
`openssl rsa -pubout -in key.pem -out key_public.pem`

As the API is looking for JSON formatted data you will need to remove the spaces and replace them with escapes
`cat key_public.pem |sed ':a;N;$!ba;s/\n/\\n/g' | sed 's/ *$//' >key_public_nosp.pem`
`truncate -s -1 key_public_nosp.pem`

Once you have created your public key you will need to submit it to the api .
`curl -k -X POST http://localhost:1337/addkey -d @payload.json`

After the key is uploaded you are presented more information about other endpoints that are available.
```
Key Loaded

Other Endpoints you have access to are the following

 /hello
/logs
/ascii
 
Dont forget to sign your (request-target), host, date.
```
Now the rest of these apis are protected by HTTP Cavage Signatures. To interact with the api you will need to create a signer to sign your requests. See the src folder for a golang version of a signer. Note you will need to make a pkcs8 version of your private key to sign requests 

`openssl pkcs8 -topk8 -inform PEM -outform PEM -in key.pem -out key.pkcs8 -nocrypt`

The API is looking for 3 specific headers signed to interact with them the ` (request-target), host, and date` 

After the signer is built do a get request to the logs endpoint to see that there are 5 undocumented endpoints `flagp1-5` 

If you try to use your signer with your private key you will get a `403 - Forbidden`

To solve this you will need to do a HTTP replay attack against the endpoint. To do this attack you will need to script out the request as the signatures expire in 1< mins time. An example of this can be viewed if you look in the `urlparse.py` python script inside the src directory.

Once you get your script working execute it and you will get the flag 1 request at a time.

```
c001}
3_R3a11y_
S1GnaTur3s_Ar
{HTTP_CAVAG3_
BSidesPDX
```
or 
>BSidesPDX{HTTP_CAVAG3_S1GnaTur3s_Ar3_R3a11y_c001}


