// nbody.cpp : Template program for N-body
// Copyright UWA, 2012

#define _ANSI_SOURCE

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <gl/Gl.h>
#include <gl/glut.h>

#define M_PI        3.14159265358979323846264338327950288   /* pi */
#define WIDTH 800
#define HEIGHT 800
#define POINT_SIZE 1
#define POSITION_X 112
#define POSITION_Y 20
#define WORLD_LEFT -10000
#define WORLD_RIGHT 10000
#define WORLD_BOTTOM -10000
#define WORLD_TOP 10000
#define VIEW_ANGLE 45
#define RHO 100
#define WORLD_NEAR 0.1
#define WORLD_FAR 1000000
#define BALL_SIZE 0.5
#define REFRESH_RATE 0.001
#define LINE_SIZE 1000
#define G 6.67428E-11
#define DELTA_T 0.05

#define square(x) ((x)*(x))

int cycles;
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

double previousTime, eyeTheta, eyePhi, eyeRho;
float look[3];
int windowWidth, windowHeight, upY;

double SCALE = 1;

Particle *body;
int N;
int numberOfProcessors=1;

/*
 * Initialization of graphics
 */
void Init(void) {

	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(POINT_SIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*init lighting */

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 0.0, 0.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glColorMaterial(GL_FRONT,GL_DIFFUSE);                // Set Color Capability

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

    glEnable(GL_COLOR_MATERIAL);		       // Enable color

	double displayRatio = 1.0 * WIDTH / HEIGHT;
	windowWidth = WIDTH;
	windowHeight = HEIGHT;
	previousTime = clock();
	eyeTheta = 0;
    eyePhi = 0.5 * M_PI;
    eyeRho = RHO;
    upY = 1;
	look[0] = 0;
	look[1] = 0;
	look[2] = 0;
    gluPerspective(VIEW_ANGLE, displayRatio, WORLD_NEAR, WORLD_FAR);
//    GLKMatrix4MakePerspective(VIEW_ANGLE, displayRatio, WORLD_NEAR, WORLD_FAR);

}

/*
 * This function redraws the screen after the positions of particles
 * have been updated
 */
void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeRho * sin(eyePhi) * sin(eyeTheta), eyeRho * cos(eyePhi),
                    eyeRho * sin(eyePhi) * cos(eyeTheta),
					look[0], look[1], look[2], 0, upY, 0);

	int i;
	for (i = 0; i < N; i++) {
        //glClearColor(1.0,1.0,1.0,0.0);
		glColor3f(0.0f, body[i].mass/1e11*100, 0.0f);
        //glColor3f(1.0f, 0.0f, 0.0f);
		glPushMatrix(); // to save the current matrix
		glTranslated(SCALE*body[i].X, SCALE*body[i].Y, SCALE*body[i].Z);
		glutSolidSphere (BALL_SIZE, 10, 10);
		glPopMatrix(); // restore the previous matrix
	}
	glFlush();
}

/*
 * Prints the body on screen
 */
void PrintBody(int i)
{
	printf("Body #%d M=%f X=%f Y=%f Z=%f Fx=%f Fy=%f Fz=%f Vx=%f Xy=%f Vz=%f\n",
           i, body[i].mass, body[i].X, body[i].Y, body[i].Z, body[i].Fx,
           body[i].Fy, body[i].Fz,	body[i].Vx, body[i].Vy, body[i].Vz);
}

/*
 * Computing forces
 */
void Force(int a) {
	double distance;
	double con;
	double gd;

	body[a].Fx = body[a].Fy = body[a].Fz = 0;

	int b;
	for(b=0; b<N; ++b)
		if( b != a ){
		distance = sqrt(square(body[b].X - body[a].X) + square(body[b].Y
                                - body[a].Y) + square(body[b].Z - body[a].Z));
		con = G * body[a].mass * body[b].mass / square(distance);
		gd = con / distance;
		body[a].Fx += gd * (body[b].X - body[a].X);
		body[a].Fy += gd * (body[b].Y - body[a].Y);
		body[a].Fz += gd * (body[b].Z - body[a].Z);
		}
}

/*
 * Compute velocities
 */
void Velocity(int a) {
		body[a].Vx += body[a].Fx/body[a].mass * DELTA_T;
		body[a].Vy += body[a].Fy/body[a].mass * DELTA_T;
		body[a].Vz += body[a].Fz/body[a].mass * DELTA_T;
}

/*
 * Compute positions
 */
