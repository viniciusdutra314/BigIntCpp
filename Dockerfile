#ubuntu 25.04
FROM ubuntu:sha256:95a416ad2446813278ec13b7efdeb551190c94e12028707dd7525632d3cec0d1
RUN apt update && apt install -y clang clangd cmake libc++-dev lldb