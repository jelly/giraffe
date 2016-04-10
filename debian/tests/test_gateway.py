#!/usr/bin/python

import os
import unittest

import imaplib
import poplib

import zarafa

auth_user = os.environ['AUTH_USER']
auth_pass = os.environ['AUTH_PASS']


class TestGateway(unittest.TestCase):
    '''
    Tests for zarafa-gateway
    '''

    def logonPOP3(self):
        client = poplib.POP3('127.0.0.1')
        _ = client.user(auth_user)
        _ = client.pass_(auth_pass)
        return client

    def testIMAPLogin(self):
        client = imaplib.IMAP4(host='127.0.0.1', port=143)
        response = client.login(auth_user, auth_pass)
        self.assertIn('OK', response)

    def testPOP3Login(self):
        client = poplib.POP3('127.0.0.1')
        response = client.user(auth_user)
        self.assertIn('Waiting for password', response)
        response = client.pass_(auth_pass)
        self.assertIn('Username and password accepted', response)

    def testPOP3List(self):
        user = zarafa.Server(auth_user=auth_user, auth_pass=auth_pass).user(auth_user)
        user.inbox.create_item(subject='test', body='test')

        client = self.logonPOP3()
        self.assertIn('+OK 1 messages', client.list())
