#!/usr/bin/env python
# -*- coding: utf-8 -*-

def mergesort(l):
	if len(l) <= 1:
		return l
	else:
		return merge(mergesort(l[:len(l)/2]), mergesort(l[len(l)/2:]) )

def merge(ll, rl):
	tmp = []
	while len(ll) and len(rl):
		if ll[0] <= rl[0]:
			tmp.append(ll[0])
			del ll[0]
		else:
			tmp.append(rl[0])
			del rl[0]
	while len(ll):
		tmp.append(ll[0])
		del ll[0]
	while len(rl):	
		tmp.append(rl[0])
		del rl[0]			
	return tmp

l = [6, 6, 5, 10, 2, 3, 2, 4, 6, 1]
print l
print mergesort(l)
