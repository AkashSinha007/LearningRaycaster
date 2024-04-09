

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>


float px, py; //player position

void init()
{
    glClearColor(0.3,0.3,0.3,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1024, 512,0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    px = 300; 
    py = 300;
    // glBegin(GL_TRIANGLES);
    // glVertex2f(-0.5f,-0.5f);
    // glVertex2f(0.0f,0.5f);
    // glVertex2f(0.5f,-0.5f);
    // glEnd();

}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        px -= 5;
    }

    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        px += 5;
    }

    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        py -= 5;
    }

    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        py += 5;
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
}


void display(GLFWwindow* window)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Swap front and back buffers */
    drawPlayer();
    
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