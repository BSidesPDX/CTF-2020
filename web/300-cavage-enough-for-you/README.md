# 300 - Cavage Enough for You

## Description

TODO


## Deploy

### server
> docker build -t web300 . && docker run -p 1337:1337 web300:latest

### client
Change env varable in Dockerfile
> docker build -t web300-client . && docker run  web300-client:latest


## Challenge

Tom has decided that he is tired of making a blog. Now he just wants to make Ascii art and have an api to access it. He has even let others use it.

Can you figure out what he messed up when making his api?

Author(s): 1nd0

Flag: `BSidesPDX{HTTP_CAVAG3_S1GnaTur3s_Ar3_R3a11y_c001}`
