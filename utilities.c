#include "utilities.h"

GEN moduk(int a, int b){
    return gmodulo(stoi(a), stoi(b));
}

GEN initListModulo(int p, ...) {
    va_list args;
    va_start(args, p);

    int count = 0;
    int current;
    do {
        current = va_arg(args, int);
        if (current != -1) count++;
    } while (current != -1);

    va_end(args);

    
    GEN output = cgetg(count + 1, t_VEC); 

    va_start(args, p);
    for (int i = 1; i <= count; i++) {
        current = va_arg(args, int);
        gel(output, i) = gmodulo(stoi(current), stoi(p));
    }
    va_end(args);

    return output;
}

GEN initListModulo2(GEN p1, int p, ...) {
    va_list args;
    va_start(args, p);

    int count = 0;
    int current;
    do {
        current = va_arg(args, int);
        if (current != -1) count++;
    } while (current != -1);

    va_end(args);

    
    GEN output = cgetg(count + 1, t_VEC); 

    va_start(args, p);
    for (int i = 1; i <= count; i++) {
        current = va_arg(args, int);
        gel(output, i) = gmodulo(stoi(current), p1);
    }
    va_end(args);

    pariprintf("output = %Ps\n", output);
    return output;
}


GEN addVectors(GEN x, GEN y){

    long size = lg(x) - 1;

    GEN output = cgetg(size+1, t_VEC);

    for (int i = 1 ; i <= size; i++){
        gel(output, i) = gadd(gel(x, i), gel(y, i));
    }

    return output;

}

GEN prodVectors(GEN x, GEN y){
    long size = lg(x) - 1;

    GEN output = cgetg(size+1, t_VEC);

    for (int i = 1 ; i <= size; i++){
        gel(output, i) = gmul(gel(x, i), gel(y, i));
    }

    return output;
}

GEN chooseX(int p)
{
  return gmodulo(genrand(stoi(p)), stoi(p));
}


GEN mulConstante(GEN x, GEN alpha){
    long size = lg(x) - 1;

    GEN output = cgetg(size+1, t_VEC);

    for (int i = 1 ; i <= size; i++){
        gel(output, i) = gmul(gel(x, i), alpha);
    }

    return output;
}

