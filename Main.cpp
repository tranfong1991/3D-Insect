#define _USE_MATH_DEFINES
#include <iostream>
#include <gl/glut.h>

#define RIGHT 1
#define LEFT -1
#define UP 1
#define DOWN -1

bool armUp = false;
bool armDown = false;
bool viewMode = true;
bool moveMode = false;
float topFrustumIncr = 0.0;
float upperLeftLegAngleIncr = 0.0;
float lowerLeftLegAngleIncr = 0.0;
float upperRightLegAngleIncr = 0.0;
float lowerRightLegAngleIncr = 0.0;

float angle = 0.0;
float rotateX = 0.0;
float rotateY = 1.0;
float rotateZ = 0.0;
float prevX = 0.0, prevY = 0.0;
float posX = 0.0, posY = 0.0, posZ = 10.0;
float originX = 300, originY = 300;
float newAngle, newX, newY;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_FLAT);

	//hidden surface removal: both z-buffer and backface culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
}

void body()
{
	glColor3f(1.0, 0.0, 0.0);
	glScalef(1.7, 2.0, 1.0);
	glutSolidSphere(1, 20, 50);

	//divider
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
		glScalef(0.03, 1.0, 1.05);
		glutSolidSphere(1.0, 20, 50);
	glPopMatrix();

	//dots
	glPushMatrix();
		glTranslatef(-0.3, 0.3, 0.0);
		glScalef(1.0, 1.0, 1.8);
		glutSolidSphere(0.5, 20, 50);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.3, 0.2, 0.0);
		glScalef(1.0, 1.0, 1.9);
		glutSolidSphere(0.5, 20, 50);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.3, 0.0, 0.0);
		glScalef(1.0, 1.0, 2.5);
		glutSolidSphere(0.4, 20, 50);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.3, -0.3, 0.0);
		glScalef(1.0, 1.0, 1.4);
		glutSolidSphere(0.6, 20, 50);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.3, -0.2, 0.0);
		glScalef(1.0, 1.0, 1.9);
		glutSolidSphere(0.5, 20, 50);
	glPopMatrix();
}

/*
	side = 1 : right
	side = -1 : left
*/
void eye(int side)
{
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
		glTranslatef(side * 0.25, 0.3, 0.5);
		glScalef(0.8, 0.5, 0.8);
		glutSolidSphere(0.2, 20, 50);
	glPopMatrix();
}

void antenna(int side)
{
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(side * 0.4, 0.9, 0.0);
		glRotatef(side * 60, 0.0, 0.0, 1.0);
		glScalef(6.0, 0.5, 1.0);
		glutSolidCube(0.1);
	glPopMatrix();
}

void head()
{
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(0.0, 1.0, 0.0);
		glScalef(0.7, 0.5, 1.0);
		glutSolidSphere(0.7, 20, 50);

		eye(RIGHT);
		eye(LEFT);
		antenna(RIGHT);
		antenna(LEFT);
	glPopMatrix();
}

void frontLeg(int side, float lowerLegAngleIncr, float upperLegAngleIncr)
{
	//upper leg
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(side, 0.7, 0.0);
		glRotatef(lowerLegAngleIncr, 1.0, 0.0, 0.0);
		glRotatef(side * (50.0 + upperLegAngleIncr), 0.0, 0.0, 1.0);
		glScalef(1.8, 0.3, 1.0);
		glutSolidSphere(0.2, 20, 50);

		//lower leg
		glPushMatrix();
			glTranslatef(side * 0.25, 0.1, -0.15);
			glRotatef(side * -35.0, 0.0, 1.0, 0.0);
			glRotatef(35.0, 1.0, 0.0, 0.0);
			glScalef(0.2, 0.3, 1.5);
			glutSolidSphere(0.2, 20, 50);
		glPopMatrix();
	glPopMatrix();
}

void middleLeg(int side, float lowerLegAngleIncr, float upperLegAngleIncr)
{
	//upper leg
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(side * 1.1, 0.0, 0.0);
		glRotatef(lowerLegAngleIncr, 1.0, 0.0, 0.0);
		glRotatef(side * upperLegAngleIncr, 0.0, 0.0, 1.0);
		glScalef(1.8, 0.3, 1.0);
		glutSolidSphere(0.2, 20, 50);

		//lower leg
		glPushMatrix();
			glTranslatef(side * 0.3, -0.1, -0.15);
			glRotatef(side * -35.0, 0.0, 1.0, 0.0);
			glRotatef(-35.0, 1.0, 0.0, 0.0);
			glScalef(0.2, 0.3, 1.5);
			glutSolidSphere(0.2, 20, 50);
		glPopMatrix();
	glPopMatrix();
}

