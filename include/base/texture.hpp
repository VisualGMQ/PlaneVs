#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <string>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "base/log.hpp"
#include "base/config.hpp"
#include "base/drawable.hpp"
#include "base/geomentry.hpp"
#include "base/validable.hpp"
#include "base/geomentry.hpp"
#include "base/gl_program.hpp"
#include "base/gl_gfxbuf.hpp"
using std::string;
using glm::vec2;
using glm::vec3;
using glm::mat4;

class ITexture: public TextureDrawable {
 public:
    virtual isize GetSize() const = 0;
};

class Texture final : public Validable, public ITexture {
 public:
     static Texture* Create(const string filename);
     static void Destroy() {
         for (Texture* t : _instances)
             delete t; 
         Log("Textures deleted");
     }

     Texture() = delete;
     Texture(const string filename);
     Texture(const Texture&) = delete;
     Texture& operator=(const Texture&) = delete;
     isize GetSize() const override;
     void Load(string filename);
     void Draw(irect* src_rect, irect* dst_rect, color* tex_color, color* key_color) const override;
     void Draw(irect* src_rect, irect*, float degree, FlipEnum flip, color* tex_color, color* key_color) const override;
     ~Texture();

 private:
     static vector<Texture*> _instances;

     void createTexture();
     void bufferTextureData(SDL_Surface* surface);
     mat4 calcPositionInfo(float x, float y) const;
     mat4 calcRotateScaleInfo(irect clip_area, isize dst_size, float angle_degree, FlipEnum flip) const;
     isize _size;

     GLuint _texture = 0;
};

#endif

