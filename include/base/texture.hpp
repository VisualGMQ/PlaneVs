#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "base/log.hpp"
#include "base/config.hpp"
#include "base/geo_math.hpp"
#include "base/validable.hpp"
#include "base/itexture.hpp"
#include "base/destroyable.hpp"

using std::string;
using std::vector;
using glm::vec2;
using glm::vec3;
using glm::mat4;

class Texture final: public Validable, public ITexture, public Destroyable {
 public:
     static Texture* Create(SDL_Texture* texture);
     /*
      * @brief create independent texture, the texture must delete by your self(use `delete texture;`)
      */
     static Texture* CreateIndependent(SDL_Texture* texture);
     static void DestroyAll() {
         for (Texture* t : _instances)
             delete t; 
         _instances.clear();
     }

     Texture() = delete;
     Texture(const Texture&) = delete;
     Texture& operator=(const Texture&) = delete;
     isize GetSize() const override;
     void Load(SDL_Texture* texture);
     void Draw(SDL_Renderer*, irect* src_rect, irect* dst_rect, icolor* tex_color) const override;
     void Draw(SDL_Renderer*, irect* src_rect, irect*, float degree, FlipEnum flip, icolor* tex_color) const override;
     void Destroy() override;
     ~Texture();

 private:
     static vector<Texture*> _instances;
     isize _size;
     SDL_Texture* _texture = nullptr;

     explicit Texture(SDL_Texture* texture);
};

#endif

