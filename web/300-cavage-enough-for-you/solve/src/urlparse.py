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

#endpoints=["flagp1","flagp2","flagp3","flagp4","flagp5"]
endpoints=["flagp5","flagp4","flagp3","flagp2","flagp1"]
    
i = 0
for line in log:    
     #get = re.findall(a,log)[i].split('/')[-1]
     #get = log.split()[1].split('/')
     authorization = re.findall(b,log)[i]
     date = re.findall(c,log)[i]
     expire = re.findall(d,log)[i]
     host = re.findall(e,log)[i]
     #ep= host.split()[1].split('/')[-1]
        
        
    
     r= requests.get("http://localhost:1337/"+endpoints[i],headers={"Accept-Encoding":"gzip",'Authorization':authorization,"Date":date,"Expire":expire,"Host":host})
        
    #del prepped.headers['Connection']
     #print(endpoints[i])  
     print(r.text)
     #print(get,authorization,endpoints[i])
     i+=1
     if i == 5:
         break

    


#headers = b.findall(a)[0].split('"')[1]
# '(request-target) host date content-type expire'
#print(headers)

