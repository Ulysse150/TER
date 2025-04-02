#ifndef group
#define group


#include <pari/pari.h>
#include <stdlib.h>



typedef enum  {
    ADD = 0,
    MUL = 1
} loiComp;


// On definit ce qu est une loi de groupe
// C est à dire une fonction prennant GEN x, GEN y
// Et renvoyant une loi de groupe dessus ()
// Une loi est une fonction de signature (GEN, GEN) -> GEN
typedef GEN (*Loi)(GEN,GEN);

typedef struct{
    /*On definit un  groupe par sa loi de composition
        que j'ai décidé d'appeller mul  
    */
    Loi mul;
    GEN one;

   

} Group;





/* Initie un groupe selon sa loi*/
Group *initGroup(Loi loi, GEN one);

/*Definit la puissance a partir d'une loi */

/* Initie le groupe (Z/pZ) en loi addittive ou multiplicative*/
Group *initZpZ(int p, loiComp l);


/* Renvoie x^y  = x * ... * x  ) y fois
    y est un 

*/
GEN power(Group *g, GEN x, GEN y);


/*  
    Renvoie a1^b1 * ... * an ^ bn
    ou * est loi de groupe et
    a = [a1, ..., an]
    b = [b1, ... , bn]

*/
GEN powerVector(Group *g, GEN a, GEN b);

/* Renvoie [x1^y, x2^y, .., xn^y]
    ou x = [x1, x2 , ..., xn]


*/
GEN powerSingle(Group *g, GEN x, GEN y);


/* Renvoie i mod p*/
GEN Mod(int i, int p);

/** Takes 2 vectors x and y and multiplies them
 * output[i] = x[i] * y[i]
 * 
 * 
 */
GEN mulVectors(Group *group, GEN x, GEN y);

#endif
