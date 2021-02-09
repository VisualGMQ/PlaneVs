#include "engin/stage.hpp"
#include "engin/app.hpp"
#include "engin/sprite_sheet_cache.hpp"
#include "engin/animation.hpp"

class SpriteSheetCache_Work: public Stage {
 public:
    void Init() override {
        _cache = SpriteSheetCache::Create("./test_resources/mario/mario.json");
        _animation = Animation::Create();
        for (int i = 0; i < 6; i++)
            _animation->AddFrame(_cache->CreateSprite("Mario_walk" + to_string(i+1)), 3);

        _animation->MoveTo(300, 300);
        _animation->Scale(4, 4);
        _animation->SetLoop(Animation::LOOP_INFINITE);
        _animation->EnableRestoreOriginFrame();
        _animation->SetFlip(FLIP_HORIZENTAL);
        _animation->Show();
        _animation->Play();
    }

    void EventHandle(SDL_Event&) override {

    }

    void Step() override {
        _animation->Update();
        _animation->Draw();
    }

    void Destroy() override {

    }

 private:
    Animation* _animation = nullptr;
    SpriteSheetCache* _cache = nullptr;
};


int main(int argc, char** argv) {
    SpriteSheetCache_Work workable;

    App app(&workable);
    app.SetTitle("Sprite Sheet Cache Workable");

    app.Run();
    return 0;
}
