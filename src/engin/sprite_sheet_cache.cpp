#include "engin/sprite_sheet_cache.hpp"

forward_list<SpriteSheetCache> SpriteSheetCache::_instances;

SpriteSheetCache* SpriteSheetCache::Create(string sheet_filename, icolor* key_color) {
    SpriteSheetCache cache(sheet_filename, key_color);
    SpriteSheetCache::_instances.push_front(cache);
    return &SpriteSheetCache::_instances.front();
}

Sprite* SpriteSheetCache::CreateSprite(string name, irect* area) {
    if (!_repo)
        return nullptr;
    Sprite* sprite = Sprite::create();
    sprite->init(_repo->Get(name), area);
    return sprite;
}
