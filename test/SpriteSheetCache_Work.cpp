#include "engin/exec_body.hpp"
#include "engin/app.hpp"
#include "engin/sprite_sheet_cache.hpp"

class SpriteSheetCache_Work: public ExecBody {
 public:
    void Init() override {
        _cache = SpriteSheetCache::Create("./test_resources/test_pngs/icons.json");
        _sprite = _cache->CreateSprite("sword1");
        _sprite->Show();
        _sprite->MoveTo(200, 100);
        _sprite->SetRotation(60);
        _sprite->SetSize(300, 300);
    }

    void EventHandle(SDL_Event&) override {

    }

    void Step() override {
        _sprite->Move(10, 0);
        if (_sprite->GetPosition().x > 400)
            _sprite->SetFlip(FLIP_HORIZENTAL);
        else
            _sprite->SetFlip(FLIP_BOTH);

        if (_sprite->GetPosition().x > 800)
            _sprite->MoveTo(200, 100);
        _sprite->Draw();
        _sprite->Update();
    }

    void Destroy() override {

    }
 private:
    Sprite* _sprite = nullptr;
    SpriteSheetCache* _cache = nullptr;
};


int main(int argc, char** argv) {
    App app;
    app.SetTitle("Sprite Sheet Cache Workable");

    SpriteSheetCache_Work workable;
    app.SetExecBody(&workable);

    app.Run();
    return 0;
}
