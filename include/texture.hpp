#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <string>
#include "GL/glew.h"
#include "SDL.h"
#include "SDL_image.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "header.hpp"
#include "validable.hpp"
#include "gl_program.hpp"
using std::string;
using glm::vec2;
using glm::vec3;
using glm::mat4;

struct ShapeInfo {
    vec2 position;
    vec2 scale = vec2(1.0f, 1.0f);
    float degree = 0;
};

struct ColorInfo {
    Color color = {1, 1, 1, 1};
    Color key_color = {0, 0, 0, 1};
};

class Texture final : public Validable{
 public:
     Texture();
     Texture(const string filename);
     Texture(const Texture&) = delete;
     Texture& operator=(const Texture&) = delete;
     Size GetSize() const;
     void Load(string filename);
     void Draw(GLProgram& program, ShapeInfo shape_info, ColorInfo color_info);
 private:
     void createTexture();
     void bufferTextureData(SDL_Surface* surface);
     mat4 calcPositionInfo(float x, float y);
     mat4 calcRotateScaleInfo(float scale_x, float scale_y, float angle_degree);

     GLuint _texture = 0;
     Size _size = {0, 0};
};

#endif

