#ifndef GL_PROGRAM_HPP
#define GL_PROGRAM_HPP
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "base/validable.hpp"
#include "engin/gl_shader.hpp"
using glm::mat4;
using glm::value_ptr;
using glm::vec4;
using std::string;

class GLProgram : public Validable{
 public:
     GLProgram();
     GLProgram(GLShader& vertex_shader, GLShader& frag_shader);
     void ApplyShaders(GLShader& vertex_shader, GLShader& frag_shader);
     void Use();
     void Destroy();
     void UniformMat4(const string, mat4);
     void UniformInt1(const string, int);
     void UniformFloat1(const string, float);
     void UniformFloat3(const string, float, float, float);
     void UniformFloat4(const string, float, float, float, float);
     void UniformVec4(const string, vec4);
     ~GLProgram();
 private:
     GLuint _program = 0;

     void createProgram();
     void attachShaders(GLShader&, GLShader&);
     void linkShaders();
     GLint getLocation(const string& name);
};

class SystemProgram final {
 public:
     static void Init();
     static GLProgram* GetTextureProgram();
     static void Destroy();
 private:
     static GLProgram* _texture_program;
};

#endif

