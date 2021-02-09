#ifndef SPRITE_SHEET_CACHE_HPP
#define SPRITE_SHEET_CACHE_HPP
#include <forward_list>
#include <string>

#include "base/texture_repo.hpp"
#include "base/geo_math.hpp"
#include "engin/sprite.hpp"
#include "engin/director.hpp"
using std::forward_list;

class SpriteSheetCache final {
 public:
    static SpriteSheetCache* Create(string sheet_filename, icolor* key_color = nullptr);

    Sprite* CreateSprite(string name, irect* area = nullptr);

 private:
    static forward_list<SpriteSheetCache> _instances;
    TextureRepo* _repo = nullptr;

    SpriteSheetCache(string sheet_filename, icolor* key_color) {
        _repo = TextureRepo::CreateFromSheet(Director::GetInstance()->GetRender(), sheet_filename, key_color);
    }
};

#endif

