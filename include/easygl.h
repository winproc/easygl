#include "res/GL/glew.h"
#include "res/GLFW/glfw3.h"

typedef struct {
    unsigned short r;
    unsigned short g;
    unsigned short b;
} RGB;

typedef struct {
    GLfloat x;
    GLfloat y;
} Vector2;

void init_resources();
short init_window(GLFWwindow* window, int x, int y, const char* title);
int loop_window(GLFWwindow* window);

GLuint instance();
void use_instance(GLuint vao);

GLuint add_data(GLfloat* buffer, size_t arraysize, int strict);
void reset_data(GLuint bufid, GLfloat* buffer, size_t arraysize);

GLuint program_f(const char* filename_vert, const char* filename_frag);
GLuint program_s(const char* strbuf_vert, const char* strbuf_frag); // not implemented in EasyGL1
void use_program(GLuint program_id);



