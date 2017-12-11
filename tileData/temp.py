stuff = 'q,q,l,m,o,m,l,j,i,g,e,d,e,e,e,e,e,e,e,e,e,d,h,j,k,m,m,m,m,m,k,i,k,k,k,k,s,x,x,w,v,y,ab,ag,ai,al,aq,ao,an,at,bc,bc,ba,au,at,ao,an,ag,af,v,u,s'.split(',')

for line in stuff:
	tot = 0
	str = line.strip()
	for i in range(len(str)):
		tot *= 26
		c = str[i]
		tot += ord(c) - ord('a') + 1 
	print(tot - (ord('d')-ord('a') + 1))