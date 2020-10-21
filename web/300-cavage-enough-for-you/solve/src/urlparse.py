#!/usr/bin/python3


import re
import requests

with open ("logs.txt","rt") as file:
    log = file.read()
    
# endpoint
#endpoint = a.index()


# 'flagp3'
a = r'GET (\S+)'
b = r'Authorization:\[([^\]]+)'
c = r'Date:\[([^\]]+)'
d= r'Expire:\[([^\]]+)'
e = r'Host:\[([^\]]+)'

i = 0
for line in log:    
    get = re.findall(a,log)[i].split('/')[-1]
    authorization = re.findall(b,log)[i]
    date = re.findall(c,log)[i]
    expire = re.findall(d,log)[i]
    host = re.findall(e,log)[i]
    #ep= host.split()[1].split('/')[-1]
    
    
   
    r= requests.get("http://localhost:1337/"+get,headers={"Accept-Encoding":"gzip",'Authorization':authorization,"Date":date,"Expire":expire,"Host":host})
    
    #del prepped.headers['Connection']
    
    print(r.text)
    #print(get,authorization,date,expire,host)
    i+=1
    if i == 5:
        break

    


#headers = b.findall(a)[0].split('"')[1]
# '(request-target) host date content-type expire'
#print(headers)
