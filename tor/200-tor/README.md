# 200 - Default Onion - Fixed

## Description

Similar to the previous, Tor challenge, this is a mostly default Apache service running as a Tor hidden service.  However, this time the `/server-status` page is configured to check that the supplied HTTP host is either `localhost` or `127.0.0.1`.  The problem is this host field can just be modified in the request itself.

## Deploy

Build and run the Docker container.

## Challenge

Oops, I fixed the bug in the previous Tor challenge.

Author(s): fdcarl

Flag: `BSidesPDX{pLz_ju5T_Us3_nG!nX_inS7e4D}`
