FROM alpine:latest

LABEL org.opencontainers.image.authors="romkasrm1985@gmail.com"

RUN apk update && \
    apk upgrade && \
    apk add git && \
    apk add build-base

RUN git config --global user.name "Kasimov Roman Elmirovich" && \
    git config --global user.email "romkasrm1985@gmail.com" && \
    git clone https://github.com/kas1movrom/parvpo

WORKDIR /parvpo/lab1

RUN g++ main.cpp -fopenmp -o main

CMD ["./main"]
