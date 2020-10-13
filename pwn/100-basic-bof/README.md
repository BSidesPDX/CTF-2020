# 100 - basic-bof

## Description

A simple buffer overflow challenge. There is no win() function, but it gives you a libc leak, so it's trivial to determine which libc remote is using using [libcdb](https://libc.blukat.me/?q=puts%3A7f5c448899c0&l=libc6_2.27-3ubuntu1_amd64), then call one\_gadget.

This challenge is also meant to introduce people to basic tools that'll be useful for the next two, harder challenges.

## Deploy

In `src/`, run `./compile.sh`. Then, the `Dockerfile` is ready to go. Provide `basic-bof` and `Dockerfile` (another way of determining libc version for solvers).

## Challenge

Welcome to basic bof. Just ret to one\_gadget as a warmup.

Author(s): arinerron

Flag: `BSidesPDX{r3t_t0-0ne_g@dg3t}`

