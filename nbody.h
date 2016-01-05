#include <stdbool.h>

#ifndef NBODY_H
#define NBODY_H

typedef struct {
    double mass;
    double X;
    double Y;
    double Z;
    double Vx;
    double Vy;
    double Vz;
    double Fx;
    double Fy;
    double Fz;
    int color;
} Particle;

Particle *body;
Particle *body_origin;
int N;
unsigned long round_count;
unsigned long cycles;

int nbody_main(int argc, char **argv);
void genData();
void Judge();

#endif


