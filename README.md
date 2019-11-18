# BSidesPDX CTF 2020

## BSidesPDX

BSidesPDX CTF 2020 is using the [bsides-ctf-framework](https://github.com/BSidesPDX/bsides-ctf-framework). See [TTimzen's blog post](https://www.tophertimzen.com/blog/BSidesPDXCTFFramework/) for a detailed explanation of the framework, motivations, and instructions for writing challenges.

Challenge authors:
- <Add yourself here when submitting a PR>


## Final Statistics

RESERVED FOR FINAL STATISTICS. SEE [CTF-2019](https://github.com/BSidesPDX/CTF-2019/edit/master/README.md) FOR MORE.

## Challenges

| Challenge Name                                                 | Category      | Points | Port(s)             |
| -------------------------------------------------------------- | ------------- | ------ | ------------------- |
|  <Add challenge information here>              |       |     |                 |


## Local Deployment

To locally test, deploy or play challenges with Docker, run the following (Ubuntu)

1. `sudo apt install docker-compose gcc-multilib g++-multilib linux-libc-dev:i386`
2. `make`
3. `docker-compose build && docker-compose up -d`
4. Containers are viewable at localhost:PORT (view with docker-compose ps)
5. `docker-compose kill` to stop the containers
6. `make clean` to clean the source folders


## Cloud Deployment

This year we ran all of our challenges in k8s using the Makefile and yamls in the `oci` directory of all pwn and web challenges.  Due to Docker issues with Trust Game, this was manually deployed to a standalone compute instance.
