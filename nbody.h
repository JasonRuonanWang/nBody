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

extern Particle *body;
extern Particle *body_initial;
extern int N;
extern unsigned long round_count;
extern unsigned long cycles;

int nbody_main(int argc, char **argv);
void genData();
void Judge();
void Compute();
void reset();

#endif


