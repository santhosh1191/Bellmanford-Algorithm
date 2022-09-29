#include<process.h>   
#include<string.h>
#include<stdlib.h>
#include <glut.h> 
#include <gl.h>
#include<math.h>
#include<stdio.h>
#include<windows.h>       
#include<MMSystem.h>
//#include "RGBPixMap.h"
#define GL_PI 3.14
#define MAX 25
#define INFINITY 999
//RGBpixmap pix[6];
int width=480;
int height=640;
void keyboard(unsigned char key, int a, int b);
void displayx();
void Aboutmethod();
void Aboutintro();
void display();
void displayM();
void initial();
void drawbold();
int n,i=1,a[25],b[25],cost[25][25],tree[25][25],src,l[2],dist[10];
char s[20],*s1;
void *currentfont;
float SCREEN_Y = 500, YD = SCREEN_Y / 12;
//BELLMAN VARIABLESf
typedef struct {
   int u, v, w;
} Edge;
const int NODES = 5 ; /* the number of nodes */
int EDGES=0;            /* the number of edges */
Edge edges[32];       /* large enough for n <= 2^NODES=32 */
int d[32];            /* d[i] is the minimum distance from source node s to node i */


//FUNCTION TO SELECT BITMAP FONT
void setFont(void *font)
{
    currentfont=font;
}
//FUNCTION TO DRAW BITMAP string at (x,y)
void drawstring(GLfloat x,GLfloat y,char *string)
{
  char *c;
  glRasterPos2f(x,y);
  for(c=string;*c!='\0';*c++)
  {
	  glLineWidth(5.0);
    glutBitmapCharacter(currentfont,*c);
  }
}
void drawbold(GLfloat x,GLfloat y,GLfloat z,const char* string)
{
glTranslatef(x,y,z);
glScaled(0.17,0.3,0.0);
const char *c;
 //glRasterPos2f(x,y,z);
  for(c=string;*c!='\0';c++)
  {
    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,*c);
  }
}
//delay function
void delay()
{
    for(int i=0;i<22000;i++)
       for(int j=0;j<22000;j++);
}

void square(int x1, int y1, int x2, int y2)
{
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	glVertex2f(x2, y1);
	glEnd();
}
void drawoutline(int x1, int y1, int x2, int y2)
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glLineWidth(3.5f);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(x1, y1);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(x1, y2);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2f(x2, y2);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(x2, y1);
	glEnd();
}

