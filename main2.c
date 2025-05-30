
/*-*- compile-command: "cc -c -o com.o -g -O3 -Wall -fomit-frame-pointer -fno-strict-aliasing -fPIC -I\"/usr/include/x86_64-linux-gnu\" com.c && cc -o com.so -shared -g -O3 -Wall -fomit-frame-pointer -fno-strict-aliasing -fPIC -Wl,-shared -Wl,-z,relro com.o -lc -lm -L/usr/lib/x86_64-linux-gnu -lpari"; -*-*/
#include "proofProtocol.h"
#include <pari/pari.h>
#include <stdlib.h>
#include <time.h>
#include "utilities.h"
#include <time.h>
#include <math.h>



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


Group *initCourbe(GEN a, GEN b, GEN p, GEN *ptr){
    E = courbe(a, b, p, 1);
    *ptr = E;
    Group *G = (Group*)malloc(sizeof(Group));
    init_nul();
    G->one = o;
    G->mul = loi;
    return G;

}











/* Will return  n points from elliptic curve*/

GEN genPoints(Group *G, GEN gen, int n){
 
  

  GEN output = cgetg(n+1, t_VEC);
  //pari_printf("gen = %Ps\n", gen);

  GEN ind;
  for(int i = 1; i <= n; i++){
    ind =  gadd(gen_1, genrand(stoi(n-1)));
    
    gel(output, i) = power2(G, gen, ind);
    //gel(output, i) = mkvec2(gmodulo(stoi(41), stoi(101)), gmodulo(stoi(41), stoi(101)));
  }
  //free(&ind);
  return output;
}

/* Return n random numbers in (Z/pZ)*    */
GEN genZpz(GEN p, int n){

  GEN output = cgetg(n+1, t_VEC);
  GEN ind;
  for (int i = 1; i <=n; i++){
    ind =  gadd(gen_1, genrand(p));
    gel(output, i) = gmodulo(ind, p);
  }
  return output;

}

/*Returns the g, h, a, b, u, and P in a vector

for the parameters 
*/
GEN initParameters(int length, Group *G, GEN gen, GEN ordre){

    GEN a1 = genZpz(ordre, length);
    GEN b1 = genZpz(ordre, length);

    GEN g = genPoints(G, gen, length);
    GEN h = genPoints(G, gen, length);

   
    GEN u = gel(g, 2);
    GEN P = buildP(G, g, h, a1, b1, u);

    GEN output = cgetg(7, t_VEC);
    gel(output, 1) = a1;
    gel(output, 2) = b1;

    gel(output, 3) = g;
    gel(output, 4) = h;

    gel(output, 5) = u;
    gel(output, 6) = P;

    return output;

}


int main(int argn,char *argv[]){
    pari_init(2000000000, 2); // Initialize PARI with memory allocation

    // to get real random values
    pari_ulong seed = (pari_ulong)time(NULL);

    // Convertir la graine en un objet GEN
    GEN seed_gen = utoi(seed);



    // Définir la graine du générateur aléatoire
    setrand(seed_gen);
    



   int p = 100;

    GEN y = moduk(7, 17);
    GEN x = moduk(9, 29);
   


     GEN p1 = strtoi("0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff");
     GEN a = gmodulo(strtoi("0xffffffff00000001000000000000000000000000fffffffffffffffffffffffc") ,p1);
     GEN b = gmodulo(strtoi("0x5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b"), p1);
    


    
     GEN Gx = gmodulo(strtoi("0x6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296"), p1);
     GEN Gy = gmodulo(strtoi("0x4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5"), p1);

    GEN generateur = mkvec2(Gx, Gy);
    GEN ordre = strtoi("115792089210356248762697446949407573529996955224135760342422259061068512044369");
    
   

    
    Group *zpz = initZpZ(ordre,  ADD);

    Group *groupe = initCourbe(a, b, p1, &E);

    GEN g = genPoints(groupe, generateur, 4);
    GEN h = genPoints(groupe, generateur, 4);


    GEN a1 = initListModulo2(ordre, 47, 85, 145, 475,  -1);
    GEN b1 = initListModulo2(ordre, 47, 85, 145, 142,  -1);
   
    a1 = mkvec4(gmodulo(stoi(47), ordre), gmodulo(stoi(85), ordre),gmodulo(stoi(47), ordre),gmodulo(stoi(40), ordre)
  
  );

  b1 = mkvec4(gmodulo(stoi(47), ordre), gmodulo(stoi(85), ordre),gmodulo(stoi(47), ordre),gmodulo(stoi(40), ordre)
  
  );


    GEN u = gel(g, 2);

    GEN P = buildP(groupe, g, h, a1, b1, u);

  
    int puissance;

    if (argn == 1){
      puissance = 6;
    }else{
      puissance = atoi(argv[1]);
    }    

    int longueur = 1;
    for (int i = 0; i < puissance; i++){
        longueur = 2 * longueur;
     }

   
    pariprintf("Simulation avec p = %d, générateurs de taille %d\n", puissance, longueur);
   
    clock_t start =  clock();
    GEN parameters = initParameters(longueur, groupe, generateur, ordre);
    clock_t end = clock();


    a1 = gel(parameters, 1); b1 = gel(parameters, 2); 
    g = gel(parameters, 3) ; h = gel(parameters, 4);
    u = gel(parameters, 5)  ; P = gel(parameters, 6);

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Paramètres générés en %f secondes: \n", time_taken);

    
    prover *bob = initProver(g,h,u,P,a1,b1,groupe);
    verifieur *alice = initVerifieur(g,h,u,P,groupe); 
   
    start = clock();
   result output = zeroKnowledgeProof(bob, alice, groupe,longueur,ordre, 0  );
   
   end = clock();
   time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    
  
    pariprintf("Resultat : %s calculé en : %f secondes\n" , Char(output), time_taken);
   

    printf("\n");
    pari_close();
    return 0;

}
