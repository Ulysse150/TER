#ifndef elliptic
#define elliptic

#include <pari/pari.h>
#include <stdlib.h>


#define INFINI mkcol(gen_0)
#include "group.h"

/* Cree un groupe pour une courbe elliptique
 * y^2 = x^3 +ax+b [p]
 *  
 */
Group *initCourbe(int a, int b, int p);


GEN
courbe(GEN a, GEN b, GEN p, long prec);



//Loi initLoi(int a, int b, int p);


#endif