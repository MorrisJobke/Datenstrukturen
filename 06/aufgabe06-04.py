#!/usr/bin/env python
# -*- coding: utf-8 -*-

A = 0
C = 1
D = 2
F = 3
G = 4
L = 5
R = 6
S = 7
Z = 8

t = ["A", "C", "D", "F", "G", "L", "R", "S", "Z"]

a = [[0 for j in range(9) ] for i in range(9)]

a[A][C] = a[C][A] = 15
a[C][F] = a[F][C] = 30
a[C][G] = a[G][C] = 10
a[C][R] = a[R][C] = 25
a[C][S] = a[S][C] = 10
a[C][Z] = a[Z][C] = 30
a[D][F] = a[F][D] = 20
a[D][R] = a[R][D] = 15
a[G][L] = a[L][G] = 40
a[G][R] = a[R][G] = 10
a[L][R] = a[R][L] = 20
a[S][Z] = a[Z][S] = 10

print
print "%7s %4s %4s %4s %4s %4s %4s %4s %4s"%tuple(t)
for i in range(9):
	print "%2s %4i %4i %4i %4i %4i %4i %4i %4i %4i"%tuple([t[i]] + a[i])
	
print

for i in range(9):
	for j in range(9):
		for k in range(9):
			if a[j][i] and a[i][k] and a[j][k]:
				if a[j][i] + a[i][k] < a[j][k]:
					a[j][k] = a[j][i] + a[i][k]
					a[k][j] = a[j][i] + a[i][k]
					
print "%7s %4s %4s %4s %4s %4s %4s %4s %4s"%tuple(t)
for i in range(9):
	print "%2s %4i %4i %4i %4i %4i %4i %4i %4i %4i"%tuple([t[i]] + a[i])
	
