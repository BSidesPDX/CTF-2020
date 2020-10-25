# BSidesPDX CTF 2020

## BSidesPDX

BSidesPDX CTF 2020 is using the [bsides-ctf-framework](https://github.com/BSidesPDX/bsides-ctf-framework). See [TTimzen's blog post](https://www.tophertimzen.com/blog/BSidesPDXCTFFramework/) for a detailed explanation of the framework, motivations, and instructions for writing challenges.

Challenge authors:
- [aagallag](https://twitter.com/aagallag)
- [arinerron](https://twitter.com/arinerron)
- [0xdade](https://twitter.com/0xdade)
- [fdcarl](https://twitter.com/fdcarl)
- [0x1nd0](https://twitter.com/0x1nd0)


## Final Statistics

RESERVED FOR FINAL STATISTICS. SEE [CTF-2019](https://github.com/BSidesPDX/CTF-2019/edit/master/README.md) FOR MORE.

## Challenges

| Challenge Name                                                 | Category      | Points | Cloud Port(s)       | Local Port(s)       |
| -------------------------------------------------------------- | ------------- | ------ | ------------------- | ------------------- |
| [Sowing Discord](intro/)                                       | intro         | 10     | N/A                 | N/A                 |
| [Flag Vault](re/100-flagvault/)                                | re            | 100    | N/A                 | N/A                 |
| [flagvault.c](re/200-flagvault.c/)                             | re            | 200    | N/A                 | N/A                 |
| [cheatcode](re/300-cheatcode/)                                 | re            | 300    | N/A                 | N/A                 |
| [Heading the Right Way](web/100-heading-the-right-way/)        | web           | 100    | 8081                | 8080                |
| [SOCKING IT TO YA](web/200-socking-it-to-ya/)                  | web           | 200    | 8081, 8082, 1080    | 8081, 8082, 1080    |
| [Cavage Enough for You](web/300-cavage-enough-for-you/)        | web           | 300    | 1337                | 1337                |
| [basic-bof-1](pwn/100-basic-bof-1/)                            | pwn           | 100    | 9999                | 9990                |
| [basic-bof-2](pwn/200-basic-bof-2/)                            | pwn           | 200    | 9999                | 9991                |
| [speakers](pwn/300-speakers/)                                  | pwn           | 300    | 9999                | 9991                |
| [Default Onion](tor/100-default-onion/)                        | tor           | 100    | N/A                 | N/A                 |
| [Default Onion - Fixed](tor/200-default-onion-fixed/)          | tor           | 200    | N/A                 | N/A                 |
| [Microblog](tor/300-microblog/)                                | tor           | 300    | N/A                 | N/A                 |
| [Please Stand By](over-the-air/100-Please-Stand-By/)           | over-the-air  | 100    | N/A                 | N/A                 |
| [Xclusive Numborz](over-the-air/200-Xclusive-numborz/)         | over-the-air  | 200    | N/A                 | N/A                 |
| [Down the rabbit hole](over-the-air/300-Down-the-rabbit-hole/) | over-the-air  | 300    | N/A                 | N/A                 |


## Local Deployment

To locally test, deploy or play challenges with Docker, run the following (Ubuntu)

1. `sudo apt install docker-compose`
2. `sudo docker-compose build && docker-compose up -d`
3. Containers are viewable at localhost:PORT (view with docker-compose ps)
4. `sudo docker-compose down` to stop the containers

### Get Onion Addresses for Tor Challenges

Default Onion: `sudo docker exec -it default-onion cat /var/lib/tor/hidden_http/hostname`
Default Onion - Fixed: `sudo docker exec -it default-onion-fixed cat /var/lib/tor/hidden_http/hostname`
Microblog: `sudo docker exec -it microblog cat /var/lib/tor/hidden_http/hostname`

## Cloud Deployment

This year we ran all of our challenges in k8s using the Makefile and yamls in the `oci` directory of all pwn, web, and tor challenges.  The Over-the-Air challenges had a Twilio bot and were streaming to Twitch on a seperate VM.  We've done our best to include all of the tools and information required to stand-up the Over-the-Air challenges locally, but due to the use of Twilio, it will be difficult to replicate the challenge: `Down the rabbit hole` in it's entirety.
