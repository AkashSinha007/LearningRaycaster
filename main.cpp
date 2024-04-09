

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

#include<cmath>
#define PI 3.1415926535


int  mapX = 8, mapY = 8, mapS = 64;

int map[]=           //the map array.
{
 1,1,1,1,1,1,1,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,1,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1,	
};


float px, py, pdx,pdy,pa; //player position

void init()
{
    glClearColor(0.3,0.3,0.3,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1024, 512,0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    px = 300; 
    py = 300;
    pdx=cos(pa)*5;
    pdy=sin(pa)*5;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        pa-= 0.1;
        if(pa <0)
        {
            pa+= 2*PI;
        }
        pdx = cos(pa)*5;
        pdy = sin(pa)*5;
    }

    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        pa+= 0.1;
        if(pa > 2*PI)
        {
            pa-= 2*PI;
        }
        pdx = cos(pa)*5;
        pdy = sin(pa)*5;
    }

    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        px += pdx;
        py += pdy;
    }

    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        px -= pdx;
        py -= pdy;
    }
    
    //glfwSetWindowShouldClose(window, GLFW_TRUE);
    // Add more key handling here if needed
}

void drawPlayer()
{
    glColor3f(1,1,0);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2i(px,py);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px,py);
    glVertex2i(px+pdx*5, py+pdy*5);
    glEnd();
}


void drawMap2D()
{
 int x,y,xo,yo;
 for(y=0;y<mapY;y++)
 {
  for(x=0;x<mapX;x++)
  {
   if(map[y*mapX+x]==1){ glColor3f(1,1,1);} else{ glColor3f(0,0,0);}
   xo=x*mapS; yo=y*mapS;
   glBegin(GL_QUADS); 
   glVertex2i( 0   +xo+1, 0   +yo+1); 
   glVertex2i( 0   +xo+1, mapS+yo-1); 
   glVertex2i( mapS+xo-1, mapS+yo-1);  
   glVertex2i( mapS+xo-1, 0   +yo+1); 
   glEnd();
  } 
 } 
}

void display(GLFWwindow* window)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /*draw Map with Boundry Walls*/
    drawMap2D();

    /*draw Player*/
    drawPlayer();
    

    /* Swap front and back buffers */
    glfwSwapBuffers(window);
}



int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Raycaster Demo", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Set the key callback */
    glfwSetKeyCallback(window, keyCallback);

    /*Initialize player coordinates*/
    init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        /* Render here */
        display(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}