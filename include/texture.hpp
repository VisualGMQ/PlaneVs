#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <string>
#include "GL/glew.h"
#include "SDL.h"
#include "SDL_image.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "header.hpp"
#include "gl_program.hpp"
using std::string;
using glm::vec2;
using glm::vec3;
using glm::mat4;

class Texture final{
 public:
     Texture();
     Texture(string filename);
     Texture(const Texture&) = delete;
     Texture& operator=(const Texture&) = delete;
     Size GetSize() const;
     void Load(string filename);
     void Draw(GLProgram& program, float x, float y, float scalex = 1, float scaley = 1, float degree = 0);
     void Draw(GLProgram& program, float x, float y, Size size, float degree = 0);
     bool Valid() const;
 private:
     void createTexture();
     void bufferTextureData(SDL_Surface* surface);
     mat4 calcPositionInfo(float x, float y);
     mat4 calcTransformInfo(float scalex, float scaley, float angle_degree);

     GLuint _texture = 0;
     Size _size = {0, 0};
     bool _valid = false;
};

#endif

