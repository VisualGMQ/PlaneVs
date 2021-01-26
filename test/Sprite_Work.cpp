#include "engin/exec_body.hpp"
#include "engin/app.hpp"
#include "engin/sprite.hpp"

class Sprite_Workable: public ExecBody {
 public:
    void Init() override {
        _sprite = Sprite::Create("test_resources/cube_man.png");
        _sprite->Show();
        _sprite->MoveTo(200, 100);
        _sprite->SetRotation(60);
        _sprite->SetSize(300, 300);
        _sprite->SetColor(0, 1, 0);
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
    Sprite* _sprite;
};


int main(int argc, char** argv) {
    App app;
    app.SetTitle("Sprite Workable");

    Sprite_Workable workable;
    app.SetExecBody(&workable);

    app.Run();
    return 0;
}
