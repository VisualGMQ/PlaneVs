#ifndef GL_SHADER_HPP
#define GL_SHADER_HPP
#include <string>
#include <fstream>
#include <streambuf>
#include "GL/glew.h"
#include "header.hpp"
using std::string;
using std::ifstream;
using std::istreambuf_iterator;

class GLShader final{
 public:
     GLShader(GLenum type, string filename);
     GLuint GetId() const;
     GLenum GetType() const;
     void Destroy();
     ~GLShader();
 private:
     GLuint _shader = 0;
     GLenum _type;

     string loadShaderContent(string filename);
     void createShader(GLenum shader_type);
     void fillShaderContent(string content);
     void compileShader();
};

#endif

