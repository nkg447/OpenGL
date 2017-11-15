#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

int xmin = 40, ymin = 40, xmax = 100, ymax = 80;

void setPixel(GLint x, GLint y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);

    glEnd();
}

int getRegion(float x, float y) {
    int region = 0;
    if (x < xmin) region = region | (1 << 0);
    if (x > xmax) region = region | (1 << 1);
    if (y < ymin) region = region | (1 << 2);
    if (y > ymax) region = region | (1 << 3);
    return region;

}


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
    int r1 = getRegion(x1, y1);
    int r2 = getRegion(x2, y2);
    int x, y;
   
	glViewport(0,0,250,250);
	createLineWithRect(x1,y1,x2,y2);
    
    while (((r1 | r2) != 0) && ((r1 & r2) == 0)) {
        if (r1 != 0) {
            if ((r1 | 1) == r1) {
                y = (((y2 - y1) * (xmin - x1) / (x2 - x1)) + y1);
                x = xmin;
            } else if ((r1 | 2) == r1) {
                y = (((y2 - y1) * (xmax - x1) / (x2 - x1)) + y1);
                x = xmax;
            } else if ((r1 | 4) == r1) {
                x = (((ymin - y1) * (x2 - x1) / (y2 - y1)) + x1);
                y = ymin;
            } else {
                x = (((ymax - y1) * (x2 - x1) / (y2 - y1)) + x1);
                y = ymax;
            }
            x1 = x;
            y1 = y;
        } else {
            if ((r2 | 1) == r2) {
                y = (((y2 - y1) * (xmin - x1) / (x2 - x1)) + y1);
                x = xmin;
            } else if ((r2 | 2) == r2) {
                y = (((y2 - y1) * (xmax - x1) / (x2 - x1)) + y1);
                x = xmax;
            } else if ((r2 | 4) == r2) {
                x = (((ymin - y1) * (x2 - x1) / (y2 - y1)) + x1);
                y = ymin;
            } else {
                x = (((ymax - y1) * (x2 - x1) / (y2 - y1)) + x1);
                y = ymax;
            }
            x2 = x;
            y2 = y;
        }
        r1 = getRegion(x1, y1);
        r2 = getRegion(x2, y2);
    }
    printf("x1 - %f   x2 - %f\ny1 - %f   y2 - %f\n\n", x1, x2, y1, y2);
    
	glViewport(250,250,250,250);
	createLineWithRect(x1,y1,x2,y2);
}

void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    clipLine(70, 90, 110, 40);

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
