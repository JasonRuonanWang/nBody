#include "nbody.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define BOUNDARY 100.0

double random_double(double max){
    int r = rand();
    double rd = (double)rand()/(double)RAND_MAX - 0.5;
    rd = rd / 0.5 * max;
    return rd;
}

void genData(){
    int i;
    for (i=0; i<N; i++){
        body[i].mass = 1e11;
        body[i].X= random_double(10);
        body[i].Y= random_double(10);
        body[i].Z= 0;
        body[i].Vx= random_double(1);
        body[i].Vy= random_double(1);
        body[i].Vz= 0;

        body_origin[i].mass = body[i].mass;
        body_origin[i].X = body[i].X;
        body_origin[i].Y = body[i].Y;
        body_origin[i].Z = body[i].Z;
        body_origin[i].Vx = body[i].Vx;
        body_origin[i].Vy = body[i].Vy;
        body_origin[i].Vz = body[i].Vz;
    }
}

void Judge(){
    int i;
    for (i=0; i<N; i++){
        if (body[i].X<-BOUNDARY || body[i].X>BOUNDARY)
            genData();
        if (body[i].Y<-BOUNDARY || body[i].Y>BOUNDARY)
            genData();
        if (body[i].Z<-BOUNDARY || body[i].Z>BOUNDARY)
            genData();
    }
}

int main(int argc, char**argv){
    if (argc >= 2){
        return -1;
    }
    N=3;
    body = (Particle*) calloc((size_t)N, sizeof(Particle));
    body_origin = (Particle*) calloc((size_t)N, sizeof(Particle));
    srand((unsigned)time(NULL));
    running =true;
    while(running){
        genData();
        nbody_main(argc, argv);
    }

    return 0;
}