//DISPLAY FUNCTION FOR TITLE PAGE
void title()
{
    /*glLineWidth(3.0);
    glColor3f(1.0,2.0,0.5);
    glBegin(GL_LINE_LOOP);
    glVertex2f(10,10);
    glVertex2f(10,490);
    glVertex2f(490,490);
    glVertex2f(490,10);
    glEnd();*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 0.0, 5.0);
	drawstring(230, 445, "SDM INSTITUTE OF TECHNOLOGY");
	//drawbold(230, 435,0.0, "SDM INSTITUTE OF TECHNOLOGY");

	glColor3f(0.5, 2.0, 0.0);
	drawstring(170, 415, "DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
	glColor3f(0.5, 2.0, 0.0);
	drawstring(170, 385, "COMPUTER GRAPHICS LABORATORY WITH MINI PROJECT ");
	glColor3f(1.0,0.0, 5.0);
	drawstring(275, 355, "A MINI PROJECT ON");
	glColor3f(1.0, 1.0, 0.0);
	drawstring(235, 325, "*BELLMANFORD ALGORITHM*");

	glColor3f(0.0, 1.0, 0.8);
	drawstring(45, 210, "SUBMITTED BY:");
	glColor3f(1.0, 0.5, 0.0);
	drawstring(45, 170, "SANTHOSH K(4SU19CS083)");
	drawstring(45, 150, "SATHEESH BHAT(4SU19CS084)");
	drawstring(45, 130, "SATHVICK M(4SU19CS085)");
	drawstring(45, 110, "SRINIVAS S(4SU19CS101)");
	glColor3f(0.0, 1.0, 0.8);
	drawstring(500, 195, "GUIDED BY:");
	glColor3f(1.0, 0.5, 0.0);
	drawstring(500, 170, "Prof.Arjun K");
	glColor3f(0.0, 1.0, 0.8);
	drawstring(260, 90, "<<<[PRESS 'H' TO HELP]>>>");
	glColor3f(1.0,0.5,0.5);
	square(350, (SCREEN_Y / 2) + 33, 270, SCREEN_Y / 2 + 30 + YD - 3);//box2
	glColor3f(0.0, 0.0, 0.0);
	drawstring(285.0, SCREEN_Y / 2 + 47, "Enter vertices");//label
	drawoutline(350, (SCREEN_Y / 2) + 34, 270, SCREEN_Y / 2 + 30 + YD - 3);

	 glColor3f(1.0f, 0.0f, 0.0f);
     glPointSize(20);
            glBegin(GL_POINTS);
            glVertex2f(312 ,240);
            glEnd();

	glBegin( GL_LINES);
	glColor3f(1.0,1.0,0.0);
 glVertex3f(312.0f, 150.0f, 0.0f);
 glColor3f(0.0,1.0,1.0);
 glVertex3f(312.0f, 283.0f, 0.0f);
 glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glColor3f(1.0, 0.5, 0.5);
	square(350, (SCREEN_Y / 2) - 47, 270, SCREEN_Y / 2 - 50 + YD - 3);//box2
	glColor3f(0.0, 0.0, 0.0);
	drawstring(285, (SCREEN_Y / 2) - 33, "Cost matrix");//label
	drawoutline(350, (SCREEN_Y / 2) - 47, 270, SCREEN_Y / 2 - 50 + YD - 3);

	 glColor3f(1.0f, 0.0f, 0.0f);
     glPointSize(20);
            glBegin(GL_POINTS);
            glVertex2f(312 ,160);
            glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glColor3f(1.0, 0.5, 0.5);
	square(350, SCREEN_Y / 2 - 128, 270, SCREEN_Y / 2 - 131 + YD - 3);//box2
	glColor3f(0.0, 0.0, 0.0);
	drawstring(285, (SCREEN_Y / 2) - 114, "Display Graph");//label
	drawoutline(350, (SCREEN_Y / 2) - 128, 270, SCREEN_Y / 2 - 131 + YD - 3);
	glutKeyboardFunc(keyboard);
	glFlush();
}
/*void help() {
	glColor3f(1.0, 0.5, 1);
	drawstring(263, 415, "BELLMAN FORD ALGORITHM");
	glColor3f(1.5, 1.0, 1.0);
	drawstring(50, 375, "INSTRUCTIONS:");
	drawstring(50, 370, "__");
	glColor3f(1, 0.5, 0.5);
	drawstring(60, 348, "Keyboard Functions");
	drawstring(60, 342, " ------------- ");
	glColor3f( 1.0,1.0,0.0);
	drawstring(60, 325, "*Press 'X' to start");
	drawstring(60, 307, "*Press 'Right Mouse Button' to start the implementation");
	drawstring(60, 289, "*Press 'h' for help window");
	drawstring(60, 271, "*Press 'q' for quit");
	drawstring(60, 253, "*Press 'm' for main menu");
	drawstring(60, 181, "*press any key to close the terminal");
	glColor3f(1, 0.5,0.5);
	drawstring(60, 158, "Mouse Function");
	drawstring(60, 152, "------------ ");
	glColor3f( 0.5,1,1);
	drawstring(60, 135, "*left click on mouse to go to the previous window");
	glutMouseFunc(MOUSE2);
	glutKeyboardFunc(keyboard);
	glFlush();

}*/
void MOUSE2(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON&&state==GLUT_DOWN);
	title();
}
void aboutbtn(int btn,int state,int x,int y)
{
if(btn==GLUT_LEFT_BUTTON&&state==GLUT_DOWN);
Aboutmethod();
}


	void keyboard(unsigned char key, int a, int b) {
		if (key == 'S') {

		//glClearColor(1.0, 1.0, 1.0, 1.0);
		//glClear(GL_COLOR_BUFFER_BIT);
		glutDisplayFunc(display);
		glutPostRedisplay();
		//initial();
	}
	if (key == 'H') {

		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		displayx();

	}

	/*if (key == 'h') {
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		help();
	}
	if (key == 'n') {
		glClear(GL_COLOR_BUFFER_BIT);

	}
	*/
	if (key == 'q')
	{
		exit(0);
	}
	if (key == '?') {
		Aboutintro();

	}
	}
	
