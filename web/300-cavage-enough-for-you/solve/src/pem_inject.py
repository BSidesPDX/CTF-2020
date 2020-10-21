with open ("key_public_nosp.pem","rt") as file:
    pkcspub = file.read()
with open ("key.pkcs8", "rt") as file:
    pkcskey = file.read()

Client = open("tls.go", "rt")

outclient = open("tls2.go", "wt")

payload = open("payload.json", "rt")
payloadout = open("payload2.json","wt")

for line in Client:
    outclient.write(line.replace('PKCS8KEY',pkcskey))

for line in payload:
    payloadout.write(line.replace("RSAPUB",pkcspub))
 
Client.close
outclient.close
payload.close
payloadout.close
