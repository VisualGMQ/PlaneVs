#ifndef GL_PROGRAM_HPP
#define GL_PROGRAM_HPP
#include <string>
#include "gl_shader.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
using glm::mat4;
using glm::value_ptr;
using std::string;

class GLProgram {
 public:
     GLProgram();
     GLProgram(GLShader& vertex_shader, GLShader& frag_shader);
     void ApplyShaders(GLShader& vertex_shader, GLShader& frag_shader);
     void Use();
     void Destroy();
     void UniformMat4(string, mat4);
     void UniformInt1(string, int);
     void Uniformfloat1(string, float);
     ~GLProgram();
 private:
     GLuint _program = 0;

     void createProgram();
     void attachShaders(GLShader&, GLShader&);
     void linkShaders();
     GLint getLocation(string name);
};

#endif

