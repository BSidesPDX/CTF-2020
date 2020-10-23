# 200 - Default Onion - Fixed (Solution)

## Finding the challenge

There's an onion address in the challenge description. Grab yourself a Tor browser and navigate to it!

## Solving the challenge

So the challenge description mentions that the issue from the previous challenge has been fixed, and now it's only locally accessible. So, now if you visit [http://bsidespdxojp6j7d.onion/server-status](http://bsidespdxojp6j7d.onion/server-status), it fails.

The "only locally accessible" is a hint, and another common issue for web services in general. The service is relying on the `Host` header to determine if the request is local or not. So, simply modify the request to to send `Host: localhost` or `Host: 127.0.0.1` and the flag will appear in the same way as the previous challenge.

## Flag
`BSidesPDX{pLz_ju5T_Us3_nG!nX_inS7e4D}`