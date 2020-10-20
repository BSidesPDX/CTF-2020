# 100 - basic-bof

## Description

A simple buffer overflow challenge. There is no win() function, but it gives you a libc leak, so it's trivial to determine which libc remote is using using [libcdb](https://libc.blukat.me/?q=puts%3A7f5c448899c0&l=libc6_2.27-3ubuntu1_amd64), then call one\_gadget.

This challenge is also meant to introduce people to basic tools that'll be useful for the next, harder challenges.

## Deploy

In `src/`, run `./compile.sh`. Then, the `Dockerfile` is ready to go. Provide `basic-bof` and `Dockerfile` (another way of determining libc version for solvers).

## Challenge

Welcome to basic bof. [Where can you return to now?](https://github.com/david942j/one_gadget)

Author(s): arinerron

Flag: `BSidesPDX{r3t_t0-0ne_g@dg3t}`

