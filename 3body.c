#include "nbody.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double BOUNDARY = 100.0;
double RND_P = 10.0;
double RND_V = 5.0;

double c=10;
double cv=5;
double cm=1e12;

double random_double(double max){
    int r = rand();
    double rd = (double)rand()/(double)RAND_MAX - 0.5;
    rd = rd / 0.5 * max;
    return rd;
}


void reset(){
    round_count++;
    cycles=0;
    int i;
    for (i=0; i<N; i++){
        body[i].mass = 1e12;
        body[i].X= random_double(RND_P);
        body[i].Y= random_double(RND_P);
//        body[i].Z= 0;
        body[i].Z= random_double(RND_P);
        body[i].Vx= random_double(RND_V);
        body[i].Vy= random_double(RND_V);
//        body[i].Vz= 0;
        body[i].Vz= random_double(RND_V);
    }
    body[2].Vx= 0 - body[0].Vx - body[1].Vx;
    body[2].Vy= 0 - body[0].Vy - body[1].Vy;
    body[2].Vz= 0 - body[0].Vz - body[1].Vz;


/*

    // Triangle
    body[0].X = 1*c; body[0].Y = 0*c; body[0].Z = 0;
    body[1].X =-1*c; body[1].Y = 0*c; body[1].Z = 0;
    body[2].X = 0*c; body[2].Y = sqrt(3.0)*c; body[2].Z = 0;
    body[0].Vx = -1*cv; body[0].Vy = -sqrt(3.0)*cv; body[0].Vz = 0;
    body[1].Vx = -1*cv; body[1].Vy =  sqrt(3.0)*cv; body[1].Vz = 0;
    body[2].Vx =  2*cv; body[2].Vy =          0*cv; body[2].Vz = 0;

    // 8
    body[0].mass = cm;
    body[1].mass = cm;
    body[2].mass = cm;
    body[0].X = 0.97000436*c; body[0].Y = -0.24308753*c; body[0].Z = 0;
    body[1].X =-body[0].X; body[1].Y = -body[0].Y; body[1].Z = 0;
    body[2].X = 0; body[2].Y = 0; body[2].Z = 0;
    body[2].Vx = -0.93240737*cv; body[2].Vy = -0.86473146*cv; body[2].Vz = 0;
    body[1].Vx = -body[2].Vx/2; body[1].Vy = -body[2].Vy/2; body[1].Vz = 0;
    body[0].Vx = body[1].Vx; body[0].Vy = body[1].Vy; body[0].Vz = 0;

*/

    for (i=0; i<N; i++){
        body_initial[i].mass = body[i].mass;
        body_initial[i].X = body[i].X;
        body_initial[i].Y = body[i].Y;
        body_initial[i].Z = body[i].Z;
        body_initial[i].Vx = body[i].Vx;
        body_initial[i].Vy = body[i].Vy;
        body_initial[i].Vz = body[i].Vz;
    }
}

void Judge(){
    int i;
    for (i=0; i<N; i++){
        if (body[i].X<-BOUNDARY
                || body[i].X>BOUNDARY
                || body[i].Y<-BOUNDARY
                || body[i].Y>BOUNDARY
                || body[i].Z<-BOUNDARY
                || body[i].Z>BOUNDARY
           ){
            printf("round=%ld, life=%ld; ", round_count, cycles);
            printf("X=%f, Y=%f, Z=%f; ", body_initial[i].X, body_initial[i].Y, body_initial[i].Z);
            printf("Vx=%f, Vy=%f, Vz=%f\n", body_initial[i].Vx, body_initial[i].Vy, body_initial[i].Vz);
            reset();
        }
    }
}

int main(int argc, char**argv){
    srand(time(NULL));

    if(argc == 2){
        cv = atof(argv[1]);
    }

    if (argc > 2){
        return -1;
    }
    N=3;
    round_count=0;
    cycles=0;
    body = (Particle*) calloc((size_t)N, sizeof(Particle));
    body_initial = (Particle*) calloc((size_t)N, sizeof(Particle));
    srand((unsigned)time(NULL));
    reset();
    nbody_main_xless();
    nbody_main(0, 0);

    return 0;
}


