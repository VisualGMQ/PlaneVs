#include "base/texture.hpp"
#include "engin/stage.hpp"
#include "engin/app.hpp"

#include <iostream>

#include <SDL_image.h>
using namespace std;

class Texture_Work: public Stage {
 public:
    void Init() override {
        _render = Director::GetInstance()->GetRender();
        SDL_Texture* texture = IMG_LoadTexture(_render, "./test_resources/sword.png");
        _texture1 = Texture::Create(texture);
        texture = IMG_LoadTexture(_render, "./test_resources/cube_man.png");
        _texture2 = Texture::Create(texture);
    }

    void EventHandle(SDL_Event&) override {}

    void Step() override {
        irect rect = {100, 100, _texture1->GetSize().w, _texture1->GetSize().h};
        _texture1->Draw(_render, nullptr, &rect, nullptr);
        rect.x = 400;
        rect.w = _texture2->GetSize().w;
        rect.h = _texture2->GetSize().h;
        _texture2->Draw(_render, nullptr, &rect, nullptr);
    }

    void Destroy() override {
        _texture1->Destroy();
        _texture2->Destroy();
    }

    virtual ~Texture_Work() = default;
    
 private:
    Texture* _texture1 = nullptr;
    Texture* _texture2 = nullptr;
    SDL_Renderer* _render = nullptr;

};

int main(int argc, char** argv) {
    Texture_Work workable;

    App app(&workable);
    app.SetTitle("Texture Workale");

    app.Run();
    return 0;
}
