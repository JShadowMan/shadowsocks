#!/usr/bin/env python3
#
# Copyright (C) 2018 Jayson Wang
#
from sstest.network import Network


if __name__ == '__main__':
    with Network.create_socket('localhost', 9980) as fd:
        fd.send(b'\x05\x01\x00\x05\x01\x00\x03noob.ru\x00\x50')
