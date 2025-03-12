#include "proofProtocol.h"
#include <stdlib.h>
#include "utilities.h"

result intResult(int i){
    switch (i % 2){
        case 0 : return REJECT; break;
        case 1 : return ACCEPT; break;
        default : return ACCEPT; break;
    }

}

char* Char(result r) {
    switch (r) {
        case 0: return "REJECT";
        case 1: return "ACCEPT";
        default: return "UNKNOWN";  // Gérer les cas non prévus
    }
}






prover *initProver( GEN g, GEN h,GEN u, GEN P,GEN a,GEN b, Group *groupe){
    /*On alloue un proveur*/

    prover *ptr = (prover*)malloc(sizeof(prover));

    /*Et on lui donne ses variables*/
    ptr->g = g; ptr->h = h;
    ptr->u = u; ptr->P = P;
    ptr->a = a; ptr->b = b;
    ptr->groupe = groupe;

    return ptr;

}

verifieur *initVerifieur(GEN g, GEN h, GEN u, GEN p,  Group *groupe){
    /*On alloue un vérifieur*/
    verifieur *ptr = (verifieur*)malloc(sizeof(verifieur));

    /*Et on lui donne ses variables*/
    ptr->g = g; ptr->h = h;
    ptr->u = u; ptr->P = p;
    ptr->groupe = groupe;

    return ptr;
}
/* Calcule le produit scalaire de deux vecteurs */
GEN dot(GEN x, GEN y){
  long l1;
  GEN p2;
  l1 = glength(x);
  {
    long i;
    p2 = gen_0;
    for (i = 1; i <= l1; ++i)
      p2 = gadd(p2, gmul(gel(x, i), gel(y, i)));
  }
  return p2;
}




/*
Calcule g^a  
ou g[0]*a[0] + ... g[n] * a[n]
Comme on est en loi additive
*/
GEN powerG(GEN g, GEN a){
  long l1;
  GEN p2;
  l1 = glength(g);
  {
    long i;
    p2 = gen_0;
    for (i = 1; i <= l1; ++i)
      p2 = gadd(p2, gmul(gel(g, i), gel(a, i)));
  }
  return p2;
}


/*La partie finale de la preuve*/
result check(verifieur *v,GEN a, GEN b,GEN g, GEN h, GEN P){
    /*Calcule dans un premier temps c*/

    
    GEN c = dot(a, b);
    
    Loi mul = v->groupe->mul;


    /*On calcule g^a *h^b *u^c */
    GEN gauche = powerVector(v->groupe, g, a);
   
    GEN droite = powerVector(v->groupe, h, b);
    GEN fin = power(v->groupe, v->u, c);

    GEN prod = mul(gauche, mul(droite,fin));
    /*On verifie que prod  egal a P*/


    return intResult(gequal(prod, P));

}

result test(int i){
    return REJECT;
}


void
init_split(void)	  /* void */
{
  return;
}

/*  This code section is used to split vectors in two

We suppose they are 2n lenght, meaning the vectors left, right have the same size
*/



/* Selectionne

x[begin :  end] (Compris)
*/
GEN getSubPart(GEN x, GEN begin, GEN end)	  /* vec */
{
  GEN p1;
  GEN p2;	  /* vec */
  p1 = gaddgs(gsub(end, begin), 1);
  {
    long i;
    p2 = cgetg(gtos(p1)+1, t_VEC);
    for (i = 1; gcmpsg(i, p1) <= 0; ++i)
      gel(p2, i) = gcopy(gel(x, gtos(gsubgs(gaddsg(i, begin), 1))));
  }
  return p2;
}

/*  Takes a vector and splits in half, left and right   */
GEN split(GEN x){
  GEN n;
  GEN p1;	  /* vec */
  n = stoi(glength(x)/2);
  p1 = cgetg(3, t_VEC);
  gel(p1, 1) = getSubPart(x, gen_1, n);
  gel(p1, 2) = getSubPart(x, gaddgs(n, 1), stoi(glength(x)));
  return p1;
}

/* Takes a vector and return its left part  */
GEN left(GEN x)
{
  return gel(split(x), 1);
}

/* Takes a vector and return its right part  */
GEN right(GEN x)
{
  return gel(split(x), 2);
}


GEN proverfirstComputation(prover *bob, GEN a, GEN b, GEN g, GEN h, int affiche){


    Loi mul = bob->groupe->mul;
    
    GEN leftA = left(a); GEN rightA = right(a);
    GEN leftB = left(b); GEN rightB = right(b);

    GEN leftG = left(g); GEN rightG = right(g); 
    GEN leftH = left(h); GEN rightH = right(h);
  
    if (affiche){

      pari_printf("a = %Ps\n", a);
      pari_printf("b = %Ps\n", b);

      pari_printf("g = %Ps\n", g);
      pari_printf("h = %Ps\n", h);
    }

    GEN cl = dot(leftA, rightB); GEN cr = dot(rightA, leftB);



    GEN L1 = powerVector(bob->groupe, rightG, leftA);
    GEN L2 = powerVector(bob->groupe, leftH,rightB );
    GEN L3 = power(bob->groupe, bob->u, cl);

    GEN L = mul(L1, mul(L2, L3));

    GEN R1 = powerVector(bob->groupe, leftG, rightA);
    GEN R2 = powerVector(bob->groupe,rightH, leftB );
    GEN R3 = power(bob->groupe, bob->u, cr);
   
    
    GEN R = mul(R1, mul(R2, R3));

    return mkvec2(L, R);
}


