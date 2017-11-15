#include<stdio.h>
#include<GL/gl.h>
#include<GL/glut.h>

void setPixel(GLint x, GLint y) {
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
}


void createLine(float x1, int y1, int x2, int y2)
{
  float dx=x2-x1;
  float dy=y2-y1;
  float m=dx/dy;
  

  dx=abs(dx);
  dy=abs(dy);
  setPixel(x1,y1);
	printf("%f\n",m);
  
      while(y1!=y2){
          y1=y1+1;
	x1=x1+m;
          setPixel(abs(x1),y1);
	printf("%f %d\n",x1,y1);
      }
  

  glFlush();
}


void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  createLine(40,50,80,100);

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
