FROM ubuntu:20.04

RUN apt-get update -y;
RUN apt-get install libfcgi-dev -y \
    && apt-get install gcc -y \
    && apt-get install spawn-fcgi -y \
    && apt-get install curl -y \
    && apt-get install nginx -y


COPY docker-entrypoint.sh /

WORKDIR /etc/nginx/

COPY /server/hello.c hello.c
COPY /server/default sites-enabled/.

ENTRYPOINT [ "/docker-entrypoint.sh" ]
