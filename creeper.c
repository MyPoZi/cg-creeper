#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

unsigned char mouseFlag = GL_FALSE;
double	 theta = 0.0;
int Start;
double angle = 0.0;

double	sizeOfTeapot = 1.0;

float light_pos[] = { 10, 10, 10, 10 };

float mtrl_diffuse[] = { 0.6, 0.6, 0.6, 0.0 };
float mtrl_specular[] = { 0.0, 1.0, 0.3, 0.0 };
float mtrl_shininess[] = { 0.8 };					// range [0,128]



void myKeyboard( unsigned char key, int x, int y )
{
    if ( key == 27 ) exit( 0 );
}

void mySetLight()
{
	//float light0_position[] = { 1.0,  1.0, 1.0, 1.0 };

	/* LIGHT0 uses the default parameters except position */
	//glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	//glEnable(GL_LIGHT0);
	/* Shading the both sides of box */
	//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	GLfloat light_diffuse[] = { 0.9, 0.9, 0.9, 1.0 };	// 拡散反射光
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };	// 鏡面反射光
	GLfloat light_ambient[] = { 0.5, 1.0, 1.0, 0.6 };	// 環境光
	GLfloat light_position[] = { -0.5, 1.0, 1.0, 1.0 };	// 位置と種類

	// 光源の設定
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);	 // 拡散反射光の設定
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); // 鏡面反射光の設定
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);	 // 環境光の設定
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // 位置と種類の設定

	glShadeModel(GL_SMOOTH);	// シェーディングの種類の設定
	glEnable(GL_LIGHT0);		// 光源の有効化
}

void myFloor()
{
	int i, j, idx, range = 100;
	double x, z, d = 0.05;

	for (i = -range; i <= range; i++) {
		x = i * d;
		for (j = -range; j <= range; j++) {
			z = j * d;
			idx = 0;
			if ( (abs(i) % 2) == (abs(j) % 2) ) idx = 1;
			glBegin(GL_QUADS);
			if (idx) glColor3d(0.0, 0.2, 0.0);
			// else glColor3d(0.0, 0.5, 0.0);
			glNormal3b(0.0, 1.0, 0.0);
			glVertex3d(x, 0.0, z);
			glVertex3d(x, 0.0, z + d);
			glVertex3d(x + d, 0.0, z + d);
			glVertex3d(x + d, 0.0, z);
			glEnd();
		}
	}
}

void myDisplay(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtrl_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtrl_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mtrl_shininess);

	// glPushMatrix();

	//glClearColor(0.2f, 0.2f, 0.2f, 1.0);					// 背景色
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);		// 隠面処理の適用
	mySetLight();					// 光源の設定
	glEnable(GL_LIGHTING);		// 光源ON
	// glPopMatrix();





	glPushMatrix();
		glTranslated(0.0, -3.0, 0.0);
		myFloor();
	glPopMatrix();


	glRotated(theta, 0.0, 1.0, 0.0);
	glRotated(angle, 1.0, 0.0, 0.0);


	glPushMatrix();






	// head
	glPushMatrix();
		glColor3d(0.0, 1.0, 0.0);
		glutSolidCube(1.0);
	glPopMatrix();
	// body
	glTranslated(0.0, -1.5, 0.0);
	glPushMatrix();
		glColor3d(0.0, 1.0, 0.0);
		glScaled(0.9, 2.0, 0.5);
		glutSolidCube(1.0);
	glPopMatrix();
	// foot1
	glTranslated(0.0, -1.5, 0.0);
	glPushMatrix();
		glColor3d(1.0, 1.0, 1.0);
		glTranslated(0.0, 0.0, 0.5);
		glScaled(0.9, 1.0, 0.5);
		glutSolidCube(1.0);
	glPopMatrix();
	// foot2
		glPushMatrix();
		glColor3d(1.0, 1.0, 1.0);
		glTranslated(0.0, 0.0, -0.5);
		glScaled(0.9, 1.0, 0.5);
		glutSolidCube(1.0);
	glPopMatrix();


	glPopMatrix();



    glutSwapBuffers();


}


void myMouseMotion(int x, int y)
{
	int		xdis, ydis;
	double	a = 0.1;

	if (mouseFlag == GL_FALSE) return;
	ydis = y - Start;
	angle += (double)ydis * a;

	Start = y;
	glutPostRedisplay();
}

void myMouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		Start = y;
		mouseFlag = GL_TRUE;
	}
	else {
		mouseFlag = GL_FALSE;
	}
}

void getValueFromMenu(int value)
{
	switch (value) {
	case 1:
		sizeOfTeapot = 0.5;
		break;
	case 2:
		sizeOfTeapot = 1.0;
		break;
	case 3:
		sizeOfTeapot = 2.0;
		break;
	default:
		break;
	}
}

void mySetMenu()
{
	glutCreateMenu(getValueFromMenu);
	glutAddMenuEntry("x 0.5", 1);
	glutAddMenuEntry("x 1.0", 2);
	glutAddMenuEntry("x 2.0", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void myIdle(void)
{
	theta = fmod(theta + 0.01, 360.0);
	glutPostRedisplay();
}

void myInit (char *progname)
{
    int width = 500, height = 500;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize( width, height);
	glutInitWindowPosition(0, 0); 
	glutCreateWindow(progname);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0);					// 背景色
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)width/(double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); 
	myInit(argv[0]);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouseFunc);
	glutMotionFunc(myMouseMotion);
	mySetMenu();
	mySetLight();
	glutIdleFunc(myIdle);
	glutDisplayFunc(myDisplay);
	glutMainLoop(); 
	return 0;
}
