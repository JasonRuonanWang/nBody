#include "nbody.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define BOUNDARY 50.0
#define RND_P 10.0
#define RND_V 1.0

double random_double(double max){
    int r = rand();
    double rd = (double)rand()/(double)RAND_MAX - 0.5;
    rd = rd / 0.5 * max;
    return rd;
}

void genData(){
    round_count++;
    int i;
    for (i=0; i<N; i++){
        body[i].mass = 1e11;
        body[i].X= random_double(RND_P);
        body[i].Y= random_double(RND_P);
        body[i].Z= 0;
//        body[i].Z= random_double(RND_P);
        body[i].Vx= random_double(RND_V);
        body[i].Vy= random_double(RND_V);
        body[i].Vz= 0;
//        body[i].Vz= random_double(RND_V);
    }
    body[2].Vx= 0 - body[0].Vx - body[1].Vx;
    body[2].Vy= 0 - body[0].Vy - body[1].Vy;
    body[2].Vz= 0 - body[0].Vz - body[1].Vz;

    for (i=0; i<N; i++){
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
    round_count=0;
    cycles=0;
    body = (Particle*) calloc((size_t)N, sizeof(Particle));
    body_origin = (Particle*) calloc((size_t)N, sizeof(Particle));
    srand((unsigned)time(NULL));
    genData();
    nbody_main(argc, argv);

    return 0;
}


