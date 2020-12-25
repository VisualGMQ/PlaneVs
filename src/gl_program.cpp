#include "gl_program.hpp"

GLProgram::GLProgram() {
    createProgram();
}

GLProgram::GLProgram(GLShader& vertex_shader, GLShader& frag_shader) {
    createProgram();
    ApplyShaders(vertex_shader, frag_shader);
}

void GLProgram::createProgram() {
    _program = glCreateProgram();
    Assertm("program create failed", _program != 0);
}

void GLProgram::ApplyShaders(GLShader& vertex_shader, GLShader& frag_shader) {
    attachShaders(vertex_shader, frag_shader);
    linkShaders();
}

void GLProgram::attachShaders(GLShader& shader1, GLShader& shader2) {
    glAttachShader(_program, shader1.GetId());
    glAttachShader(_program, shader2.GetId());
}

void GLProgram::linkShaders() {
    glLinkProgram(_program);

    GLint success;
    glGetProgramiv(_program, GL_LINK_STATUS, &success);
    if (!success) {
        char buf[1024] = {0};
        glGetProgramInfoLog(_program, sizeof(buf), nullptr, buf);
        Log("program link failed:\n" + string(buf));
    }
}

void GLProgram::Use() {
    glUseProgram(_program);
}

void GLProgram::Destroy() {
    glDeleteProgram(_program);
}

void GLProgram::UniformMat4(string name, mat4 m) {
    GLint loc = getLocation(name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(m));
}

void GLProgram::UniformInt1(string name, int value) {
    GLint loc = getLocation(name);
    glUniform1d(loc, value);
}

void GLProgram::Uniformfloat1(string name, float value) {
    GLint loc = getLocation(name);
    glUniform1f(loc, value);
}

GLint GLProgram::getLocation(string name) {
    GLuint loc = glGetUniformLocation(_program, name.c_str());
    if (loc == -1)
        Log(name + " location can't find");
    return loc;
}

GLProgram::~GLProgram() {
    Destroy();
}
