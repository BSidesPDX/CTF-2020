# 100 - Default Onion (Solution)

## Finding the challenge

There's an onion address in the challenge description. Grab yourself a Tor browser and navigate to it!

## Solving the challenge

The most common technique for leaking an Apache Tor hidden service's real IP address is to visit /server-status. So, just visit [http://bsidespdxcgjccaz.onion/server-status](http://bsidespdxcgjccaz.onion/server-status). The flag will be returned as a Header in the response.

## Flag
`BSidesPDX{4p4ch3_s3rv3r_st4tus_1s_l34ky}`