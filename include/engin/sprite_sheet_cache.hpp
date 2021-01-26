#ifndef SPRITE_SHEET_CACHE_HPP
#define SPRITE_SHEET_CACHE_HPP
#include <vector>
#include <string>

#include "base/texture_repo.hpp"
#include "base/geomentry.hpp"
#include "engin/sprite.hpp"
using std::vector;

class SpriteSheetCache final {
 public:
    static SpriteSheetCache* Create(string sheet_filename);

    Sprite* CreateSprite(string name, irect* area = nullptr);

 private:
    static vector<SpriteSheetCache> _instances;
    TextureRepo* _repo = nullptr;

    SpriteSheetCache(string sheet_filename) {
        _repo = TextureRepo::CreateFromSheet(sheet_filename);
    }

    ITexture* get(string name) {
        return (*_repo)[name];
    }
};

#endif

