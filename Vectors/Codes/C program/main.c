#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include "lib.h"

int main()

{
 double **a,**b,**c,**f,**g,**h, **l,**R,**e1,**e2,**e3,**A,**B,**C;//declaring variables
 int m=3,n=1,p;

 e1=loadtxt("e1.dat",m,n); //e1=[1 0 0] 
 e2=loadtxt("e2.dat",m,n); //e2=[0 1 0]
 e3=loadtxt("e3.dat",m,n); //e3=[0 0 1] 


a=cross_prod(e2,e3);//cross product of e2 and e3
b=cross_prod(e1,e3);//cross product of e3 and e1
c=cross_prod(e1,e2);//cross product of e1 and e2


f=transpose(e1,m,n);
g=transpose(e2,m,n);
h=transpose(e3,m,n);

A = matmul(f,a,1,3,1);//dot product of e1 and a
B = matmul(g,b,1,3,1);//dot product of e2 and b
C = matmul(h,c,1,3,1);//dot product of e3 and c
//finding the result
l = linalg_add(A,B,n,n);
R = linalg_add(l,C,n,n);

//printing the result
print(R,1,1);

 return 0;
}
