#include<stdio.h>
#include<GL/gl.h>
#include<GL/glut.h>

void setPixel(GLint x, GLint y) {
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
}


void createLine(float m, float c)
{
  
  if(m>1){
  float x1=0,y1=0;
  	while(y1<480){
  		x1=(y1-c)/m;
  		setPixel(abs(x1),abs(y1));
  		y1++;
  	}
  }else{
  	float x1=0,y1=0;
  	while(x1<640){
  		y1=m*x1+c;
  		setPixel(abs(x1),abs(y1));
  		x1++;
  	}
  }

  glFlush();
}


void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  createLine(0.2,0);
  createLine(10,0);
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
