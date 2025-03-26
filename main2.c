/*-*- compile-command: "cc -c -o com.o -g -O3 -Wall -fomit-frame-pointer -fno-strict-aliasing -fPIC -I\"/usr/include/x86_64-linux-gnu\" com.c && cc -o com.so -shared -g -O3 -Wall -fomit-frame-pointer -fno-strict-aliasing -fPIC -Wl,-shared -Wl,-z,relro com.o -lc -lm -L/usr/lib/x86_64-linux-gnu -lpari"; -*-*/
#include "proofProtocol.h"
#include <pari/pari.h>
#include <stdlib.h>
#include <time.h>
#include "utilities.h"
#include <time.h>



int main(int argn,char *argv[]){
    pari_init(1000000, 2); // Initialize PARI with memory allocation



    //testing the algorithm on elliptic curves



    pari_printf("Hello world!\n");


    pari_close();

}
