#include "engin/stage.hpp"
#include "engin/app.hpp"
#include "engin/sprite_sheet_cache.hpp"

#include <array>
using std::array;

class SpriteSheetCache_Work: public Stage {
 public:
    void Init() override {
        _cache = SpriteSheetCache::Create("./test_resources/test_pngs/icons.json");
        _sprites[0] = _cache->CreateSprite("sword1");
        _sprites[1] = _cache->CreateSprite("sword2");
        _sprites[2] = _cache->CreateSprite("sword3");
        _sprites[3] = _cache->CreateSprite("cloth1");
        _sprites[4] = _cache->CreateSprite("cloth2");
        _sprites[5] = _cache->CreateSprite("cloth3");
        for (int i = 0; i < _sprites.size(); i++) {
            _sprites[i]->Show();
            _sprites[i]->MoveTo(100, 100+i*100);
            _sprites[i]->RotateTo(30);
        }
    }

    void EventHandle(SDL_Event&) override {

    }

    void Step() override {
        for (Sprite* sprite : _sprites) {
            sprite->MoveBy(10, 0);
            if (sprite->GetPosition().x > 1000)
                sprite->MoveBy(-900, 0);
            sprite->Draw();
            sprite->Update();
        }
    }

    void Destroy() override {

    }

 private:
    array<Sprite*, 6> _sprites;
    SpriteSheetCache* _cache = nullptr;
};


int main(int argc, char** argv) {
    SpriteSheetCache_Work workable;

    App app(&workable);
    app.SetTitle("Sprite Sheet Cache Workable");

    app.Run();
    return 0;
}
