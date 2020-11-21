#!/usr/bin/env python
f = open('./secret', 'rb')
r = f.read()
ff = open('fuck', 'wb')
ff.write(r[::-1])
ff.close()
