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
#include "base/geomentry.hpp"
#include "base/validable.hpp"
#include "base/gl_program.hpp"
#include "base/gl_gfxbuf.hpp"
#include "base/itexture.hpp"
#include "base/destroyable.hpp"

using std::string;
using glm::vec2;
using glm::vec3;
using glm::mat4;

class Texture final: public Validable, public ITexture, public Destroyable {
 public:
     static Texture* Create(SDL_Surface* surface);
     /*
      * @brief create independent texture, the texture must delete by your self(use `delete texture;`)
      */
     static Texture* CreateIndependent(SDL_Surface* surface);
     static void DestroyAll() {
         for (Texture* t : _instances)
             delete t; 
         Logi("static Texture::DestroyAll", "Textures deleted");
     }

     Texture() = delete;
     Texture(const Texture&) = delete;
     Texture& operator=(const Texture&) = delete;
     isize GetSize() const override;
     void Load(SDL_Surface* surface);
     void Draw(irect* src_rect, irect* dst_rect, icolor* tex_color, icolor* key_color) const override;
     void Draw(irect* src_rect, irect*, float degree, FlipEnum flip, icolor* tex_color, icolor* key_color) const override;
     void Destroy() override;
     ~Texture();

 private:
     static vector<Texture*> _instances;

     explicit Texture(SDL_Surface* surface);
     void createTexture();
     void bufferTextureData(SDL_Surface* surface);
     mat4 calcPositionInfo(float x, float y) const;
     mat4 calcRotateScaleInfo(irect clip_area, isize dst_size, float angle_degree, FlipEnum flip) const;
     isize _size;

     GLuint _texture = 0;
};

#endif