void backLeg(int side, float lowerLegAngleIncr, float upperLegAngleIncr)
{
	//upper leg
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(side, -0.7, 0.0);
		glRotatef(lowerLegAngleIncr, 1.0, 0.0, 0.0);
		glRotatef(side * (-50.0 + upperLegAngleIncr), 0.0, 0.0, 1.0);
		glScalef(1.8, 0.3, 1.0);
		glutSolidSphere(0.2, 20, 50);

		//lower leg
		glPushMatrix();
			glTranslatef(side * 0.25, -0.1, -0.15);
			glRotatef(side * -35.0, 0.0, 1.0, 0.0);
			glRotatef(-35.0, 1.0, 0.0, 0.0);
			glScalef(0.2, 0.3, 1.5);
			glutSolidSphere(0.2, 20, 50);
		glPopMatrix();
	glPopMatrix();
}

void drawInsect()
{
	body();
	head();

	frontLeg(RIGHT, lowerRightLegAngleIncr, upperRightLegAngleIncr);
	middleLeg(RIGHT, lowerRightLegAngleIncr, upperRightLegAngleIncr);
	backLeg(RIGHT, lowerRightLegAngleIncr, upperRightLegAngleIncr);

	frontLeg(LEFT, lowerLeftLegAngleIncr, upperLeftLegAngleIncr);
	middleLeg(LEFT, lowerLeftLegAngleIncr, upperLeftLegAngleIncr);
	backLeg(LEFT, lowerLeftLegAngleIncr, upperLeftLegAngleIncr);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0 + topFrustumIncr, 1.5, 30.0);

	//model view matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glTranslatef(posX, posY, posZ);
	glRotatef(angle, rotateX, rotateY, rotateZ);
	drawInsect();

	glutSwapBuffers();
}

void moveLeftLegs(int dir)
{
	if (dir == UP ? armUp : armDown){
		if (dir == UP ? upperLeftLegAngleIncr < 20 : upperLeftLegAngleIncr >- 20){
			upperLeftLegAngleIncr += dir * 2;
		}
		else {
			if (dir == UP ? lowerLeftLegAngleIncr < 25 : lowerLeftLegAngleIncr >- 25){
				lowerLeftLegAngleIncr += dir * 2;
			}
			else {
				armUp = dir == UP ? false : true;
				armDown = dir == UP ? true : false;
			}
		}
	}
	else {
		if (dir == UP ? upperLeftLegAngleIncr > -20 : upperLeftLegAngleIncr < 20)
			upperLeftLegAngleIncr -= dir * 2;
		else {
			if (dir == UP ? lowerLeftLegAngleIncr > -25 : lowerLeftLegAngleIncr < 25)
				lowerLeftLegAngleIncr -= dir * 2;
			else {
				armDown = dir == UP ? false : true;
				armUp = dir == UP ? true : false;
			}
		}
	}
}

void moveRightLegs(int dir)
{
	if (dir == UP ? armUp : armDown){
		if (dir == UP ? upperRightLegAngleIncr < 20 : upperRightLegAngleIncr > -20)
			upperRightLegAngleIncr += dir * 2;
		else {
			if (dir == UP ? lowerRightLegAngleIncr < 25 : lowerRightLegAngleIncr > -25)
				lowerRightLegAngleIncr += dir * 2;
			else {
				armUp = dir == UP ? false : true;
				armDown = dir == UP ? true : false;
			}
		}
	}
	else {
		if (dir == UP ? upperRightLegAngleIncr > -20 : upperRightLegAngleIncr < 20)
			upperRightLegAngleIncr -= dir * 2;
		else {
			if (dir == UP ? lowerRightLegAngleIncr > -25 : lowerRightLegAngleIncr < 25)
				lowerRightLegAngleIncr -= dir * 2;
			else {
				armDown = dir == UP ? false : true;
				armUp = dir == UP ? true : false;
			}
		}
	}
}

