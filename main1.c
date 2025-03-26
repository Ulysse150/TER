/*-*- compile-command: "cc -c -o com.o -g -O3 -Wall -fomit-frame-pointer -fno-strict-aliasing -fPIC -I\"/usr/include/x86_64-linux-gnu\" com.c && cc -o com.so -shared -g -O3 -Wall -fomit-frame-pointer -fno-strict-aliasing -fPIC -Wl,-shared -Wl,-z,relro com.o -lc -lm -L/usr/lib/x86_64-linux-gnu -lpari"; -*-*/
#include "proofProtocol.h"
#include <pari/pari.h>
#include <stdlib.h>
#include <time.h>
#include "utilities.h"
#include <time.h>


/*
GP;install("init_test","v","init_test","./com.so");
GP;install("pgcd","D0,G,D0,G,","pgcd","./com.so");
GP;install("generateurs","D0,G,D0,G,","generateurs","./com.so");
*/
void init_test(void);
GEN pgcd(GEN a, GEN b);
GEN generateurs(GEN p, GEN n);
/*End of prototype*/

void
init_test(void)	  /* void */
{
  return;
}

/*On va pour le moment travailler
avec le groupe G = (+, (Z/pZ))
Ses générateurs sont les  pgcd(n, p) = 1
*/


/* Renvoie Mod(i, n)*/
GEN modulo(int i, int n){
  return gmod(stoi(i), stoi(n));
}


GEN pgcd(GEN a, GEN b)
{
  if (gequal0(b))
    return a;
  return pgcd(b, gmod(a, b));
}

/*  Génère   n générateurs de (Z/pZ) +  */
GEN generateurs(GEN p, GEN n)	  /* vec */
{
  GEN p1;	  /* vec */
  {
    long i;
    p1 = cgetg(gtos(n)+1, t_VEC);
    for (i = 1; gcmpsg(i, n) <= 0; ++i)
      gel(p1, i) = gmodulo(gaddsg(1, genrand(gsubgs(p, 1))), p);
  }
  return p1;
}

int main(int argc, char *argv[]){

  pari_init(1000000, 2); // Initialize PARI with memory allocation
  /*Dans cette seed g= (3, 4)
    et h = (4, 2 )   (Modulo 5)
  */

  pari_ulong seed = (pari_ulong)time(NULL);

    // Convertir la graine en un objet GEN
    GEN seed_gen = utoi(seed);

    // Définir la graine du générateur aléatoire
    setrand(seed_gen);

    // Générer un nombre aléatoire avec genRand
   

    /*Ici on va dire u =  0*/
  GEN u = gmodulo(stoi(0), stoi(5));

  Group *zpZ = initZpZ(15, ADD);

 /* GEN g = generateurs(p, n);
  GEN h = generateurs(p, n);*/

  GEN g = mkvec2(gmodulo(stoi(3), stoi(5)), gmodulo(stoi(2), stoi(5)));
  GEN h = mkvec2(gmodulo(stoi(4), stoi(5)), gmodulo(stoi(3), stoi(5)));


  //pari_printf("g = %Ps\n", g);
  //pari_printf("h = %Ps\n", h);

  GEN a = initListModulo(5, 4, 2, -1);
  GEN b = initListModulo(5, 1, 4, -1);


  //pari_printf("a = %Ps\n", a);
 //pari_printf("b = %Ps\n", b);

  //GEN c = dot(a, b);

  //pari_printf("<a,b>=c= %Ps\n", c);

  //pari_printf("g^a = %Ps\n",powerG(g, a));
 
  //pari_printf("h^b = %Ps\n", powerG(h, b));
  
  

  
  


 
  int affiche;
  if (argc > 1){
    affiche = atoi(argv[1]);
  }else{
    affiche = 0;
  }
  


 /*pari_printf("%Ps\n", zpZ->pow(stoi(7), stoi(4))); */
 

  int p = 17; 
  int n = 8;

  Group *G = initZpZ(p, ADD);

  g = initListModulo(17, 4, 5, 7, 8, 9, 12, 13, 15, -1);
  h = initListModulo(17, 7, 2, 3, 4, 12, 1, 14, 16, -1);

  a = initListModulo(17, 4, 5, 6, 2, 1, 5, 9, 15, -1);
  b = initListModulo(17, 3, 7, 8, 16, 4, 3, 2, 7, -1);
  u = gmodulo(stoi(10),stoi(17));
  GEN P = buildP(G, g, h, a,b, u);

  //P = gmodulo(stoi(4), stoi(17));

  //pari_printf("P = %Ps\n", P);

  prover *bob = initProver(g,h,u,P,a,b,G);
  verifieur *alice = initVerifieur(g,h,u,P,G);


  result output = zeroKnowledgeProof(bob, alice, G, 8, 17, affiche);
  //printf("Result = %s\n", Char(output) );
  
  /*

  pariprintf("g^a = %Ps  h^b = %Ps", powerVector(G, g, a), powerVector(G, h, b));


  P = G->mul(powerVector(G, g, a), powerVector(G, h, b));
  u = gmodulo(stoi(10),stoi(17));

  

 //result tent1 = zeroKnowledgeProof(bob,alice, G, n, p);

  pari_printf("g = %Ps\n", g);
  pari_printf("h = %Ps\n", h);

  pari_printf("g^u = %Ps\n", powerSingle(G, g, u));

  pari_printf("g + h = %Ps\n", addVectors(g, h));
  pari_printf("g * h = %Ps\n", prodVectors(g, h));

  //pari_printf("%Ps\n", power(zpZ, x, y));
  printf("-----------------------------------------\n");
  printf("-----------------------------------------\n");


  Group *G2 = initZpZ(11, ADD);

  g = initListModulo(11, 4, 3, 1, 5,  -1);
  a = initListModulo(11, 2, 3, 4, 5,  -1);

  

  //g^a = Mod(2, 11)
  //h^b = Mod(10, 11)
  // c = dot(a,b) = Mod(2, 11)
  // u^c = Mod(3, 11)

  h = initListModulo(11, 7, 9, -1);
  b = initListModulo(11, 9, 8, -1);


  g = initListModulo(11, 4, 3,  -1);
  a = initListModulo(11, 2, 3,   -1);

  //g^a = Mod(2, 11)
  //h^b = Mod(10, 11)
  // c = dot(a,b) = Mod(2, 11)
  // u^c = Mod(3, 11)

  h = initListModulo(11, 7, 9,  -1);
  b = initListModulo(11, 9, 8, -1);


 

  u = gmodulo(stoi(0), stoi(11));
  
  GEN  P2 = buildP(G2, g, h, a, b, u);
  
  pari_printf("P2 = %Ps\n", P2);

  prover *bob = initProver(g,h,u,P2,a,b,G2);
  verifieur *alice = initVerifieur(g,h,u,P2, G2);

  result output = zeroKnowledgeProof(bob, alice, G2, 2, 11);
  printf("Result = %s\n", Char(output) );*/
  

   //Code Généré par pari
  pari_close(); // Clean up PARI resources
 return 0;
}