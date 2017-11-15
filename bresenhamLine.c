#include<stdio.h>
#include<GL/gl.h>
#include<GL/glut.h>

void setPixel(GLint x, GLint y) {
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
}


void createLine(int x1, int y1, int x2, int y2)
{
  int dx=x2-x1;
  int dy=y2-y1;
  int d,de,dne,dl,dr;
  int ysign=1,xsign=1;
  if(dx<1){
      xsign=-1;
  }
  if(dy<1){
      ysign=-1;
  }

  dx=abs(dx);
  dy=abs(dy);
  setPixel(x1,y1);

  //when m<=1
  if(dy<=dx){
      d=2*dy-dx;
      de=2*dy;
      dne=2*(dy-dx);
      while(y1!=y2){
          if(d>0){
              d=d+dne;
              y1=y1+ysign;
          }
          else{
              d=d+de;
          }
          x1=x1+xsign;
          setPixel(x1,y1);

      }
  }//when m>1
  else{
      d=dy-2*dx;
      dl=-2*dx;
      dr=2*(dy-dx);
      while(y1!=y2){
          if(d>=0){
              d=d+dl;
          }
          else{
              d=d+dr;
              x1=x1+xsign;
          }
          y1=y1+ysign;
          setPixel(x1,y1);
      }
  }

  glFlush();
}


void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  createLine(0,0,80,50);
  createLine(0,0,60,80);


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
