#include<stdio.h>
#include<GL/gl.h>
#include<GL/glut.h>

int cx=100,cy=100;
void setPixel(GLint x, GLint y) {
  glBegin(GL_POINTS);
  
  glVertex2i(x+cx,y+cy);
  glVertex2i(x+cx,-y+cy);
  glVertex2i(-x+cx,y+cy);
  glVertex2i(-x+cx,-y+cy);
  
  glEnd();
}


void createCircle(int r)
{
  int x=0,y=r;
  int h=1-r;
  	setPixel(x,y);
  	setPixel(y,x);
  	while(y>x){
  		if(h<0){
  			h=h+2*x+3;
  		}
  		else{
  			h=h+2*(x-y)+5;
  			y=y-1;
  		}
  		x=x+1;
  		setPixel(x,y);
  		setPixel(y,x);
  	}

  glFlush();
}


void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
	createCircle(100);
  glFlush();
}



int main(int argc, char **argv)
{
  glutInit(&argc, argv);


  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Nikunj Kumar Gupta - 500044730");
  glClearColor(0.0,0.0,0.0,0);
  glColor3f(1.0,1.0,1.0);
  gluOrtho2D(0,640,0,480);


  glutDisplayFunc(draw);
  glutMainLoop();
  return 0;
}
