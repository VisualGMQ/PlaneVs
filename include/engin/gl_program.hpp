#ifndef GL_PROGRAM_HPP
#define GL_PROGRAM_HPP
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "base/log.hpp"
#include "base/id_generator.hpp"
#include "base/validable.hpp"
#include "engin/gl_shader.hpp"
#include "base/manager.hpp"
using glm::mat4;
using glm::value_ptr;
using glm::vec4;
using std::string;

class GLProgram;

using GLProgramManager = IdInstanceManager<GLProgram>;

class GLProgram final: public Validable, public HasID {
 public:
     friend GLProgramManager;
     void ApplyShaders(GLShader& vertex_shader, GLShader& frag_shader);
     void Use();
     void Delete();
     void UniformMat4(const string, mat4);
     void UniformInt1(const string, int);
     void UniformFloat1(const string, float);
     void UniformFloat3(const string, float, float, float);
     void UniformFloat4(const string, float, float, float, float);
     void UniformVec4(const string, vec4);
     ~GLProgram();
 private:
     GLuint _program = 0;

     GLProgram(IdType id);
     GLProgram(IdType id, GLShader& vertex_shader, GLShader& frag_shader);
     void createProgram();
     void attachShaders(GLShader&, GLShader&);
     void linkShaders();
     GLint getLocation(const string& name);
};


inline void CreatePresetPrograms() {
    GLProgram* tex_program = GLProgramManager::CreatePreset(TEXTURE_PROGRAM_ID);
    GLShader tex_vertex_shader(GL_VERTEX_SHADER, "./shader/tex_shader.vert"),
             tex_frag_shader(GL_FRAGMENT_SHADER, "./shader/tex_shader.frag");
    tex_program->ApplyShaders(tex_vertex_shader, tex_frag_shader);

    GLProgram* geo_program = GLProgramManager::CreatePreset(GEOM_PROGRAM_ID);
    GLShader geo_vertex_shader(GL_VERTEX_SHADER, "./shader/geo_shader.vert"),
             geo_frag_shader(GL_FRAGMENT_SHADER, "./shader/geo_shader.frag");
    geo_program->ApplyShaders(geo_vertex_shader, geo_frag_shader);
}

#endif

