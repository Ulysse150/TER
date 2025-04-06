#ifndef utilities
#define utilities

#include <pari/pari.h>
#include <stdlib.h>
#include <stdarg.h>


GEN chooseX(int p);


GEN moduk(int a, int b);

/*   Prend une liste d'entiers
    l[0] l[1] ... l[n]
    et renvoie pour tout i > 0 l[i] modulo l[0]
    -1 est le dernier
*/
GEN initListModulo(int p ,...);
GEN initListModulo2(GEN p1, int p, ...);

/* Here we suppose we are talking about vectors of Z/pZ  */

/* Adds two vectors of same size*/
GEN addVectors(GEN x, GEN y);


/* Multiplies two vectors of same size*/
GEN prodVectors(GEN x, GEN y);





/* Multiplies a vector by a constant*/
GEN mulConstante(GEN x, GEN alpha);


/* Creates a P and 

    from g,h,a, b, and U
    c = dot(a,b)
    such as P = g^a * h^b * u ^c
*/

#endif