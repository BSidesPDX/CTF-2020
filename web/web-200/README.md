# Web-200-SOCKING-IT-TO-YA

## Description
Tom has decided that it would be better to not use headers for security and is going to implement something different 


## Challenge 
Can you figure out the new security systems Tom has put in place works and how to gain access to the super valuable secret. Note the proxy username and password is accessable somehow. **DO NOT TRY TO BRUTE FORCE IT** Ports to look at 8082 1080



## Deploy
>docker build -t web200 . && docker run -p 8081:8081 -p 8082:8082 -p 1080:1080 web200:latest

## Flag

`flag: BSidesPDX{MTLS_1S_SUP3R_C00L_S0_1S_Wh1t3_L1sts}`





