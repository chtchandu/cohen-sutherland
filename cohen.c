#include<stdio.h>
#include<GL/glut.h>

#define outcode int

double xmin=50,ymin=50,xmax=100,ymax=100;
double xvmin=200,yvmin=200,xvmax=300,yvmax=300;

const int right=8;
const int left=2;
const int top=4;
const int bottom=1;

int x1,x2,y1,y2;

outcode compute(double x,double y);

void cohen(double x0,double y0,double x1,double y1)
{
    outcode outcode0,outcode1,outcodeout;
    int accept=0,done=0;
    
    outcode0=compute(x0,y0);
    outcode1=compute(x1,y1);
    
    do
    {
        if(!(outcode0|outcode1))
        {
            accept=1;
            done=1;
        }
        
        else if( outcode0 &  outcode1)
        {
            done = 1;
        }
        
        else
        {
            double x,y;
            outcodeout=outcode0?outcode0:outcode1;
            
            if(outcodeout & top)
            {
                x=x0+(x1-x0)*(ymax-y0)/(y1-y0);
                y=ymax;
            }
            
            else if(outcodeout & bottom)
            {
                x=x0+(x1-x0)*(ymin-y0)/(y1-y0);
                y=ymin;
            }
            
            else if(outcodeout & right)
            {
                y=y0+(y1-y0)*(xmax-x0)/(x1-x0);
                x=xmax;
            }
            
            else
            {
                y=y0+(y1-y0)*(xmin-x0)/(x1-x0);
                x=xmin;
            }
            
            if(outcodeout==outcode0)
            {
                x0=x;
                y0=y;
                outcode0=compute(x0,y0);
            }
            
            else
            {
                x1=x;
                y1=y;
                outcode1=compute(x1,y1);
            }
        }
    }while(!done);
    
    if(accept)
    {
        double sx=(xvmax-xvmin)/(xmax-xmin);
        double sy=(yvmax-yvmin)/(ymax-ymin);
        
        double vx0=xvmin+(x0-xmin)*sx;
        double vy0=yvmin+(y0-ymin)*sy;
        double vx1=xvmin+(x1-xmin)*sx;
        double vy1=yvmin+(y1-ymin)*sy;
        
        glColor3f(1,0,0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(xvmin,yvmin);
        glVertex2f(xvmax,yvmin);
        glVertex2f(xvmax,yvmax);
        glVertex2f(xvmin,yvmax);
        glEnd();
        
        glColor3f(0,0,1);
        glBegin(GL_LINES);
        glVertex2d(vx0,vy0);
        glVertex2d(vx1,vy1);
        glEnd();
    }
}


outcode compute(double x,double y)
{
    outcode code=0;
    
    if(y>ymax)
    {
        code|=top;
    }
    else if(y<ymin)
    {
        code|=bottom;
    }
    if(x>xmax)
    {
        code|=right;
    }
    if(y<ymin)
    {
        code|=left;
    }
    return code;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex2d(x1,y1);
    glVertex2d(x2,y2);
    glEnd();  
    
    glColor3f(0,0,1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin,ymin);
    glVertex2f(xmax,ymin);
    glVertex2f(xmax,ymax);
    glVertex2f(xmin,ymax);
    glEnd();
    
    cohen(x1,y1,x2,y2);
    
    glFlush();
}

void myinit()
{
    glClearColor(1,1,1,1);
    glColor3f(1,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
}

void main(int argc, char **argv)
{
    printf("enter the end points\n");
    scanf("%d%d%d%d",&x1,&x2,&y1,&y2);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("cs");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
}

