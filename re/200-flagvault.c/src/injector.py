#!/usr/bin/env python2

with open('flagvault.clean', 'rb') as f:
	data = f.read()

OFFSET = 0x1c7b
LENGTH = 659

impl = data[OFFSET:OFFSET+LENGTH+1]

result = ''
for c in impl:
	t = '\\x%02x' % (ord(c) ^ 0x66)
	result += t

result = 'const char verify_password_b[] = "%s";' % result

with open('flagvault.injectable.c', 'rb') as f:
	code = f.read()

code = code.replace('const char verify_password_b[] = "";', result)

with open('flagvault.injected.c', 'wb') as f:
	f.write(code)
