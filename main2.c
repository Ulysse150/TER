/*-*- compile-command: "cc -c -o com.o -g -O3 -Wall -fomit-frame-pointer -fno-strict-aliasing -fPIC -I\"/usr/include/x86_64-linux-gnu\" com.c && cc -o com.so -shared -g -O3 -Wall -fomit-frame-pointer -fno-strict-aliasing -fPIC -Wl,-shared -Wl,-z,relro com.o -lc -lm -L/usr/lib/x86_64-linux-gnu -lpari"; -*-*/
#include "proofProtocol.h"
#include <pari/pari.h>
#include <stdlib.h>
#include <time.h>
#include "utilities.h"
#include <time.h>


GEN courbe(GEN a, GEN b, GEN p, long prec)
{
  GEN p1;	  /* vec */
  p1 = cgetg(3, t_VEC);
  gel(p1, 1) = gcopy(a);
  gel(p1, 2) = gcopy(b);
  return ellinit(p1, p, prec);
}



GEN E;


GEN loi(GEN x, GEN y){
    return elladd(E, x, y);
}

void init_nul(void);
/*End of prototype*/

static GEN o;
/*End of global vars*/

void init_nul(void)	  /* void */
{
  GEN p1;	  /* vec */
  o = pol_x(fetch_user_var("o"));
  p1 = cgetg(2, t_VEC);
  gel(p1, 1) = gen_0;
  o = p1;
  return;
}


Group *initCourbe(int a, int b, int p, GEN *ptr){
    E = courbe(stoi(a), stoi(b), stoi(p), 1);
    *ptr = E;
    Group *G = (Group*)malloc(sizeof(Group));
    init_nul();
    G->one = o;
    G->mul = loi;
    return G;

}


/* Return the repetition of additive law on x done n times */
GEN pointPower(GEN E, GEN x, int n){
    
    GEN output = o;
    for(int i = 0; i < n; i++){
      output = elladd(E, x, output);
    }
    return output;
}



/* Will return  n points from elliptic curve*/
GEN genPoints(GEN courbe, int n){
  GEN gens = ellgenerators(courbe);
  

  GEN output = cgetg(n+1, t_VEC);
  GEN gen = gel(gens, 1);
  //pari_printf("gen = %Ps\n", gen);

  pari_printf("%Ps  \n", gen);

  for(int i = 1; i <= n; i++){
    GEN ind =  gadd(gen_1, genrand(stoi(n-1)));
    long entier  = itos(ind);
    pari_printf("i = %d ind = %Ps x = %Ps\n",i, ind, pointPower(courbe, gen , entier) );
    gel(output, i) = pointPower(courbe, gen , entier);
  }
 
  return output;
}

int main(int argn,char *argv[]){
    pari_init(1000000, 2); // Initialize PARI with memory allocation

    // to get real random values
    pari_ulong seed = (pari_ulong)time(NULL);

    // Convertir la graine en un objet GEN
    GEN seed_gen = utoi(seed);

    // Définir la graine du générateur aléatoire
    setrand(seed_gen);
    
    //testing the algorithm on elliptic curves

    Group *groupe = initCourbe(14, 15, 101, &E);
    pari_printf("%Ps\n",E);

    GEN n = stoi(16);

    GEN g = genPoints(E, 8);
    GEN h = genPoints(E, 8);


    GEN a = initListModulo(17, 4, 5, 6, 2, 1, 5, 9, 15, -1);
    GEN b = initListModulo(17, 3, 7, 8, 16, 4, 3, 2, 7, -1);
   

    GEN u = mkvec2(gmodulo(stoi(7), stoi(101)),   gmodulo(stoi(70), stoi(101)));

    pari_printf("g = %Ps\n", g);
    pari_printf("a = %Ps\n", a);
    GEN c = dot(a, b);
    u = mkvec(gel(h, 3));
    pari_printf("u = %Ps  c = %Ps \n", u, c);

    //GEN z = powerSingle(groupe, u, c);
   
   


    //pari_printf("z1 = %Ps\n z2 = %Ps\n",z1, z2);
    //pari_printf("Hello world g = %Ps!\n",g);
   GEN P = mkvec(buildP(groupe, g, h, a,b, u));


    prover *bob = initProver(g,h,u,P,a,b,groupe);
    verifieur *alice = initVerifieur(g,h,u,P,groupe);

    result output = zeroKnowledgeProof(bob, alice, groupe, 8, 17, 1);

   


    pari_close();

}
