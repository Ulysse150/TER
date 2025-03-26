#include "elliptic.h"


GEN
courbe(GEN a, GEN b, GEN p, long prec)
{
  GEN p1;	  /* vec */
  p1 = cgetg(3, t_VEC);
  gel(p1, 1) = gcopy(a);
  gel(p1, 2) = gcopy(b);
  return ellinit(p1, p, prec);
}


/*Loi initLoi(GEN a, GEN b, GEN p, long prec)
{
    GEN a1 = stoi(a);
    GEN b2 = stoi(b);
    GEN p2 = stoi(p);

    GEN E  = courbe(a, b, p, 1);
    

    GEN loi_addition(GEN P, GEN Q) {
        // Utilisation de elladd pour l'addition de points sur la courbe E
        return elladd(E, P, Q);
    }

    // Retourne la fonction de loi comme un pointeur de fonction
    return (Loi)loi_addition;
}*/



Group *initCourbe(int a, int b, int p){
    Group *gr = (Group*)(malloc(sizeof(Group)));

    gr->one = INFINI;






    return gr;
}