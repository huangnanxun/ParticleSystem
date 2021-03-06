
#define _CRT_SECURE_NO_WARNINGS    

#include <stdlib.h>     
#include"particle.h"
#include <stdio.h>


emitter* e1;

GLuint texture[1];

float whRatio;
int wHeight = 0;
int wWidth = 0;


float center[] = { 0,0,0 };
float eye[] = { 0, 0, 5};

GLuint faucet;
char ch = '1';
bool status_ON = true;

void timerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(33, timerFunc, 1);
}

particle* init_particle()
{
	static int count = 0;
	float size = rand() % 50 * 0.02f;
	particle* p;
	unsigned char init_color[3] = { 0,0,1 };
	float init_xspeed = float(rand() % 10 - 4) / 200;
	float init_yspeed = float(rand() % 10 - 4) / 200;
	float init_zspeed = float(rand() % 10 - 4) / 200;
	float life_cycle = rand() % 100;
	p = new particle(size,size,size,init_xspeed, init_yspeed, init_zspeed, 0, float(-9.8 / 1000),0, life_cycle, 0, init_color, false);

	return p;
}
void drawScene()
{
	if (status_ON) {
		e1->update();
		e1->generate();
	}
	else {
		e1->update();
	}
}

void updateView(int height, int width)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);       
	glLoadIdentity();           
	whRatio = (GLfloat)width / (GLfloat)height;
	glOrtho(-30, 30, -30, 30, -100, 100);
	glMatrixMode(GL_MODELVIEW);
}

void reshape(int width, int height)
{
	if (height == 0) {
		height = 1;      
	}
	wHeight = height;
	wWidth = width;
	updateView(wHeight, wWidth);       
}

void idle()
{
	glutPostRedisplay();
}

void init(void)
{
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glColor4f(1.0, 1.0, 1.0, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	e1 = new emitter(2500, 0, 0, 25, 25, 0, 0);
	e1->emit(init_particle);
}

float camera_rotate = 0;
float camera_scale = 1;
float camera_height = 0;

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(camera_rotate, 0.0f, 1.0f, 0.0f);
	glScaled(camera_scale, camera_scale, camera_scale);
	glTranslatef(0.0f, camera_height, 0.0f);
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);

	glPushMatrix();
	glTranslatef(0, 24, -2.2);
	glColor3f(1.0, 0.23, 0.27);
	glScalef(0.1, 0.1, 0.1);
	glCallList(faucet);
	glPopMatrix();

	drawScene();
	glutSwapBuffers(); 
}


void keypress(int key, int x, int y)
{
	if (key == GLUT_KEY_RIGHT) {
		camera_rotate += 1.50f;
		printf("Right");
	}
	if (key == GLUT_KEY_LEFT) {
		camera_rotate -= 1.50f;
		printf("Left");
	}
	if (key == GLUT_KEY_UP) {
		camera_height += 1.50f;
		printf("Up");
	}
	if (key == GLUT_KEY_DOWN) {
		camera_height -= 1.50f;
		printf("Down");
	}
	if (key == GLUT_KEY_PAGE_UP) {
		camera_scale *= 1.10f;
		printf("Scale_up");
	}
	if (key == GLUT_KEY_PAGE_DOWN) {
		camera_scale /= 1.10f;
		printf("Scale_down");
	}

}


void mouseclick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (status_ON == true) {
			status_ON = false;
			printf("close faucet");
		}
		else {
			status_ON = true;
			printf("open faucet");
		}
	}
}

void loadObj(const char* fname)
{
	FILE* fp;
	int read;
	GLfloat x, y, z;
	char ch;
	faucet = glGenLists(1);
	fp = fopen(fname, "r");
	if (!fp)
	{
		printf("can't open file %s\n", fname);
		exit(1);
	}
	glPointSize(2.0);
	glNewList(faucet, GL_COMPILE);
	{
		glPushMatrix();
		glBegin(GL_POINTS);
		while (!(feof(fp)))
		{
			read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
			if (read == 4 && ch == 'v')
			{
				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}
	glPopMatrix();
	glEndList();
	fclose(fp);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);          
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);           
	glutInitWindowSize(800, 600);         
	int windowHandle = glutCreateWindow("Particle_System");
	glutMouseFunc(mouseclick);
	glutSpecialFunc(keypress);
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);      
	glutIdleFunc(idle);  
	loadObj("faucet.obj");
	init();
	glutTimerFunc(33, timerFunc, 1);
	glutMainLoop();
	return 0;
}
