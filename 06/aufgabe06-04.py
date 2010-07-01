#!/usr/bin/env python
# -*- coding: utf-8 -*-

from pprint import pprint

A = 0
C = 1
D = 2
F = 3
G = 4
L = 5
R = 6
S = 7
Z = 8

a = [[999 for j in range(9) ] for i in range(9)]

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

pprint(a)

for i in range(9):
	for j in range(9):
		for k in range(9):
			#print a[j][i] + a[j][k], a[j][k]
			if a[j][i] + a[j][k] < a[j][k]:
				#print "g"
				a[j][k] = a[j][i] + a[j][k]
				a[k][j] = a[j][i] + a[j][k]

pprint(a)
