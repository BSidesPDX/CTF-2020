# 100 - Default Onion

## Description

A mostly default Apache service running as a Tor hidden service.  The most common technique for leaking an Apache Tor hidden service's real IP address is to visit `/server-status`.  While this doesn't actually leak the IP address, it does include a flag in the Header of the response.

## Deploy

Build and run the Docker container.

## Challenge

I found this Tor hidden service.  Are you able to leak any underlying information about it?

[http://bsidespdxcgjccaz.onion](http://bsidespdxcgjccaz.onion)

Author(s): 0xdade

Flag: `BSidesPDX{4p4ch3_s3rv3r_st4tus_1s_l34ky}`
