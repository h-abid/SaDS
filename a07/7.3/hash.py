
import itertools
import csv


def power(x):
	for i in range(1234567):
		x *= x
		x %= 993201131
	return x;


def hash(x):
	parts = [ord(ch) for ch in x]

	h = 0
	for i in range(len(parts)):
		# h = pow(h + 2 + parts[i], 1234567) % 9993201131
		h = power(h + 2 + parts[i])
	return h

if __name__ == '__main__':
	x = 'thisisastring'
	chars = "abcdefghijklmnopqrstuvwxyz"
	count = 8

	i = 0
	passwords = []
	for item in itertools.product(chars, repeat=count):
		# print("".join(item))
		passwords.append("".join(item))
		i = i + 1
		if i == 250:
			break
	print(passwords)

	table = {}
	for p in passwords:
		h = hash(p)
		print "password: ", p, " hash: ", h
		table[h] = p
	w = csv.writer(open("passes.csv", "w"))
	for key, val in table.items():
		w.writerow([key, val])

