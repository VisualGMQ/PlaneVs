#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <string>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "base/log.hpp"
#include "base/geomentry.hpp"
#include "base/validable.hpp"
#include "base/geomentry.hpp"
#include "engin/gl_program.hpp"
#include "engin/gl_gfxbuf.hpp"
using std::string;
using glm::vec2;
using glm::vec3;
using glm::mat4;

struct ShapeInfo {
    irect src_rect;
    irect dst_rect;
    float degree = 0;
};

struct ColorInfo {
    color tex_color = {1, 1, 1, 1};
    color key_color = {0, 0, 0, 1};
};

class Texture final : public Validable{
 public:
     Texture();
     Texture(const string filename);
     Texture(const Texture&) = delete;
     Texture& operator=(const Texture&) = delete;
     isize GetSize() const;
     void Load(string filename);
     void Draw(irect src_rect, irect dst_rect);
     void Draw(ShapeInfo shape_info, ColorInfo color_info);

 private:
     void createTexture();
     void bufferTextureData(SDL_Surface* surface);
     mat4 calcPositionInfo(float x, float y);
     mat4 calcRotateScaleInfo(irect clip_area, isize dst_size, float angle_degree);

     GLuint _texture = 0;
     isize _size = {0, 0};
};

#endif

