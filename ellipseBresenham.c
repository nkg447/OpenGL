#include<stdio.h>
#include<GL/gl.h>
#include<GL/glut.h>

int cx=200,cy=200;

void setPixel(GLint x, GLint y) {
  glBegin(GL_POINTS);
  printf("%d %d\n",x,y);
  glVertex2i(x+cx,y+cy);
  glVertex2i(x+cx,-y+cy);
  glVertex2i(-x+cx,y+cy);
  glVertex2i(-x+cx,-y+cy);

  glEnd();
}


void createEllipse(int rx,int ry)
{
  int a=rx,b=ry;
  int x=0,y=ry;
  float d1=b*b+a*a*((1/4)-b);
  setPixel(x,y);
	while((x*b*b)<=(y*a*a)){
		if(d1<0){
			d1=d1+b*b*(2*x+3);
		}
		else{
			d1=d1+b*b*(2*x+3)-a*a*(2*y-2);
			y=y-1;
		}
		x=x+1;
		setPixel(x,y);
	}

	float d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;

	while(y!=0){
		if(d2<0){
			d2=d1+2*b*b*(x+1)-a*a*(2*y-3);
			x=x+1;
		}
		else{
			d2=d2+a*a*(3-2*y);

		}
		y=y-1;
		setPixel(x,y);
	}
  glFlush();
}


void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
	createEllipse(80,20);
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
