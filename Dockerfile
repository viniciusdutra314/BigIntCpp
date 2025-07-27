FROM ubuntu:rolling
RUN apt update && apt install -y clang clangd cmake libc++-dev