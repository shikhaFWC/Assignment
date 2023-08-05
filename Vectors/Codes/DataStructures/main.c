#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include "lib.h"

int main() 
{
    Node *e1, *e2, *e3, *A, *B, *C, *l, *R,  *a, *b, *c, *f, *g, *h;
    int m = 3, n = 1, p;

e1 = loadtxt("e1.dat"); // e1=[1 0 0]
e2 = loadtxt("e2.dat"); // e2=[0 1 0]
e3 = loadtxt("e3.dat"); // e3=[0 0 1]

a=cross_prod1(e2,e3);// cross product of e2 and e3
 b = cross_prod1(e1, e3); // cross product of e3 and e1
 c = cross_prod1(e1, e2); // cross product of e1 and e2
 

    f = transpose(e1);
    g = transpose(e2);
    h = transpose(e3);

    A = matmul(f, a, m, n);
    B = matmul(g, b, m, n);
    C = matmul(h, c, m, n);
    // finding the result
    l = linalg_add(A, B);
    R = linalg_add(l, C);

    // printing the result
    print(R,1,1);


    return 0;
}

