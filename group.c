#include "group.h"


static Loi statLoi;
static GEN statOne;

Group *initGroup(Loi loi, GEN one){

    Group *G = (Group*)malloc(sizeof(Group));


    G->mul = loi;
    G->one = one;
   

   



    return G;
}




Group *initZpZ(GEN p, loiComp l){


    switch (l) {
        case ADD : 
            return initGroup(gadd, gmodulo(stoi(0), p));
            break;
        case MUL: 
            return initGroup(gmul, gmodulo(stoi(1), p));
            break;
    }
}

GEN Mod(int i, int p){
    return gmodulo(stoi(i), stoi(p));
}





GEN powerRec(Loi mul, GEN x, int i){
    if (i == 1){
        return x;
    }else{
        if (i %2 == 0){
            GEN acc = powerRec(mul, x, i/2);
            return mul(acc, acc);
        }else{
            GEN acc = powerRec(mul, x, i-1);
            return mul(x, acc);        }
    }
}


GEN power(Group *g, GEN x, GEN y){
  
    GEN y3 = gel(y, 2);
    int i = itos(y3);

    if (i == 0){
        return g->one;
    }else{
        return powerRec(g->mul, x, i);
    }

    
}




GEN powerRec2(Loi mul, GEN x, GEN i){
   
    if (gequal(i, gen_1)){
        return x;
    }else{

        GEN pa = gmod(i, gen_2);
        if (gequal(pa, gen_0)){
            GEN acc = powerRec2(mul, x, gshift(i, -1));
            return mul(acc, acc);
        }else{
            GEN acc = powerRec2(mul, x, gsub(i, gen_1));
            return mul(x, acc);        }
    }
}

GEN power2(Group *g, GEN x, GEN y){
  
    GEN i = lift(y);
  

    if (gequal(i, gen_0)){
        return g->one;
    }else{
        return powerRec2(g->mul, x, i);
    }

    
}


GEN powerVector(Group *g, GEN a, GEN b){
    GEN output = g->one;
    GEN current;

    int N = lg(a) - 1;

 //  pariprintf("a = %Ps\n", a);
  // pariprintf("b = %Ps\n", b);
    

    for (int i = 1; i <= N ; i++){

       

        
        current = power2(g, gel(a, i),gel(b, i));
      //  pariprintf( "i = %d\n", i);
       // pariprintf(" i = %d current = %Ps\n",i, current);
       
        output = g->mul(output, current);
    }
   
    //output = g->mul(output, power2(g, gel(a, N), gel(b, N)));

    return output;
}


GEN powerSingle(Group *g, GEN x, GEN y){
    long size = lg(x) - 1;

    GEN output = cgetg(size+1, t_VEC);

    for (int i = 1; i <= size; i++){
        gel(output, i) = power2(g, gel(x,i), y);
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

