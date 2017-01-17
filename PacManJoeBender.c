/*
 *  Pacman Final Project
 *  An imitation of the classic arcade game PacMan
 *	Created by Joe Bender
 *
 *	Use W,A,S,D to move and spacebar to halt the PacMan agent.
 *
 *  Deficiencies:
 *	Maze lacks collision and dots do not disappear after being eaten.
 */


//include statements
#include <math.h>
#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>

//variable declaration
float rad = 0.04 ;
float xc=.45, yc=.45, xv=0 , yv=0;
float g = -1.0 ;
float dt = 0.005 ; //speed of pacman
float time = 0.0 ;
float degrees, angle ;
float damp=1.05 ;
int n=330 ;
int pos = 0;
int oldpos = 0;
int mouth = 1;
int i,j,k ;
int a = 330;
int newvar = 0;
float sz = 0.1;
float gap = 0;
//char dpts[20] ; Variable to display score



//maze array

int walls[10][10][4] =
{
{{1,0,0,1},{1,0,1,0},{1,0,1,0},{1,0,1,0},{1,0,0,0},{1,0,0,0},{1,0,1,0},{1,0,1,0},{1,0,1,0},{1,1,0,0}},
{{0,1,0,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{0,1,0,1}},
{{0,1,0,1},{1,1,1,1},{1,0,0,1},{1,0,1,0},{1,0,1,0},{0,1,0,1},{1,1,1,1},{1,1,0,1},{1,1,1,1},{0,1,0,1}},
{{0,0,0,1},{1,1,1,1},{0,1,0,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{0,1,0,1},{1,1,1,1},{0,1,0,1}},
{{0,1,0,1},{1,1,1,1},{0,0,1,0},{1,0,1,0},{1,1,1,1},{1,1,0,0},{1,1,1,1},{0,1,0,1},{1,1,1,1},{0,1,0,1}},
{{0,1,0,1},{1,1,1,1},{1,1,1,0},{1,1,0,1},{1,1,1,1},{0,1,0,1},{1,1,1,1},{1,1,0,1},{1,1,1,1},{0,1,0,0}},
{{0,1,0,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,0,1},{1,1,1,1},{1,1,0,1},{1,1,1,1},{0,1,0,1}},
{{0,1,0,1},{1,1,1,1},{1,0,1,1},{1,0,1,0},{1,0,0,0},{1,1,0,1},{1,1,1,1},{1,1,0,1},{1,1,1,1},{0,1,0,1}},
{{0,1,0,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{0,1,0,1}},
{{0,0,1,1},{1,0,1,0},{1,0,1,0},{1,0,1,0},{0,0,1,0},{1,0,1,0},{1,0,1,0},{1,0,1,0},{1,0,1,0},{0,1,1,0}}
};




void init()
{

glClearColor (0.0, 0.0, 0.0, 0.0);

         glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        glOrtho(0, 1.0, 0, 1.0, -1.0, 1.0);

}


void display() {



glClear(GL_COLOR_BUFFER_BIT) ;

//draw dots
glColor3f(0.0, 0.0, 1.0);
for (i=0; i<10; i++)
{
	for (j=0; j<10; j++)
	{
		glBegin(GL_POLYGON) ;
		glColor3f(1.0, 1.0, 1.0);
		//glVertex2f(xc, yc) ;
		n=360;
		 for (k=0 ; k<n ; ++k) {
			 angle = (3.14159*k)/180.0 ;
			 glVertex2f(.015*cos(angle)+(i+.5)*sz, .015*sin(angle)+(j+.5)*sz) ;
			}
		glEnd() ;
	}
}
//draw maze
glColor3f(0.0, 0.0, 1.0);
for (i=0; i<10; i++)
{
	for (j=0; j<10; j++)
	{
		for(k=0; k<4;k++)
		{
			if (walls[i][j][k] == 0)
			{
				glBegin(GL_QUADS);
				glVertex2f(i*(sz+gap), j*(sz+gap));
				glVertex2f(i*(sz+gap), (j+1)*sz+j*gap);
	 			glVertex2f((i+1)*sz+i*gap, (j+1)*sz+j*gap);
	 			glVertex2f((i+1)*sz+i*gap, j*(sz+gap));
				glEnd();
			}
			else
			{
			    //placeholder
			}

		}
	}
}





if ( pos == 0 )
{
		//static pacman agent
		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 0.0);
		n=360;
		for (k=0 ; k<n ; ++k)
		{
			 angle = (3.14159*k)/180.0 ;
			 glVertex2f(rad*cos(angle)+xc, rad*sin(angle)+yc) ;
		}

		glEnd() ;

}
else if ( pos == 1 )
{


		//using the w key to move
		glBegin(GL_POLYGON) ;
		glColor3f(1.0, 1.0, 0.0);
		glVertex2f(xc, yc) ;
		n  = 330;
			for (k=30 ; k<n ; ++k){
			 angle = -((3.14159*k)/180.0) ;
			 glVertex2f(rad*sin(angle)+xc, rad*cos(angle)+yc) ;
			 k++;
			}


		glVertex2f(xc, yc) ;

		glEnd() ;
		newvar++;

}
else if ( pos == 2 )
{
		//using the d key to move
		glBegin(GL_POLYGON) ;
		glColor3f(1.0, 1.0, 0.0);
		glVertex2f(xc, yc) ;
		n = 330;
		 for (k=30 ; k<n ; ++k) {
			 angle = (3.14159*k)/180.0 ;
			 glVertex2f(rad*cos(angle)+xc, rad*sin(angle)+yc) ;
			}

		glVertex2f(xc, yc) ;

		glEnd() ;
		newvar++;
}
else if ( pos == 3 )
{
	//using the s key to move
		glBegin(GL_POLYGON) ;
		glColor3f(1.0, 1.0, 0.0);
		glVertex2f(xc, yc) ;
		n = 330;
		 for (k=30 ; k<n ; ++k) {
			 angle = (3.14159*k)/180.0 ;
			 glVertex2f(rad*sin(angle)+xc, rad*-cos(angle)+yc) ;
			}

		glVertex2f(xc, yc) ;

		glEnd() ;


		newvar++;
}
else if ( pos == 4 )
{
	//using the a key to move
		glBegin(GL_POLYGON) ;
		glColor3f(1.0, 1.0, 0.0);
		glVertex2f(xc, yc) ;
		n = 330;
		 for (k=30 ; k<n ; ++k) {
			 angle = (3.14159*k)/180.0 ;
			 glVertex2f(rad*-cos(angle)+xc, rad*sin(angle)+yc) ;
			}

		glVertex2f(xc, yc) ;

		glEnd() ;

		newvar++;
}
else
{
	//placeholder
}

//recreate full circle
if ((newvar/20)%2)
{
	//static
		glBegin(GL_POLYGON) ;
		glColor3f(1.0, 1.0, 0.0);
		n=360;
		 for (k=0 ; k<n ; ++k) {
			 angle = (3.14159*k)/180.0 ;
			 glVertex2f(rad*cos(angle)+xc, rad*sin(angle)+yc) ;
			}
		glEnd() ;
}

glFlush() ;
glutSwapBuffers() ;
}


//setting up directional movement
void keyb(unsigned char key, int xx, int yy) {

if (key=='w'){
	yv = 1;
	xv = 0;
	pos = 1;
}
if (key=='s'){
	yv = -1;
	xv = 0;
	pos = 3;
}
if (key=='a'){
	xv = -1;
	yv = 0;
	pos = 4;
}
if (key=='d'){
	xv = 1;
	yv = 0;
	pos = 2;
}
if (key==' '){
	xv = 0;
	yv = 0;
	pos = 0;
}

}



void idle() {
  time += dt ;
  xc += xv*dt ;
  yc += yv*dt ;


  //below allows for collision with wall
  if(xc<=rad-0.001) xv*=0 ;
  if(xc>=1.0-rad) xv*=0 ;
  if(yc<=rad-0.001) yv*=0 ;
  if(yc>=1.0-rad) yv*=0 ;
  glutPostRedisplay() ;
}

/*  This was an attempt to display the score

void writescore()
{


int ii;
float ix;

glColor3f(1.0,0.5,0.5);
sprintf(dpts,"SCORE %6d", A variable for points would go here);

for (ii=0; ii<20 ; ++ii)
{
ix = (float)ii/400.0;
glRasterPos2f(.04+30*ix,.05);
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, dpts[ii]);
}
}
*/


int main(int argc, char** argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("PacMan Game - Joe Bender");
	glutKeyboardFunc(keyb);
        glutIdleFunc(idle) ;
	glutDisplayFunc(display);
        init() ;
	glutMainLoop();

}

