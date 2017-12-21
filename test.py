#!/usr/bin/env python3

from pprint import pprint
import socket
import sys

try:
    hostname = sys.argv[1]
except IndexError:
    hostname = 'example.com'

result = socket.getaddrinfo(
    hostname, 0, 0, socket.SOCK_DGRAM, socket.IPPROTO_UDP, flags=0)

pprint(result)
