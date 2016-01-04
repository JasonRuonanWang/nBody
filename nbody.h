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
int N;

int nbody_main(int argc, char **argv);



