def pow2(n):
    print(' '*5,end='')
    print(('{0: <5}'.format('2'))*(n+5))
    print(' '*2,end='')
    for i in range(-5,n+1):
        print('{0: <5}'.format(str(i*2+1)),end="")
    print()
    
    for j in range(-5,n+2):
        print('{0: <5}'.format(str(j**2)),end="") #Треугольники квадратов

#pow2(int(input()))
def powM(m,n):
    sp=[]
    for i in range(-4,n):
        sp1=[]
        for k in range(-4,m-i+1):
            if i==-4:
                sp1.append(k**n)
            else:
                sp1.append(sp[i+3][k+4]-sp[i+3][k+3])
        sp.append(sp1)
    for i in range(n,0,-1):
        print(sp[i-1])                          #Треугольники n степени
#powM(int(input()),int(input()))

def powT(n):
    sp=[]
    a=b=0
    for i in range(n+1):
       sp1=[]
       if i%2: a+=1
       else: b+=1
       c=-n+1+a
       d=n+1-b
       
       for k in range(c,d):
           if len(sp)==0:
               sp1.append(k**n)
           else:
               print(i-a,k+d-1)
               sp1.append(sp[i-a][k+d-1]-sp[i-a][k+d-2])
       sp.append(sp1)
       print(sp[i])
powT(5)
def powL(m,n):
    sp=[]
    for i in range(-4,n):
        sp1=[]
        for k in range(-4,m-i+1):
            if i==-4:
                sp1.append(k**n)
            else:
                sp1.append(sp[i+3][k+4]-sp[i+3][k+3])
        sp.append(sp1)
    for i in range(5,6):
        M=abs(sp[i][0])
        for j in sp[i]: M=min(M,abs(j))
    return M
for d in range(7,25,2):
   sp=[]
   n=powL(d,d)
   r=n
   if d%2==1: n=n//6
   else: n=n//12
   for i in range(2,n+1):
       while n%i==0:
           sp.append(i)
           n=n//i
   print(d,r,sp)
