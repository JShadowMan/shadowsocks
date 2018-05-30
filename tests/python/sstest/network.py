#!/usr/bin/env python3
#
# Copyright (C) 2018 Jayson Wang
#
import socket
import contextlib


class Network(object):

    @staticmethod
    @contextlib.contextmanager
    def create_socket(host: str, port: int) -> socket.socket:
        s = socket.socket()
        s.connect((host, port))
        yield s
        s.close()
