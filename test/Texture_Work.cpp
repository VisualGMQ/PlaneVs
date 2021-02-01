#include "base/texture.hpp"
#include "engin/exec_body.hpp"
#include "engin/app.hpp"

#include <iostream>

#include <SDL_image.h>
using namespace std;

class Texture_Work: public ExecBody {
 public:
    void Init() override {
        SDL_Surface* surface = IMG_Load("./test_resources/sword.png");
        _texture1 = Texture::Create(surface);
        SDL_FreeSurface(surface);
        surface = IMG_Load("./test_resources/cube_man.png");
        _texture2 = Texture::Create(surface);
        SDL_FreeSurface(surface);
    }

    void EventHandle(SDL_Event&) override {}

    void Step() override {
        irect rect = {100, 100, _texture1->GetSize().w, _texture1->GetSize().h};
        _texture1->Draw(nullptr, &rect, nullptr, nullptr);
        rect.x = 400;
        rect.w = _texture2->GetSize().w;
        rect.h = _texture2->GetSize().h;
        _texture2->Draw(nullptr, &rect, nullptr, nullptr);
    }

    void Destroy() override {
        _texture1->Destroy();
        _texture2->Destroy();
    }

    virtual ~Texture_Work() = default;
    
 private:
    Texture* _texture1 = nullptr;
    Texture* _texture2 = nullptr;

};

int main(int argc, char** argv) {
    App app;
    app.SetTitle("Texture Workale");

    Texture_Work workable;
    app.SetExecBody(&workable);

    app.Run();
    return 0;
}
