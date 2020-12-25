#include "gl_shader.hpp"

GLShader::GLShader(GLenum type, string filename) {
    _type = type;
    string content = loadShaderContent(filename);
    createShader(type);
    fillShaderContent(content);
    compileShader();
}

string GLShader::loadShaderContent(string filename) {
    ifstream file(filename);
    Assertm("shader " + filename + " open failed", !file.fail());
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

void GLShader::createShader(GLenum shader_type) {
    _shader = glCreateShader(shader_type);
    Assertm("Shader create failed", _shader != 0);
}

void GLShader::fillShaderContent(string content) {
    GLint len = content.size();
    const char* c_content = content.c_str();
    glShaderSource(_shader, 1, &c_content, &len);
}

GLuint GLShader::GetId() const {
    return _shader;
}

GLenum GLShader::GetType() const {
    return _type;
}

void GLShader::compileShader() {
    glCompileShader(_shader);

    GLint success;
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char buf[1024] = {0};
        glGetShaderInfoLog(_shader, sizeof(buf), nullptr, buf);
        Log("shader compile failed:\n" + string(buf));
    }
}

void GLShader::Destroy() {
    glDeleteShader(_shader);
}

GLShader::~GLShader() {
    Destroy();
}
