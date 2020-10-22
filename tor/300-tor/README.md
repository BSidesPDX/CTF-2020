# 300 - Microblog

## Description

Using part of the [Flask Mega Tutorial](https://blog.miguelgrinberg.com/post/the-flask-mega-tutorial-part-i-hello-world) as the base, it's a fairly simple Twitter-like service. The difference, however, is this one allows users to either upload or link to a jpg or png for their avatar.

If the user gives a URL, it first does a HEAD request to attempt to ensure the URL points to an actual image of a < 1MB. If it appears to be an image, it will then attempt to get the image at the URL and the flag will be in the headers for the request.

## Deploy

Build and run the Docker container.

## Challenge

I stumbled across a hidden microblogging service, if there was only some way to get the server side to leak some info.

Author(s): fdcarl

Flag: `BSidesPDX{3veR_7r!ed_t0_sSrF_4n_0n!on?}`
