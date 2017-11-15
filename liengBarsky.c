#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

int xmin = 40, ymin = 40, xmax = 100, ymax = 80;

void createLineWithRect(int x1,int y1,int x2,int y2){
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2f(xmin,ymin);
    glVertex2f(xmax,ymin);
    
    glVertex2f(xmax,ymin);
    glVertex2f(xmax,ymax);
    
    glVertex2f(xmax,ymax);
    glVertex2f(xmin,ymax);
    
    glVertex2f(xmin,ymax);
    glVertex2f(xmin,ymin);
    glEnd();
}

void clipLine(float x1, float y1, float x2, float y2) {
    float p[]={0,0,0,0};
    float q[]={0,0,0,0};
    float u[]={0,0,0,0};
    int i,dx=x2-x1,dy=y2-y1;
    
    glViewport(0,0,250,250);
	createLineWithRect(x1,y1,x2,y2);
    printf("x1 - %f   x2 - %f\ny1 - %f   y2 - %f\n\n", x1, x2, y1, y2);
    p[0]=-dx;
    p[1]=dx;
    p[2]=-dy;
    p[3]=dy;
    q[0]=x1-xmin;
    q[1]=xmax-x1;
    q[2]=y1-ymin;
    q[3]=ymax-y1;
    for(i=0;i<4;i++){
    
    	u[i]=q[i]/p[i];
    }
    float umin=1,umax=0;
    for(i=0;i<4;i++){
    
    	if(p[i]<0){
    		if(u[i]>umax)
    			umax=u[i];
    	}
    	else{
    		if(u[i]<umin)
    			umin=u[i];
    	}
    }
    int x=x1,y=y1;
    x1=x+umax*dx;
    y1=y+umax*dy;
    
    x2=x+umin*dx;
    y2=y+umin*dy;
    printf("x1 - %f   x2 - %f\ny1 - %f   y2 - %f\n\n", x1, x2, y1, y2);
    glViewport(250,250,250,250);
	createLineWithRect(x1,y1,x2,y2);
}

void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    clipLine(30, 20, 70, 80);

    glFlush();
}
	
int main(int argc, char * * argv) {
    glutInit( & argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Nikunj Kumar Gupta - 500044730");
    glClearColor(0.0, 0.0, 0.0, 0);
    glColor3f(1.0, 1.0, 1.0);
    gluOrtho2D(0, 250, 0, 250);

    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
