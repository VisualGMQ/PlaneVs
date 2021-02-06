#include "base/gl_program.hpp"

GLProgram::GLProgram(IdType id):HasID(id) {
    createProgram();
}

GLProgram::GLProgram(IdType id, GLShader& vertex_shader, GLShader& frag_shader):HasID(id) {
    createProgram();
    ApplyShaders(vertex_shader, frag_shader);
}

void GLProgram::createProgram() {
    _program = glCreateProgram();
    Assertm(_program != 0, "GLProgram::createProgram", "program create failed");
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
        Logw("GLProgram::linkShaders", "program link failed:\n%s", buf);
        invalid();
    } else {
        valid();
    }
}

void GLProgram::Use() {
    glUseProgram(_program);
}

void GLProgram::Delete() {
    glDeleteProgram(_program);
    invalid();
}

void GLProgram::UniformMat4(const string name, mat4 m) {
    glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, value_ptr(m));
}

void GLProgram::UniformInt1(const string name, int value) {
    glUniform1d(getLocation(name), value);
}

void GLProgram::UniformFloat1(const string name, float value) {
    glUniform1f(getLocation(name), value);
}

void GLProgram::UniformFloat3(const string name, float v1, float v2, float v3) {
    glUniform3f(getLocation(name), v1, v2, v3);
}

void GLProgram::UniformFloat4(const string name, float v1, float v2, float v3, float v4) {
    glUniform4f(getLocation(name), v1, v2, v3, v4);
}

void GLProgram::UniformVec4(const string name, vec4 value) {
    glUniform1fv(getLocation(name), 1, value_ptr(value));
}

GLint GLProgram::getLocation(const string& name) {
    GLuint loc = glGetUniformLocation(_program, name.c_str());
    if (loc == -1)
        Logw("GLProgram::getLocation", "%s location can't find", name.c_str());
    return loc;
}

GLProgram::~GLProgram() {
    Delete();
}
