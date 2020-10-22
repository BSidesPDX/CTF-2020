# 300 Cavage Enough for You

## Description
Tom has decided that he is tried of making a blog. Now he just wants to make Ascii art and have an api to access it. He has even let others use it.


## Challenge

Can you figure out what he messed up when making his api?


## Deploy
### server
>docker build -t web300 . && docker run -p 1337:1337 web300:latest

### client
Change env varable in Dockerfile
>docker build -t web300-client . && docker run  web300-client:latest



## Flag
`"BSidesPDX{HTTP_CAVAG3_S1GnaTur3s_Ar3_R3a11y_c001}`
