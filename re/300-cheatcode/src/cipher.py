#!/usr/bin/env python2

FLAG = 'BSidesPDX{i_am_4_c0ns0l3_h4ck3r_n0w!_96041347b}'
FLAG = 'BSidesPDX{c0ns0l3s_ar3_jU57_c0MPU73rS_th3Y_d0Nt_wAnT_YOU_2_wr1t3_c0d3_f0r!}'
XKEY = '\x01\x04\xff\xff\x02'

KEY_A     = 1 << 0
KEY_B     = 1 << 1
KEY_DDOWN = 1 << 15
KEY_DUP   = 1 << 13
KEY_DLEFT = 1 << 12
KEY_DRIGHT = 1 << 14

CHEAT_CODE = [KEY_DDOWN, KEY_DUP, KEY_DUP, KEY_DLEFT, KEY_DLEFT, KEY_A, KEY_A, KEY_DRIGHT, KEY_B, KEY_DDOWN, KEY_DLEFT]
CHEAT_CODE_KEY = []

"""
for c in CHEAT_CODE:
	val = 0
	for i in range(0,32,4):
		temp = (c >> i) & 0xff
		if temp == 0x00:
			continue
		val = temp
	CHEAT_CODE_KEY.append(val)
"""
for c in CHEAT_CODE:
	i = 0
	while i <= 32:
		tmp = (c >> i) & 0xff
		if tmp != 0x00:
			print('0x%x' % tmp)
			CHEAT_CODE_KEY.append(tmp)
			break
		i = i + 4


cipher_blocks = []
prev = -42
i = 0

for c in FLAG:
	r = ord(c) ^ CHEAT_CODE_KEY[i % 11]
	r = r ^ ord(XKEY[i % 5])
	cur = (r - i)*prev
	cipher_blocks.append(cur)
	i += 1
	prev = ord(c)

print(cipher_blocks)
print('length==%d' % len(cipher_blocks))
prev = -42
i = 0
result = ''
for b in cipher_blocks:
	print(result)
	r = b / prev
	r = r + i
	r = r ^ ord(XKEY[i % 5])
	r = r ^ CHEAT_CODE_KEY[i % 11]
	result += chr(r)
	prev = r
	i += 1

print(result)
