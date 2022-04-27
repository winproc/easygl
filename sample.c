#include "include/easygl.h"
#include <stdio.h>

/** Sample EasyGL program that renders a triangle **/

#define TRUE 1
#define FALSE 0

int main(void) {

    GLFWwindow* window;

    GLfloat trigdata[6] = {
        0.5, 0.0,
        0.0, 0.5,
        -0.5, 0.0,

    };

    if (!glfwInit()) {
        puts("Failed to initialize GLFW");
        return 0;
    }

    window = glfwCreateWindow(640, 380, "hello world", NULL, NULL);

    if (!window) {
        puts("Failed to create window with GLFW");
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        puts("Failed to initialize GLEW");
        return 0;
    }

    GLuint programid = program_f("main.vert", "main.frag");

    GLuint meshid = instance();
    use_instance(meshid);

    add_data(trigdata, 6, TRUE);

    use_instance(meshid);
    use_program(programid);

    return loop_window(window);
}