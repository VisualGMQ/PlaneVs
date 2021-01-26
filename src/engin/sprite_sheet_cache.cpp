#include "engin/sprite_sheet_cache.hpp"

vector<SpriteSheetCache> SpriteSheetCache::_instances;

SpriteSheetCache* SpriteSheetCache::Create(string sheet_filename) {
    SpriteSheetCache cache(sheet_filename);
    _instances.push_back(std::move(cache));
    return &_instances.back();
}

Sprite* SpriteSheetCache::CreateSprite(string name, irect* area) {
    if (!_repo)
        return nullptr;
    Sprite* sprite = Sprite::create();
    sprite->init(_repo->Get(name), area);
    return sprite;
}
