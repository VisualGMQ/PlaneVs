#ifndef GFX_BUF_HPP
#define GFX_BUF_HPP
#include <vector>

#include <GL/glew.h>

#include "base/header.hpp"
using std::vector;

class GLGfxBufManager{
 public:
     class GLGfxBuf final {
      public:
         friend GLGfxBufManager;
         GLuint vao;
         GLuint vbo;
         GLuint ebo;
         IdType GetId() const { return _id; }
         GLGfxBuf(GLGfxBuf&) = delete;
         GLGfxBuf operator=(const GLGfxBuf&) = delete;
         ~GLGfxBuf() {
             glDeleteBuffers(1, &vbo);
             glDeleteBuffers(1, &ebo);
             glDeleteVertexArrays(1, &vao);
         }
      private:
         GLGfxBuf():_id(GenerateId()) {
             glGenBuffers(1, &vbo);
             glGenBuffers(1, &ebo);
             glGenVertexArrays(1, &vao);
         }
         IdType _id;
     };
     static GLGfxBuf* Create();
     static void FreeById(IdType id);
     static GLGfxBuf* GetById(IdType id);
     static void Destroy();

 private:
     static vector<GLGfxBuf*> _gfxbufs;
};

#endif

