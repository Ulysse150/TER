#include "group.h"


static Loi statLoi;
static GEN statOne;

Group *initGroup(Loi loi, GEN one){

    Group *G = (Group*)malloc(sizeof(Group));


    G->mul = loi;
    G->one = one;
   

   



    return G;
}




Group *initZpZ(int p, loiComp l){


    switch (l) {
        case ADD : 
            return initGroup(gadd, gmodulo(stoi(0), stoi(p)));
            break;
        case MUL: 
            return initGroup(gmul, gmodulo(stoi(1), stoi(p)));
            break;
    }
}

GEN Mod(int i, int p){
    return gmodulo(stoi(i), stoi(p));
}



GEN power(Group *g, GEN x, GEN y){
    GEN output = g->one;

    GEN i = gen_0;
    GEN y_lifted = lift(y);


    while (gcmp(i, y_lifted) == -1){
        output = g->mul(output, x);
        i = gadd(i, gen_1);
    }
    

    return output;

}

GEN powerVector(Group *g, GEN a, GEN b){
    GEN output = g->one;
    GEN current;

    int N = lg(a) - 1;


    for (int i = 1; i <= N ; i++){
        current = power(g, gel(a, i),gel(b, i));
        output = g->mul(output, current);
    }


    return output;
}


GEN powerSingle(Group *g, GEN x, GEN y){
    long size = lg(x) - 1;

    GEN output = cgetg(size+1, t_VEC);

    for (int i = 1; i <= size; i++){
        gel(output, i) = power(g, gel(x,i), y);
    }
    return output;
}


GEN mulVectors(Group *groupe, GEN x, GEN y){
    long size = lg(x) - 1;

    Loi mul = groupe->mul;
    GEN output = cgetg(size+1, t_VEC);
    for (int i = 1; i <= size; i++){
        gel(output, i) = mul(gel(x, i) , gel(y, i));

    }

    return output;
}

