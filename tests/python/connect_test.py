#!/usr/bin/env python3
#
# Copyright (C) 2018 Jayson Wang
#
import time
import socket
import logging


class SsConnectTest(object):

    def __init__(self, host: str, port: int):
        self._host = host
        self._port = port

    def test_tcp_connect(self):
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.connect((self._host, self._port))

            time.sleep(1)
            s.close()

            logging.info('tcp_connect: success')
        except ConnectionRefusedError:
            logging.error('server running?')

    def test_udp_connect(self):
        pass


if __name__ == '__main__':
    logging.basicConfig(level=logging.DEBUG)
    testSuite = SsConnectTest('localhost', 9980)

    testSuite.test_tcp_connect()
    testSuite.test_udp_connect()
