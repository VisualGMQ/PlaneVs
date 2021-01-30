#ifndef SPRITE_SHEET_CACHE_HPP
#define SPRITE_SHEET_CACHE_HPP
#include <forward_list>
#include <string>

#include "base/texture_repo.hpp"
#include "base/geomentry.hpp"
#include "engin/sprite.hpp"
using std::forward_list;

class SpriteSheetCache final {
 public:
    static SpriteSheetCache* Create(string sheet_filename);
    static void Destroy();

    Sprite* CreateSprite(string name, irect* area = nullptr);

 private:
    static forward_list<SpriteSheetCache> _instances;
    TextureRepo* _repo = nullptr;

    SpriteSheetCache(string sheet_filename) {
        _repo = TextureRepo::CreateFromSheet(sheet_filename);
    }
};

#endif

