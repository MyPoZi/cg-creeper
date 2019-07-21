#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

unsigned char mouseFlag = GL_FALSE;
double	 theta = 0.0;
int Start;
double angle = 0.0;

double	sizeOfTeapot = 1.0;

float light_pos[] = { 10, 10, 10, 10 };

float mtrl_diffuse[] = { 0.5, 0.5, 0.5, 0.0 };
float mtrl_specular[] = { 0.0, 1.0, 0.0, 0.0 };
float mtrl_shininess[] = { 0.8 };

#define imageWidth		64
#define imageHeight		64

unsigned char texImage[imageHeight][imageWidth][4];

void makeTexImage(void)
{
	int i, j, c;

	for (i = 0; i < 16; i++) {
		for (j = 8; j < 24; j++) {
			texImage[i][j][0] = (unsigned char)255;
			texImage[i][j][1] = (unsigned char)255;
			texImage[i][j][2] = (unsigned char)255;
			texImage[i][j][3] = (unsigned char)0;
		}
	}

	for (i = 0; i < 16; i++) {
		for (j = 40; j < 56; j++) {
			texImage[i][j][0] = (unsigned char)255;
			texImage[i][j][1] = (unsigned char)255;
			texImage[i][j][2] = (unsigned char)255;
			texImage[i][j][3] = (unsigned char)0;
		}
	}

	for (i = 56; i < 64; i++) {
		for (j = 56; j < 64; j++) {
			texImage[i][j][0] = (unsigned char)255;
			texImage[i][j][1] = (unsigned char)255;
			texImage[i][j][2] = (unsigned char)255;
			texImage[i][j][3] = (unsigned char)0;
		}
		for (j = 0; j < 8; j++) {
			texImage[i][j][0] = (unsigned char)255;
			texImage[i][j][1] = (unsigned char)255;
			texImage[i][j][2] = (unsigned char)255;
			texImage[i][j][3] = (unsigned char)0;
		}
	}

	for (i = 48; i < 56; i++) {
		for (j = 48; j < 64; j++) {
			texImage[i][j][0] = (unsigned char)255;
			texImage[i][j][1] = (unsigned char)255;
			texImage[i][j][2] = (unsigned char)255;
			texImage[i][j][3] = (unsigned char)0;
		}
		for (j = 0; j < 16; j++) {
			texImage[i][j][0] = (unsigned char)255;
			texImage[i][j][1] = (unsigned char)255;
			texImage[i][j][2] = (unsigned char)255;
			texImage[i][j][3] = (unsigned char)0;
		}
	}
	for (i = 40; i < 48; i++) {
		for (j = 48; j < 64; j++) {
			texImage[i][j][0] = (unsigned char)255;
			texImage[i][j][1] = (unsigned char)255;
			texImage[i][j][2] = (unsigned char)255;
			texImage[i][j][3] = (unsigned char)0;
		}
		for (j = 0; j < 16; j++) {
			texImage[i][j][0] = (unsigned char)255;
			texImage[i][j][1] = (unsigned char)255;
			texImage[i][j][2] = (unsigned char)255;
			texImage[i][j][3] = (unsigned char)0;
		}
	}

	for (i = 33; i < 40; i++) {
		for (j = 48; j < 56; j++) {
			texImage[i][j][0] = (unsigned char)255;
			texImage[i][j][1] = (unsigned char)255;
			texImage[i][j][2] = (unsigned char)255;
			texImage[i][j][3] = (unsigned char)0;
		}
		for (j = 8; j < 16; j++) {
			texImage[i][j][0] = (unsigned char)255;
			texImage[i][j][1] = (unsigned char)255;
			texImage[i][j][2] = (unsigned char)255;
			texImage[i][j][3] = (unsigned char)0;
		}
	}
}

void setupTextures(void)
{
	makeTexImage();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, texImage);
	glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
}

void myKeyboard( unsigned char key, int x, int y )
{
    if ( key == 27 ) exit( 0 );
}

void mySetLight()
{
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtrl_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtrl_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mtrl_shininess);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);		// 隠面処理の適用
	mySetLight();					// 光源の設定
	glEnable(GL_LIGHTING);		// 光源ON

	glPushMatrix();
		glTranslated(0.0, -3.0, 0.0);
		myFloor();
	glPopMatrix();

	glRotated(theta, 0.0, 1.0, 0.0);
	glRotated(angle, 1.0, 0.0, 0.0);

	glPushMatrix();

	// head
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glutSolidCube(1.0);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// body
	glTranslated(0.0, -1.5, 0.0);
	glPushMatrix();
		glColor3d(1.0, 1.0, 0.0);
		glScaled(0.9, 2.0, 0.5);
		glutSolidCube(1.0);
	glPopMatrix();

	// foot1
	glTranslated(0.0, -1.5, 0.0);
	glPushMatrix();
		glColor3d(0.0, 1.0, 0.0);
		glTranslated(0.0, 0.0, 0.5);
		glScaled(0.9, 1.0, 0.5);
		glutSolidCube(1.0);
	glPopMatrix();

	// foot2
		glPushMatrix();
		glColor3d(0.0, 1.0, 0.0);
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
		mtrl_specular[0] = 0.0;
		mtrl_specular[1] = 1.0;
		mtrl_specular[2] = 0.0;
		mtrl_specular[3] = 0.0;
		break;
	case 2:
		mtrl_specular[0] = 0.0;
		mtrl_specular[1] = 0.0;
		mtrl_specular[2] = 1.0;
		mtrl_specular[3] = 0.0;
		break;
	case 3:
		mtrl_specular[0] = 1.0;
		mtrl_specular[1] = 0.0;
		mtrl_specular[2] = 0.0;
		mtrl_specular[3] = 0.0;
		break;
	case 4:
		mtrl_specular[0] = 1.0;
		mtrl_specular[1] = 1.0;
		mtrl_specular[2] = 0.0;
		mtrl_specular[3] = 0.0;
		break;
	default:
		break;
	}
}

void mySetMenu()
{
	glutCreateMenu(getValueFromMenu);
	glutAddMenuEntry("green", 1);
	glutAddMenuEntry("blue", 2);
	glutAddMenuEntry("red", 3);
	glutAddMenuEntry("yellow", 4);
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
	glClearColor(0.2f, 0.2f, 0.2f, 1.0); // 背景
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
	setupTextures();
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