void Position(int a) {
	body[a].X += body[a].Vx * DELTA_T;
	body[a].Y += body[a].Vy * DELTA_T;
	body[a].Z += body[a].Vz * DELTA_T;
}

/*
 * Main compute function
 */
void Compute() {


	cycles++;


	int a;

#pragma omp parallel for
	for(a=0; a<N; a++) {
		Force(a);
		Velocity(a);
	}


#pragma omp parallel for
	for(a=0; a<N; a++) {
		Position(a);
	}




}

/*
 * This function is called repeatedly by graphics library. You can consider
 * it as main loop in the program.
 */
void Animate(void) {

	Compute(); //Compute and update new positions for the time step
	Display(); // Display needs to be called to redraw the screen
}

/*
 * This function is to manipulate with the image
 */
void KeyBoard(unsigned char theKey, int mouseX, int mouseY) {
	if (theKey == 'x' || theKey == 'X') {
		free(body);
		exit(EXIT_SUCCESS);
	}
	if (theKey == 'i' || theKey == 'I') {
		eyePhi -= M_PI / 20;
		if (eyePhi == 0)
			eyePhi = 2 * M_PI;
	} else if (theKey == 'm' || theKey == 'I') {
		eyePhi += M_PI / 20;
	} else if (theKey == 'j' || theKey == 'J') {
		eyeTheta -= M_PI / 20;
	} else if (theKey == 'k' || theKey == 'K') {
		eyeTheta += M_PI / 20;
	} else if (theKey == ',') {
		eyeRho += 0.5;
	} else if (theKey == '.' || theKey == 'I') {
		eyeRho -= 0.5;
	} else if (theKey == 'w' || theKey == 'W') {
		look[1] += 0.5;
	} else if (theKey == 'z' || theKey == 'Z') {
		look[1] -= 0.5;
	} else if (theKey == 'a' || theKey == 'A') {
		look[0] -= 0.5;
	} else if (theKey == 's' || theKey == 'S') {
		look[0] += 0.5;
	} else if (theKey == '+') {
		SCALE *= 1.1;
	} else if (theKey == '-') {
		SCALE *= 0.9;
	}
	if (sin(eyePhi) > 0) upY = 1;
	else upY = 1;
}

void Reshape(int width, int height) {
	double displayRatio = 1.0 * width / height;
	windowWidth = width;
	windowHeight = height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(VIEW_ANGLE, displayRatio, WORLD_NEAR, WORLD_FAR);
	glViewport(0, 0, windowWidth, windowHeight);
}

/*
 * This function reads an input file. You can change it if you choose a
 * different file format
 */
void readFile(char *fileName) {
	char line[LINE_SIZE];
	char *token;
	FILE *file;

	file = fopen(fileName, "rt");
	N = atoi(fgets(line, LINE_SIZE, file));
	body = (Particle*) calloc((size_t)N, sizeof(Particle));

	puts("----------------------Initial field-------------------------------");

	int i;
	for (i=0; i<N; ++i)
		if(fgets(line, LINE_SIZE, file) != NULL){
		token = strtok(line, ",; ");
		body[i].mass = atof(token);
		token = strtok(NULL, ",; ");
		body[i].X = atof(token);
		token = strtok(NULL, ",; ");
		body[i].Y = atof(token);
		token = strtok(NULL, ",; ");
		body[i].Z = atof(token);
		token = strtok(NULL, ",; ");
		body[i].Vx = atof(token);
		token = strtok(NULL, ",; ");
		body[i].Vy = atof(token);
		token = strtok(NULL, ",; ");
		body[i].Vz = atof(token);

		PrintBody(i);
		}
	puts("--------------------------------------------------------------");
	puts("Use:\n X - exit\n I, J, K, M - rotate\n W, Z, A, S - move to view"
         " point\n ./, - zoom in/out\n +/- - scaled zoom in/out\n");

	fclose(file);
}


// This is main function. Do not change it.
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	if (argc < 2) {
		puts("Please provide the filename, i.e. \'nbody bodiesfield.dat\'");
	    exit(EXIT_SUCCESS);
	}
	if (argc >= 2) readFile(argv[1]);
	if (argc >= 3) numberOfProcessors = atoi(argv[2]);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(POSITION_X, POSITION_Y);
	glutCreateWindow("N-Body Parallel");
	glutDisplayFunc(Display);
	glutIdleFunc(Animate);
	glutKeyboardFunc(KeyBoard);
	glutReshapeFunc(Reshape);
	Init();
	glutMainLoop();
}
