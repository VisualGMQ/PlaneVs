#ifndef GFX_BUF_HPP
#define GFX_BUF_HPP
#include <vector>

#include <GL/glew.h>

#include "base/log.hpp"
#include "base/manager.hpp"

class GLGfxBuf;

using GLGfxBufManager = IdInstanceManager<GLGfxBuf>;

class GLGfxBuf final: public HasID {
 public:
     friend GLGfxBufManager;
     GLuint vao;
     GLuint vbo;
     GLuint ebo;
     GLGfxBuf(GLGfxBuf&) = delete;
     GLGfxBuf operator=(const GLGfxBuf&) = delete;
     ~GLGfxBuf() {
         glDeleteBuffers(1, &vbo);
         glDeleteBuffers(1, &ebo);
         glDeleteVertexArrays(1, &vao);
     }
 private:
     GLGfxBuf(IdType id):HasID(id) {
         glGenBuffers(1, &vbo);
         glGenBuffers(1, &ebo);
         glGenVertexArrays(1, &vao);
     }
};

inline void CreatePresetGfxBufs() {
    GLGfxBufManager::CreatePreset(SYSTEM_GFXBUF_ID);
}

#endif