//DISPLAY FUNCTION FOR INITIALIZING (DRAWING) THE  INPUT AND OUTPUT AREAS
void initial()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    setFont(GLUT_BITMAP_HELVETICA_18);

    glColor3f(0.0,0.0,0.0);
    drawstring(15,475,"Input Area");
    drawstring(255,475,"Output Area");
    
    glColor3f(0.0,0.0,0.0);
    glLineWidth(3.0);
    glBegin(GL_LINES);
	 glColor3f(0.1,0.0,1.0);
                          glVertex2f(10,10);
						  glColor3f(0.9,0.5,0.0);
                          glVertex2f(10,490);
						   glColor3f(0.1,0.0,1.0);
                          
                          glVertex2f(10,490);
						  glColor3f(0.9,0.5,0.0);
                          glVertex2f(490,490);
						  glColor3f(0.1,0.0,1.0);
                          
                          glVertex2f(490,490);
						   glColor3f(0.9,0.5,0.0);
                          glVertex2f(490,10);
						     glColor3f(0.1,0.0,1.0);
                          
                          glVertex2f(490,15);
						    glColor3f(0.9,0.5,0.0);
                          glVertex2f(10,15);
                            glColor3f(0.1,0.0,1.0);

							
                          glVertex2f(250,15);
						  glColor3f(0.9,0.5,0.0);
                          glVertex2f(250,490);
						  glColor3f(0.1,0.0,1.0);
    glEnd();

    glFlush();
}



