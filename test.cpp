#include <GLFW/glfw3.h>
#include<glew.h>
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);



        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


// #include <GLFW/glfw3.h>
// int main(void){
// 	GLFWwindow* window;
// 	if(!glfwInit()){
// 		return -1;
// 	}
// 	window = glfwCreateWindow(640, 480, "Hello Love", NULL, NULL);

// 	if(!window){
// 		glfwTerminate();
// 		return -1;
// 	}

// 	glfwMakeContextCurrent(window);
// 	while(!glfwWindowShouldClose(window)){
// 		glClear(GL_COLOR_BUFFER_BIT);



// 		glfwSwapBuffers(window);
// 		glfwPollEvents();
// 	}

// 	glfwTerminate();
// 	return 0;


// }