GEN verifierChooseX(int p){

    GEN n = gadd(gen_1, genrand(stoi(p-1)));
    return gmodulo(n, stoi(p));

   
}


GEN proversecondComputation(prover *bob, GEN a, GEN b, GEN x, int affiche){





  GEN x1 = x;
  GEN invX = gpow(x1, stoi(-1), 1);
  
  if (affiche){
    pari_printf("a = %Ps\n", a);
    pari_printf("b = %Ps\n", b);
    pari_printf("x = %Ps\n", x);
    pari_printf("x^-1 = %Ps\n", invX);
  }

  GEN leftA = left(a);
  GEN rightA = right(a);
  GEN leftB = left(b);
  GEN rightB = right(b);

  


  GEN a2 = addVectors(mulConstante(leftA,x1), mulConstante(rightA,invX));
  GEN b2 = addVectors(mulConstante(leftB,invX), mulConstante(rightB,x1));

  
  return mkvec2(a2, b2);
}

GEN computationCommon(Group *G, GEN L, GEN R, GEN P, GEN g, GEN h, GEN x, int affiche){

  GEN invX = gpow(x, stoi(-1), 1);

  GEN leftG = left(g); GEN rightG = right(g);

  GEN leftH = left(h); GEN rightH = right(h);


  
  GEN g2 = mulVectors(G, powerSingle(G, leftG, invX ), powerSingle(G, rightG, x));
  
  GEN h2 = mulVectors(G, powerSingle(G, leftH, x ), powerSingle(G, rightH, invX));
  if (affiche){
    pari_printf("g = %Ps\n",g);
    pari_printf("g2 = %Ps\n",g2);
    pari_printf("h = %Ps\n",h);
    pari_printf("h2 = %Ps\n",h2);
  }
  
  Loi mul = G->mul;

  GEN xCarre = gpow(x, stoi(2), 1);
  GEN xCarreInv = gpow(xCarre, stoi(-1), 1);

  GEN leftSquare = power(G, L, xCarre);
 

  GEN rightSquare = power(G, R, xCarreInv);


  GEN P2 = mul(leftSquare, mul(P, rightSquare));
  return mkvec3(g2, h2, P2);

}

result protocolRecursive(prover *bob, verifieur *alice, GEN g, GEN h, GEN u, GEN P, GEN a, GEN b, int n ,int p, int affiche){
  if (n == 1){ //Cas de base
    if (affiche){
      printf("-----------------------------------------\n");
      printf("Vérification finale sur  :");
      pari_printf("a = %Ps, b = %Ps, g = %Ps h= %Ps u = %Ps P =%Ps\n",
          a,b,g,h,alice->u, P
      
      );
    }
    result r =  check(alice, a, b, g, h , P);
    if (affiche){
      printf("%s\n", Char(r));
    }
    return check(alice, a, b, g, h , P);
  }else{

    if (affiche){
      printf("-----------------------------------------\n");
      printf("Appel recursif protocol avec n = %d\n", n);
    }
    

    GEN leftRight = proverfirstComputation(bob, a, b, g, h, affiche);

    GEN L = gel(leftRight, 1); GEN R = gel(leftRight, 2);

    if (affiche){
      pari_printf("Prover a calculé L  = %Ps et R = %Ps\n", L, R);
    }

    GEN x = verifierChooseX(p);

    if (affiche){
      pari_printf("Le verifieur a choisi x = %Ps\n", x);
    }

    GEN common = computationCommon(bob->groupe, L, R, P, g, h, x, affiche);

    GEN g2 = gel(common, 1); GEN h2 = gel(common, 2); GEN P2 = gel(common, 3);

    if (affiche){
      pari_printf("Les calculs en communs on ete effectues.\n");
      pari_printf("Le proveur et le verifieur ont calcule : \ng' = %Ps \nh' = %Ps \nP' = %Ps\n", g2, h2, P2);
    }

    GEN ab = proversecondComputation(bob,a,b ,x, affiche );

    GEN a2 = gel(ab, 1); GEN b2 = gel(ab, 2);
      

    return protocolRecursive(bob, alice,g2, h2, u, P2, a2, b2 ,n/2,p, affiche);

}
}


result zeroKnowledgeProof(prover *bob, verifieur *alice, Group *groupe, int n, int p, int affiche){

  if (affiche){
    printf("Lancement protocole avec n = %d et p = %d\n", n, p);
  }
  
 
  return protocolRecursive(bob, alice, bob->g, bob->h, bob->u, bob->P, bob->a, bob->b, n, p, affiche);
}


GEN buildP(Group *G, GEN g, GEN h, GEN a, GEN b, GEN u){
  GEN G2 = powerVector(G, g, a);
  GEN c = dot(a, b);
  GEN G3 = powerVector(G ,h, b);
  GEN G4 = powerVector(G, u, c);
 

  return G->mul(G2, G->mul(G3, G4));

}