//BLANK DISPLAY FUNCTION
void display()
{
glFlush();
glutKeyboardFunc(keyboard);
}
void displayx (void)
{
	glClearColor(0.1,0.0,0.0,1.0);
	glClearColor(0.0,0.1,0.0,1.0);
	glClearColor(0.0,0.0,0.1,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1.0, 0.5, 1);

	drawstring(263, 415, "KEYBOARD AND MOUSE FUNCTIONS");
	drawstring(263, 410, "____________");
	glColor3f(1.5, 1.0, 1.0);
/*	drawstring(50, 375, "INSTRUCTIONS:");
	drawstring(50, 370, "____");*/
	glColor3f(1, 0.5, 0.5);
	drawstring(60, 348, "Keyboard Functions");
	drawstring(60, 342, " ------------- ");
	glColor3f( 1.0,1.0,0.0);
	drawstring(60, 325, "*Press 'S' to start");
	drawstring(60, 307, "*Press 'Right Mouse Button' in 'My Window' to start the implementation");
	//drawstring(60, 289, "*Press 'h' for help window");
	drawstring(60, 289, "*Press '?' for About Page");
	drawstring(60, 271, "*Press 'q' for quit");
	drawstring(60, 181, "*press any key to close the terminal");
	glColor3f(1, 0.5,0.5);
	drawstring(60, 158, "Mouse Function");
	drawstring(60, 152, "------------ ");
	glColor3f( 0.5,1,1);
	drawstring(60, 135, "*Left click on mouse to go to the previous window");
	//drawstring(60, 110, "*Right click on mouse to go to About us window");
	glutMouseFunc(MOUSE2);

	//glutKeyboardFunc(keyboard1);
	glutKeyboardFunc(keyboard);
	glFlush();
}
void MOUSE3(int btn, int state, int x, int y)
{
	if(btn==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN);
	Aboutintro();
}
void Aboutintro (void)
{
	glClearColor(0.1,0.0,0.0,1.0);
	glClearColor(0.0,0.1,0.0,1.0);
	glClearColor(0.0,0.0,0.1,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(2.0, 1.0, 0.0);
	drawstring(263, 415, "ABOUT PROJECT");
	drawstring(263, 400, "-------------");
	glColor3f(2.5, 1.0, 0.0);
	drawstring(50, 375, "INTRODUCTION:");
	drawstring(50, 370, "-------------");
	glColor3f(1.0, 1.0, 1.0);
	drawstring(60, 350, "Objective of the project is to implement bellman ford algorithm. In this project the user is asked to enter the number of vertices of the ");
	drawstring(60, 330, "respective graph.Also, the user have to enter the edge matrix of the given graph.The output is displayed in the window.The Bellmanford");
	drawstring(60, 310, "algorithm is a graph search algorithm that finds the shortest path between a given source vertex and all other vertices in the graph.This");
	drawstring(60, 290, "algorithm can be used on both weighted and unweighted graphs.In this project we mainly concentrate on creation of nodes and finding the");
	drawstring(60, 270, "shortest distance between them with the lines.");
	glColor3f(2.5, 1.0, 0.0);
	drawstring(50, 245, "ALGORITHM:");
	glColor3f(1.0, 1.0, 1.0);
	drawstring(60, 225, "1)Start with the weighted graph");
	drawstring(60, 200, "2)Choose a starting vertex and assign infinity path values to all other vertices");
	drawstring(60, 180, "3)Visit each edge and relax the path distances if they are inaccurate");
	drawstring(60, 160, "4)We need to do this V times because in the worst case, a vertex's path length might need to be readjusted V times");
	drawstring(60, 140, "5)Notice how the vertex at the top right corner had its path length adjusted");
	drawstring(60,120,"6)After all the vertices have their path lengths,we check if a negative cycle is present");
	glutMouseFunc(MOUSE2);
	//glutKeyboardFunc(keyboard1);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(aboutbtn);
	glFlush();
}
void Aboutmethod (void)
{
	glClearColor(0.1,0.0,0.0,1.0);
	glClearColor(0.0,0.1,0.0,1.0);
	glClearColor(0.0,0.0,0.1,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(2.0, 1.0, 0.0);
	drawstring(263, 415, "ABOUT PROJECT");
	drawstring(263, 400, "-------------");
	glColor3f(2.5, 1.0, 0.0);
	drawstring(50, 375, "METHODOLOGY:");
	drawstring(50, 370, "-------------");
	glColor3f(1.0, 1.0, 1.0);
	drawstring(60, 350, "For n vertices, we relax the edges for n-1 times where n is the number of edges.");
	drawstring(60, 330, "First, we draw the nodes and connecting lines by passing co-ordinate values to a GL_LINES.");
	drawstring(60, 310, "It will draw the network and connections of the network. The shortest path is calculated by using Bellman-Ford algorithm using the");
	drawstring(60, 290, "following formula-1.");
	drawstring(60, 270, "1.Initialization:");
	drawstring(60, 250, "Di=999; for all i not equal to d");
	drawstring(60, 230, "Dd=0");
	drawstring(60, 210, "2.Updation");
	drawstring(60, 190, "Di=minj{Cij+Dj}");
	drawstring(60, 170, "Repeat step 2 until no more change occur in iteration");
	glutMouseFunc(MOUSE2);
	//glutKeyboardFunc(keyboard1);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(aboutbtn);
	glFlush();
}


//DRAW A BITMAP NUMBER i at (x,y)
void raster(int x,int y,int i)
{
    char z=i+'0';
    glRasterPos2f(x-5,y-5);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,z);
}


//DRAW THE NODES (SQUARES) 
void drawSquare(int x, int y)
{

    if(i<=n)
    {
            y = 500-y;                              //Convert from screen coordinates
            glPointSize(70);
            
            if(i==src)
                      glColor3f(0.1f, 0.0f, 0.0f);
            else
                      glColor3f(1.0f, 1.5f, 0.0f);
            
            glBegin(GL_POINTS);
            glVertex2f(x , y);
            glEnd();
            
            a[i]=x;
            b[i]=y;
            
            glColor3f(1.0f, 0.0f, 0.0f);
            s1=itoa(i,s,10);
            drawstring(x-5,y-5,s1);
            
            glFlush();
   }
   i=i+1;
}

//READ DATA: |V|,COST MATRIX, SOURCE VERTEX
void read()
{
    printf("Enter the number of vertices\n");
    scanf("%d",&n);
    printf("Enter the cost matrix\n");
    for(int j=1;j<=n;j++)
            for(int k=1;k<=n;k++)
            {
                    scanf("%d",&cost[j][k]);
                    if(cost[j][k]==0 || cost[j][k]==999)
				    cost[j][k]=999;
                    else
                    {
                        edges[EDGES].u=j;
                        edges[EDGES].v=k;
                        edges[EDGES].w=cost[j][k];
                        EDGES++;
                    }
            }
     printf("\nGO TO MY WINDOW, PLACE THE NODES IN INPUT AREA AND THEN CLICK RIGHT BUTTON FOR NEXT OPTION\n");	
     initial(); //Draw the initial screen
}
//DRAW THE EDGES
void drawline()
{
  int j,k,x1,x2,y1,y2;
  for(j=1;j<=n;j++)
  {
   for(k=1;k<=n;k++)
   {
    if(cost[j][k]!=999 && j<k)
    {
     x1=a[j];
     y1=b[j];
     x2=a[k];
     y2=b[k];
    

     glColor3f(0.0,0.5,0.0);
    
     glLineWidth(3);
     glBegin(GL_LINES);
                      glVertex2i(x1-7,y1+10);
                      glVertex2i(x2-7,y2+10);
     glEnd();
    
     s1=itoa(cost[j][k],s,10);
     drawstring((x1+x2-16)/2,(y1+y2+22)/2,s1);
     glFlush();
    }
    
    if(cost[j][k]!=cost[k][j] && cost[j][k]!=999 && j>k)
    {
     x1=a[j];
     y1=b[j];
     x2=a[k];
     y2=b[k];
     
     glColor3f(1.0,0.5,0.0);
     glBegin(GL_LINES);
                       glVertex2i(x1+10,y1+18);
                       glVertex2i(x2+10,y2+18);
     glEnd();

     s1=itoa(cost[j][k],s,10);
     drawstring((x1+x2+20)/2,(y1+y2+36)/2,s1);
     glFlush();	
    }
   }
  }
}
void shortestpath(int src)
{
 //START OF BELLMAN FORD
    int j,p,q,x1,y1,x2,y2,x,y;
    int d[MAX],parent[MAX];
    int it,flag=0,child[MAX];
   
   //INITIALIZE DATA OBJECTS
   for (it = 1; it <= n; ++it) 
   {
       d[it] = INFINITY;
       parent[it]=src;
       
   }
   d[src] = 0;

   //RELAXATION METHOD
   for(int m=0;m<n;m++)//REPEAT N TIMES
   {
           //RELAX ALL EDGES
    for (it = 1; it <=n; ++it) {
         for (j = 1; j <=n; ++j) {
               if(d[it]+cost[it][j]<d[j])
               {
                d[j]=d[it]+cost[it][j];
                parent[j]=it;
               }
               }
           }
   }

   //CHECK FOR NEGATIVE LOOPS
for (it = 1; it <=n; ++it) {
       for (j = 1; j <=n; ++j) {
           if(cost[it][j]==INFINITY) 
	   continue;
           if(d[it]+cost[it][j]<d[j])
           {
            printf("\n\nGraph contains a negative-weight cycle\n");                   
       return;
           }
       }
   }
    printf("From source %d\n",src);
    for(i=1;i<=n;i++)
    if(i!=src)
    printf("The shortest distance to %d is %d\n",i,d[i]);
    printf("\n");
   //INITIALIZE SPANNING TREE EDGES
   int l=0;
   for (int it = 1; it <= n; ++it) {
   if(parent[it]==it) continue;    
tree[l][1]=parent[it];
tree[l++][2]=it;
   }

   //DRAW THE SPANNING TREE
   for(int r=1;r<=n;r++)
   {
     
             x=a[r];
             y=b[r];

             glPointSize(25);
             if(r==src)
                       glColor3f(0.7f, 0.4f, 0.0f);
             else
                       glColor3f(0.5f, 0.5f, 0.8f);

             glBegin(GL_POINTS);
                                glVertex2f(x,y+250);
             glEnd();
             
             glColor3f(0.0,1.0,0.0);
             
             s1=itoa(r,s,10);
             drawstring(x,y+250,s1);
             
             glFlush();

             }
            
             for(int x=0;x<l;x++)
             {
                     p=tree[x][1];
                     q=tree[x][2];
                     if(p==0||q==0) continue;
                    
                     x1=a[p];
                     y1=b[p];
                     x2=a[q];
                     y2=b[q];
                     
                     if(p<q)
                     {
                            glColor3f(0.0,0.5,0.0);
                            glBegin(GL_LINES);
                                              glVertex2i(x1,y1+250);
                                              glVertex2i(x2,y2+250);
                            glEnd();

                            s1=itoa(cost[p][q],s,10);
                            drawstring((x1+x2)/2,(y1+y2+500)/2,s1);
                     }

                     else
                     {
                            glColor3f(1.0,0.5,0.0);
                            glBegin(GL_LINES);
                                              glVertex2i(x1,y1+250);
                                              glVertex2i(x2,y2+250);
                            glEnd();

                            s1=itoa(cost[p][q],s,10);
                            drawstring((x1+x2)/2,(y1+y2+500)/2,s1);
                     }
                     }
             glFlush();
     
}

void mouse(int bin, int state , int x , int y) 
{
    if(bin==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
     drawSquare(x,y);

}

void top_menu(int option)
{
int x,y;
    switch(option)
    {
                  case 1:
                       read();
                       glutPostRedisplay();
                       break;
                  case 2:
                       drawline();
                       glutPostRedisplay();
                       break;
                  case 3:
                       for(int i=1; i<=n; i++)
{	
glClear(GL_COLOR_BUFFER_BIT);
initial();
for(int r=1;r<=n;r++)
{
x=a[r];
y=b[r];
glPointSize(40);
if(r==src)
glColor3f(0.7f, 0.4f, 0.0f);
else
glColor3f(0.5f, 0.5f, 0.8f);
glBegin(GL_POINTS);
glVertex2f(x,y);
glEnd();
glColor3f(0.0,1.0,0.0);
s1=itoa(r,s,10);
drawstring(x-5,y-5,s1);
setFont(GLUT_BITMAP_HELVETICA_18);
glColor3f(0.0,0.0,0.0);
drawstring(130,470,"For source");
glFlush();
}	
drawline();
s1=itoa(i,s,10);
setFont(GLUT_BITMAP_HELVETICA_18);
glColor3f(0.0,0.0,0.0);
drawstring(225,470,s1);
glutPostRedisplay();
shortestpath(i);
delay();
}
break;
                  case 4:
                       exit(0);
    }
}



void init (void)
{
    glClearColor (1.0, 0.9, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport( 0,0, 500, 500 );
    glMatrixMode( GL_PROJECTION );
     glOrtho( 0.0, 500.0, 0.0, 500.0, 1.0, -1.0 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glFlush();
}
void myInit1()
{
  glClearColor(1.2,1.1,7.3,5.0);
  glColor3f(1.0f,0.0f,0.0f);
  glColor3f(1.0f,0.0f,1.0f);
  glPointSize(5.0);
   /*glutCreateMenu(top_menu);
   glutAddMenuEntry("Read Cost Matrix",1);
   glutAddMenuEntry("Display Weighted Graph",2);
   glutAddMenuEntry("Display Shortest Path",3);
   glutAddMenuEntry("Exit",4);
   glutAttachMenu(GLUT_RIGHT_BUTTON);*/
  gluOrtho2D(0.0,640.0,0.0,480);
  //gluOrtho2D(0.0,1000.0,0.0,900);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glRasterPos2i(-20,20);
 // pix[0].draw();
  setFont(GLUT_BITMAP_TIMES_ROMAN_24);
}


void display1(void)
{  
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0,1.0,2.0);
  Aboutintro();
  displayx();
   title();
  

}

/*void displayM(void)
{  
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0,1.0,2.0);
  //initial();
  display();

}*/

//initializing pixel array




int main (int argc,char** argv)
{
   glutInit(&argc,argv);
   
  
 /*  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowPosition(0,0);
   glutInitWindowSize(1800,1000);
   glutCreateWindow("Help Sheet");
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(displayx);
   myInit1();*/
   
 glutInitDisplayMode( GLUT_SINGLE|GLUT_RGB );
   glutInitWindowSize(3000,3000);
   //glutInitWindowSize(1800,1000);
   glutInitWindowPosition(0,0);
   glutCreateWindow("My Window");
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
  glutCreateMenu(top_menu);
   glutAddMenuEntry("Read Cost Matrix",1);
   glutAddMenuEntry("Display Weighted Graph",2);
   glutAddMenuEntry("Display Shortest Path",3);
   glutAddMenuEntry("Exit",4);
   glutAttachMenu(GLUT_RIGHT_BUTTON);
//glutDisplayFunc(displayM);
    init();
   
   printf("\nGO TO MY WINDOW AND CLICK RIGHT BUTTON FOR NEXT OPTION\n");

    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
   glutInitWindowPosition(0,0);
   //glutInitWindowSize(width,height);
   glutInitWindowSize(1800,1200);
  // pix[0].readBMPFile("bellman.bmp");
   glutCreateWindow("Welcome Page");
   glutKeyboardFunc(keyboard);
  
   glutDisplayFunc(display1);
   myInit1();


   glutMainLoop();
}
/*
#include<glut.h>

void wall(double thickness)
{

//draw thin wall with top=x-zplane,corner at origin 

glPushMatrix();
glTranslated(0.5,0.5*thickness,0.5);
glScaled(1.0,thickness,1.0);
glutSolidCube(1.0);
glPopMatrix();
}

// draw one table leg

void tableLeg(double thick,double len)
{
glPushMatrix();
glTranslated(0,len/2,0);
glScaled(thick,len,thick);
glutSolidCube(1.0);
glPopMatrix();
}

void table(double topWid,double topThick,double legThick,double legLen)
{

// draw the table-a top & four legs
// draw the top first

glPushMatrix();
glTranslated(0,legLen,0);
glScaled(topWid,topThick,topWid);
glutSolidCube(1.0);
glPopMatrix();
double dist=0.95*topWid/2.0-legThick/2.0;
glPushMatrix();
glTranslated(dist,0,dist);
tableLeg(legThick,legLen);
glTranslated(0.0,0.0,-2*dist);
tableLeg(legThick,legLen);
glTranslated(-2*dist,0,2*dist);
tableLeg(legThick,legLen);
glTranslated(0,0,-2*dist);
tableLeg(legThick,legLen);
glPopMatrix();
}

void displaySolid(void)
{

//set properties of the surface material

GLfloat mat_ambient[]={0.7f,0.7f,0.7f,1.0f}; //gray
GLfloat mat_diffuse[]={.5f,.5f,.5f,1.0f};
GLfloat mat_specular[]={1.0f,1.0f,1.0f,1.0f};
GLfloat mat_shininess[]={25.0f};

glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

//set the light source

GLfloat lightIntensity[]={0.7f,0.7f,0.7f,1.0f};
GLfloat light_position[]={2.0f,6.0f,3.0f,0.0f};
glLightfv(GL_LIGHT0,GL_POSITION,light_position);
glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);

//set the camera

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
double winHt=1.0;       //half-height of window
glOrtho(-winHt*64/48.0,winHt*63/48.0,-winHt,winHt,-0.1,10.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(2.3,1.3,2.0,0.0,0.25,0.0,0.0,1.0,0.0);

//start drawing

glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glPushMatrix();
glTranslated(0.5,0.40,0.5);
glRotated(30,0,1,0);
glutSolidTeapot(0.09);
glPopMatrix();
glPushMatrix();
glTranslated(0.4,0,0.4);
table(0.6,0.02,0.02,0.3);
glPopMatrix();
wall(0.02);   //bottom
glPushMatrix();
glRotated(90.0,0.0,0.0,1.0);
wall(0.02);   //left
glPopMatrix();
glPushMatrix();
glRotated(-90.0,1.0,0.0,0.0);
wall(0.02);  //right
glPopMatrix();
glFlush();
}

int main(int argc,char **argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
glutInitWindowSize(640,480);
glutCreateWindow("simple shaded scene consisting of a tea pot on a table");
glutDisplayFunc(displaySolid);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glShadeModel(GL_SMOOTH);
glEnable(GL_DEPTH_TEST);
glEnable(GL_NORMALIZE);
glClearColor(0.0,0.0,0.0,1.0);
glViewport(0,0,640,480);
glutMainLoop();
return 0;
}
 


















































































*/