//move up and down
void moveFunc(int key, int x, int y)
{
	switch (key){
	case GLUT_KEY_UP:
		moveLeftLegs(UP);
		moveRightLegs(UP);
		if (armDown)
			posY += 0.1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		moveLeftLegs(DOWN);
		moveRightLegs(DOWN);
		if (armUp)
			posY -= 0.1;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void viewPointChange(int x, int y)
{
	if (x - prevX > 0)
		angle += 3;
	else if (x - prevX < 0)
		angle -= 3;
	prevX = x;

	glutPostRedisplay();
}

void zoomChange(int x, int y)
{
	if (y - prevY > 0)
		posZ -= 0.1;
	else if (y - prevY < 0)
		posZ += 0.1;
	prevY = y;

	glutPostRedisplay();
}

void projectionChange(int x, int y)
{
	if (y - prevY > 0)
		topFrustumIncr += 0.02;
	else if (y - prevY < 0)
		topFrustumIncr -= 0.02;
	prevY = y;

	glutPostRedisplay();
}

void walkToGoal(){
	if (abs(newAngle - angle) > 0.1){
		if (newAngle > angle){
			moveRightLegs(UP);
			if (armDown)
				angle += 0.5;
		}
		else {
			moveLeftLegs(UP);
			if (armDown)
				angle -= 0.5;
		}
		glutPostRedisplay();
	}
	else if ((posX + originX - newX) == 0 && abs(-posY * 25 + originY - newY) > 0.1){
		moveLeftLegs(UP);
		moveRightLegs(UP);
		posY = newY > posY + originY ? posY - 0.01 : posY + 0.01;
		glutPostRedisplay();
	}
	else if (abs(posX * 25 + originX - newX) > 0.1){
		moveLeftLegs(UP);
		moveRightLegs(UP);

		float slope = (newY - posY - originY) / (double)(newX - posX - originX);

		//angle <= 45 degree
		if (abs(slope) <= 1){
			posX = newX > posX + originX ? posX + 0.01 : posX - 0.01;
			posY = newX > posX + originX ? posY - slope / 100.0 : posY + slope / 100.0;
		}
		//angle > 45 degree
		else {
			posX = newY > posY + originY ? posX + 1 / (slope * 100.0) : posX - 1 / (slope * 100.0);
			posY = newY > posY + originY ? posY - 0.01 : posY + 0.01;
		}
		glutPostRedisplay();
	}
}

/*
	change modelview or projection matrix when the user holds the CTRL key and press one of the mouse buttons
	or give a goal for the insect to move to
*/
void viewFunc(int button, int state, int x, int y)
{
	int modifier = glutGetModifiers();

	if (viewMode && modifier == GLUT_ACTIVE_CTRL){
		if (state == GLUT_DOWN){
			switch (button){
			case GLUT_LEFT_BUTTON:
				prevX = x;
				glutMotionFunc(viewPointChange);
				break;
			case GLUT_MIDDLE_BUTTON:
				prevY = y;
				glutMotionFunc(zoomChange);
				break;
			case GLUT_RIGHT_BUTTON:
				prevY = y;
				glutMotionFunc(projectionChange);
				break;
			default:
				break;
			}
		}
		else glutMotionFunc(NULL);
	}
	else if (moveMode){
		if (state == GLUT_DOWN){
			if (button == GLUT_LEFT_BUTTON){
				if (y < (prevY + originY))
					newAngle = floor(atan((x - prevX - originX) / (y - prevY - originY)) * 180 / M_PI);
				else newAngle = floor(atan((x - prevX - originX) / (y - prevY - originY)) * 180 / M_PI + 180);
				
				newX = x;
				newY = y;
			}
		} else glutIdleFunc(walkToGoal);
	}
}

//activate/deactivate walk to goal mode
void modeFunc(unsigned char key, int x, int y)
{
	if (key == 'm'){
		moveMode ^= 1;
		viewMode ^= 1;

		//translate insect back to original location before walking
		angle = 0.0;
		posX = 0.0;
		posY = 0.0;
		posZ = viewMode ? 10.0 : 0.0;
		prevX = 0.0;
		prevY = 0.0;
		topFrustumIncr = 0.0;
		upperLeftLegAngleIncr = 0.0;
		upperRightLegAngleIncr = 0.0;
		lowerLeftLegAngleIncr = 0.0;
		lowerRightLegAngleIncr = 0.0;
		rotateY = viewMode ? 1.0 : 0.0;
		rotateZ = viewMode ? 0.0 : 1.0;

		glutIdleFunc(NULL);
		glutMotionFunc(NULL);
		glutPostRedisplay();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);	//z-buffer included
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Phong Tran - Homework 4");

	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(modeFunc);
	glutSpecialFunc(moveFunc);
	glutMouseFunc(viewFunc);
	glutMainLoop();
	return 0;
}