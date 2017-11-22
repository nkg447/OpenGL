
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>
#define PI 3.14159265

int WINDOW_WIDTH = 640;   // window screen width
int WINDOW_HEIGHT = 640;  // window screen height

int X1, Y1, X2, Y2;
double transMatrix[3][3];
int n;
int *points[2];

void multiplyMatrix(double a[3][3], double b[3][1],
                    double c[3][1]) {  // multiply c=a*b
  for (int i = 0; i < 3; i++) {
    double sum = 0;
    for (int k = 0; k < 3; k++) {
      sum += a[i][k] * b[k][0];
    }
    c[i][0] = sum;
  }
}

void transform(double x, double y, int *xF, int *yF) {
  double point[3][1];
  point[0][0] = x;
  point[1][0] = y;
  point[2][0] = 1;
  double transPoint[3][1];
  multiplyMatrix(transMatrix, point, transPoint);
  *xF = round(transPoint[0][0]);
  *yF = round(transPoint[1][0]);
}

void simpleDDA() {
  double dx = (X2 - X1);
  double dy = (Y2 - Y1);
  double steps, dxStep, dyStep, x = X1, y = Y1;
  steps = (abs(dx) > abs(dy)) ? (abs(dx)) : (abs(dy));
  dxStep = dx / steps;
  dyStep = dy / steps;

  glVertex2d(round(x), round(y));

  glVertex2d(x, y);
  int k;
  for (k = 0; k < steps; k++) {
    x += dxStep;
    y += dyStep;
    glVertex2d(round(x), round(y));
  }
}

void transformations2D(void) {
  
 
  glBegin(GL_POINTS);

  int i = 0;
  for (i = 0; i < n; i++) {
    X1 = points[i][0];
    X2 = points[(i + 1) % n][0];

    Y1 = points[i][1];
    Y2 = points[(i + 1) % n][1];


    //simpleDDA();

    transform(points[i][0], points[i][1], &X1, &Y1);
    transform(points[(i + 1) % n][0], points[(i + 1) % n][1], &X2, &Y2);
    
    simpleDDA();
  }
  glEnd();
  glFlush();
}


void func(){
  glClear(GL_COLOR_BUFFER_BIT);
  glViewport(0,0,250,250);
  transformations2D();
  double angle=80;
  //scanf("%lf", &angle);
  angle = angle * PI / 180.0;
  transMatrix[0][0] = cos(angle);
  transMatrix[0][1] = -sin(angle);
  transMatrix[1][0] = sin(angle);
  transMatrix[1][1] = cos(angle);
  glViewport(250,0,250,250);
  transformations2D();

  transMatrix[0][0]=0;
  transMatrix[1][1]=0;
  transMatrix[1][0]=2;
  transMatrix[0][1]=2;
  glViewport(0,250,250,250);
  transformations2D();

  transMatrix[0][0]=3;
  transMatrix[1][1]=1;
  transMatrix[1][0]=0;
  transMatrix[0][1]=0;
  glViewport(250,250,250,250);
  transformations2D();
}


int main(int argc, char **argv) {
  memset(transMatrix, 0, sizeof(transMatrix));
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == j) {
        transMatrix[i][j] = 1;
      }
    }
  }

  scanf("%d", &n);
  int i = 0;
  for (i = 0; i < n; i++) {
    points[i] = (int *)malloc(2 * sizeof(int));
    scanf("%d %d", &points[i][0], &points[i][1]);
    points[i][1]*=2;
  }
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("2-D Transformations");
  gluOrtho2D(-WINDOW_WIDTH / 2, WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2,WINDOW_WIDTH / 2);
  glutDisplayFunc(func);
  glutMainLoop();

  return 0;
}
