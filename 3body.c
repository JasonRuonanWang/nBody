#include "nbody.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char mode='x';
char figure='r';

double BOUNDARY = 100.0;
double BOUNDARY2v1 = 10000;
double RND_P = 10.0;
double RND_V = 5.0;

double c=2;
double cv=2.2;
double cm=1e12;

double random_double(double max){
    int r = rand();
    double rd = (double)rand()/(double)RAND_MAX - 0.5;
    rd = rd / 0.5 * max;
    return rd;
}

void dump(){
    int i;
    for (i=0; i<N; i++){
        printf("round=%ld, life=%ld; ", round_count, cycles);
        printf("X=%f, Y=%f, Z=%f; ", body_initial[i].X, body_initial[i].Y, body_initial[i].Z);
        printf("Vx=%f, Vy=%f, Vz=%f\n", body_initial[i].Vx, body_initial[i].Vy, body_initial[i].Vz);
    }
}

void reset(){
    round_count++;
    cycles=0;
    int i;

    if(figure == 't')
    {
        // Triangle
        body[0].mass = cm;
        body[1].mass = cm;
        body[2].mass = cm;
        body[0].X = 1*c; body[0].Y = 0*c; body[0].Z = 0;
        body[1].X =-1*c; body[1].Y = 0*c; body[1].Z = 0;
        body[2].X = 0*c; body[2].Y = sqrt(3.0)*c; body[2].Z = 0;
        body[0].Vx = -1*cv; body[0].Vy = -sqrt(3.0)*cv; body[0].Vz = 0;
        body[1].Vx = -1*cv; body[1].Vy =  sqrt(3.0)*cv; body[1].Vz = 0;
        body[2].Vx =  2*cv; body[2].Vy =          0*cv; body[2].Vz = 0;
    }
    else if(figure == '8')
    {
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
    }
    else
    {
        for (i=0; i<N; i++){
            body[i].mass = 1e12;
            body[i].X= random_double(RND_P);
            body[i].Y= random_double(RND_P);
            body[i].Z= random_double(RND_P);
            body[i].Vx= random_double(RND_V);
            body[i].Vy= random_double(RND_V);
            body[i].Vz= random_double(RND_V);
        }
        body[2].Vx= 0 - body[0].Vx - body[1].Vx;
        body[2].Vy= 0 - body[0].Vy - body[1].Vy;
        body[2].Vz= 0 - body[0].Vz - body[1].Vz;
    }

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

double distance(double x1, double y1, double z1, double x2, double y2, double z2){
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1));
}

void Judge(){
    int i;
    for (i=0; i<3; i++){
        if (body[i].X<-BOUNDARY
                || body[i].X>BOUNDARY
                || body[i].Y<-BOUNDARY
                || body[i].Y>BOUNDARY
                || body[i].Z<-BOUNDARY
                || body[i].Z>BOUNDARY
           ){
            dump();
            reset();
        }
    }
    double s01 = distance(body[0].X, body[0].Y, body[0].Z, body[1].X, body[1].Y, body[1].Z);
    double s02 = distance(body[0].X, body[0].Y, body[0].Z, body[2].X, body[2].Y, body[2].Z);
    double s12 = distance(body[1].X, body[1].Y, body[1].Z, body[2].X, body[2].Y, body[2].Z);

//    printf("s01=%f, s02=%f, s12=%f\n", s01, s02, s12);

    double s0102 = fabs(s01 - s02);
    double s0112 = fabs(s01 - s12);
    double s0212 = fabs(s02 - s12);

    if(s0102 < 0.001) s0102 = 0.001;
    if(s0112 < 0.001) s0112 = 0.001;
    if(s0212 < 0.001) s0212 = 0.001;

//    printf("s0102=%f, s0112=%f, s0212=%f\n", s0102, s0112, s0212);

    double ss0 = s0102 / s0112;
    double ss1 = s0102 / s0212;
    double ss2 = s0112 / s0212;

//    printf("ss0=%f, ss1=%f, ss2=%f\n", ss0, ss1, ss2);

    if(ss0<1) ss0 = 1 / ss0;
    if(ss1<1) ss1 = 1 / ss1;
    if(ss2<1) ss2 = 1 / ss2;

//    printf("ss0=%f, ss1=%f, ss2=%f\n", ss0, ss1, ss2);

    if(ss0 > BOUNDARY2v1 && ss1 > BOUNDARY2v1){
        dump();
        reset();
    }
    else if(ss0 > BOUNDARY2v1 && ss2 > BOUNDARY2v1){
        dump();
        reset();
    }
    else if(ss1 > BOUNDARY2v1 && ss2 > BOUNDARY2v1){
        dump();
        reset();
    }
}

int main(int argc, char**argv){
    srand(time(NULL));

    if(argc >= 2){
        mode = argv[1][0];
    }
    if(argc >= 3){
        figure = argv[2][0];
    }

    N=3;
    round_count=0;
    cycles=0;
    body = (Particle*) calloc((size_t)N, sizeof(Particle));
    body_initial = (Particle*) calloc((size_t)N, sizeof(Particle));
    srand((unsigned)time(NULL));
    reset();

    if(mode=='x'){
        nbody_main(0, 0);
    }
    else{
        while(cycles < 100000){
            Compute();
            Judge();
        }
    }

    return 0;
}


