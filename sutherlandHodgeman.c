#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
typedef struct Point Point;
struct Point{
    float x,y;
};

int xmin = 40, ymin = 40, xmax = 100, ymax = 80;
static Point arr[100];
static int k;

void createLineWithRect(Point p1,Point p2){
    glBegin(GL_LINES);
    glVertex2f(p1.x,p1.y);
    glVertex2f(p2.x,p2.y);
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

void drawFig(Point vtx[],int n){
    
    for(int i=0;i<n;i++){
        printf("(%f, %f) ",vtx[i].x,vtx[i].y);
        createLineWithRect(vtx[i],vtx[(i+1)%n]);
    }
    printf("\n");
}

void leftClip(Point p1,Point p2){
    float m=(p1.y-p2.y)/(p1.x-p2.x);
    //both in
    if(p1.x>=xmin && p2.x>=xmin){
        arr[k].x=p2.x;
        arr[k].y=p2.y;
        k++;
    }
    //out->in
    else if(p1.x<xmin && p2.x>=xmin){
        arr[k].x=xmin;
        arr[k].y=p1.y+m*(xmin-p1.x);
        arr[k+1].x=p2.x;
        arr[k+1].y=p2.y;
        k+=2;
    }
    //in->out
    else if(p1.x>=xmin && p2.x<xmin){
        arr[k].x=xmin;
        arr[k].y=p1.y+m*(xmin-p1.x);
        k++;
    }
}

void rightClip(Point p1,Point p2){
    float m=(p1.y-p2.y)/(p1.x-p2.x);
    //both in
    if(p1.x<=xmax && p2.x<=xmax){
        arr[k].x=p2.x;
        arr[k].y=p2.y;
        k++;
    }
    //out->in
    else if(p1.x>xmax && p2.x<=xmax){
        arr[k].x=xmax;
        arr[k].y=p1.y+m*(xmax-p1.x);
        arr[k+1].x=p2.x;
        arr[k+1].y=p2.y;
        k+=2;
    }
    //in->out
    else if(p1.x<=xmax && p2.x>xmax){
        arr[k].x=xmax;
        arr[k].y=p1.y+m*(xmax-p1.x);
        k++;
    }
}

void bottomClip(Point p1,Point p2){
    float m=(p1.y-p2.y)/(p1.x-p2.x);
    //both in
    if(p1.y>=ymin && p2.y>=ymin){
        arr[k].x=p2.x;
        arr[k].y=p2.y;
        k++;
    }
    //out->in
    else if(p1.y<ymin && p2.y>=ymin){
        arr[k].y=ymin;
        arr[k].x=p1.x+(ymin-p1.y)/m;
        arr[k+1].x=p2.x;
        arr[k+1].y=p2.y;
        k+=2;
    }
    //in->out
    else if(p1.y>=ymin && p2.y<ymin){
        arr[k].y=ymin;
        arr[k].x=p1.x+(ymin-p1.y)/m;
        k++;
    }
}

void topClip(Point p1,Point p2){
    float m=(p1.y-p2.y)/(p1.x-p2.x);
    //both in
    if(p1.y<=ymax && p2.y<=ymax){
        arr[k].x=p2.x;
        arr[k].y=p2.y;
        k++;
    }
    //out->in
    else if(p1.y>ymax && p2.y<=ymax){
        arr[k].y=ymax;
        arr[k].x=p1.x+(ymax-p1.y)/m;
        arr[k+1].x=p2.x;
        arr[k+1].y=p2.y;
        k+=2;
    }
    //in->out
    else if(p1.y<=ymax && p2.y>ymax){
        arr[k].y=ymax;
        arr[k].x=p1.x+(ymax-p1.y)/m;
        k++;
    }
}



void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    Point *vtx;
    int size;
    scanf("%d",&size);
    vtx=malloc(size*sizeof(Point));
    for(int i=0;i<size;i++){
        scanf("%f %f",&vtx[i].x,&vtx[i].y);
    }
    glViewport(0,0,250,250);
    drawFig(vtx,size);

    /*LEFT CLIP*/
    k=0;
    for(int i=0;i<size;i++){
        leftClip(vtx[i],vtx[(i+1)%size]);
    }

    for(int i=0;i<k;i++){
        vtx[i].x=arr[i].x;
        vtx[i].y=arr[i].y;
    }
    size=k;

    /*RIGHT CLIP*/
    k=0;
    for(int i=0;i<size;i++){
        rightClip(vtx[i],vtx[(i+1)%size]);
    }

    for(int i=0;i<k;i++){
        vtx[i].x=arr[i].x;
        vtx[i].y=arr[i].y;
    }
    size=k;

    /*BOTTOM CLIP*/
    k=0;
    for(int i=0;i<size;i++){
        bottomClip(vtx[i],vtx[(i+1)%size]);
    }

    for(int i=0;i<k;i++){
        vtx[i].x=arr[i].x;
        vtx[i].y=arr[i].y;
    }
    size=k;

    /*TOP CLIP*/
    k=0;
    for(int i=0;i<size;i++){
        topClip(vtx[i],vtx[(i+1)%size]);
    }

    for(int i=0;i<k;i++){
        vtx[i].x=arr[i].x;
        vtx[i].y=arr[i].y;
    }
    size=k;
    
    glViewport(250,250,250,250);
    drawFig(vtx,size);
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