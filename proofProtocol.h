#ifndef proofProtocol
#define proofProtocol


#include <pari/pari.h>
#include <stdlib.h>
#include "group.h"


typedef enum {
    REJECT = 0,
    ACCEPT = 1
} result;



typedef struct{
    GEN g;
    GEN h;
    GEN u;
    GEN P;
    GEN a;
    GEN b;

    Group *groupe;




} prover;
typedef struct{
    GEN g;
    GEN h;
    GEN u;
    GEN P;
    Group *groupe;


} verifieur;

/* Pour initier un prouveur */

prover *initProver( GEN g, GEN h,
    GEN u, GEN P,
    GEN a,GEN b, Group *groupe);



/* Alloue un verifieur */
verifieur *initVerifieur(GEN g, GEN h, GEN u, GEN p,Group *groupe);
result intResult(int i);
GEN dot(GEN x, GEN y);

/*
Calcule g^a  
ou g[0]*a[0] + ... g[n] * a[n]
Comme on est en loi additive
*/
GEN powerG(GEN g, GEN a);


/* Regarde le proveur et dit si
    P = g^a * h^b * u^c
*/
result check(verifieur *p,GEN a, GEN b , GEN g, GEN h ,GEN P);

char* Char(result r);
result test(int i);



void init_split(void);
GEN getSubPart(GEN x, GEN begin, GEN end);
GEN split(GEN x);
GEN left(GEN x);
GEN right(GEN x);


/* Is the first Computation of the proof
    The prover will take g,h a,b :

    cl = the dot product of left(a), right(b)
    cr = the dot product of right(a), left(b)
    then the prover sends 

    L = right(g)^left(a) *  left(h)^right(b) *  u^cl 
    R = left(g)^right(a) *  right(h)^left(b) *  u^cr
*/
GEN proverfirstComputation(prover *bob, GEN a, GEN b, GEN g, GEN h, int affiche);



GEN proversecondComputation(prover *bob, GEN a, GEN b, GEN x, int affiche);

/* Verifier decides and sends x  */
GEN verifierChooseX(int p);


GEN computationCommon(Group *G, GEN L, GEN R, GEN P, GEN g, GEN h, GEN x, int affiche);

result protocolRecursive(prover *bob, verifieur *alice, GEN g, GEN h, GEN u, GEN P, GEN a, GEN b, int n, int p, int affiche);

result zeroKnowledgeProof(prover *bob, verifieur *alice, Group *groupe, int n, int p, int affiche);


/* Creates a P and 

    from g,h,a, b, and U
    c = dot(a,b)
    such as P = g^a * h^b * u ^c
*/
GEN buildP(Group *G, GEN g, GEN h, GEN a, GEN b, GEN u);





#endif



