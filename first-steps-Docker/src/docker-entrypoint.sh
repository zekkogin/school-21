#!/bin/sh
gcc hello.c -o hello.fcgi -lfcgi
spawn-fcgi -p 8080 ./hello.fcgi
service nginx start
tail -f /dev/null
