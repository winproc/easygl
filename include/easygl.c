#include <stdio.h>
#include "easygl.h"

GLuint instance() {
    GLuint array;
    glGenVertexArrays(1, &array);

    return array;
}

void use_instance(GLuint vao) {
    glBindVertexArray(vao);
}

GLuint add_data(GLfloat* buffer, size_t arraysize, int strict) {
    GLuint buffer_id;
    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glBufferData(GL_ARRAY_BUFFER, arraysize * sizeof(GLfloat), buffer, strict ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, 0);
    glEnableVertexAttribArray(0);

    return buffer_id;
}

void reset_data(GLuint bufid, GLfloat* buffer, size_t arraysize) {
    glBindBuffer(GL_ARRAY_BUFFER, bufid);
    glBufferSubData(GL_ARRAY_BUFFER, 0, arraysize * sizeof(GLfloat), buffer);
}

size_t read_shader(const char* filename, char* buffer) {
    FILE* file;
    file = fopen(filename, "r");
    if (!file) {
        puts("Unable to open shader file");
        return 0;
    }

    size_t read_bytes = fread(buffer, sizeof(char), 2048, file);
    fclose(file);

    buffer[read_bytes] = '\0';
    return read_bytes;
}

int safe_compile(GLuint shaderid) {
    glCompileShader(shaderid);

    GLint compile_stat;
    glGetShaderiv(shaderid, GL_COMPILE_STATUS, &compile_stat);
    if (compile_stat == GL_FALSE) {
        GLchar* error;
        glGetShaderInfoLog(shaderid, 512, NULL, error);
        printf("Compilation error:\n%s", error);
        return 0x0;
    }
    return 1;
}

GLuint program_f(const char* filename_vert, const char* filename_frag) {
    GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);


    char vertex_shader[2048], fragment_shader[2048];

    size_t read_b_v, read_b_f;
    read_b_v = read_shader(filename_vert, vertex_shader);
    read_b_f = read_shader(filename_frag, fragment_shader);

    if (!read_b_v || !read_b_f) {
        puts("Failed to read shaders during program creation");
        return 0x0;
    }

    const char* vptr = vertex_shader;
    const char* fptr = fragment_shader;

    glShaderSource(vshader, 1, &vptr, NULL);
    glShaderSource(fshader, 1, &fptr, NULL);

    safe_compile(vshader);
    safe_compile(fshader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vshader);
    glAttachShader(program, fshader);

    glLinkProgram(program);

    return program;
}

void use_program(GLuint program_id) {
    glUseProgram(program_id);
}

int loop_window(GLFWwindow *window) {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 0;
}