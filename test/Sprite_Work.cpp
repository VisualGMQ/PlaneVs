#include "engin/exec_body.hpp"
#include "engin/app.hpp"
#include "engin/sprite.hpp"

class Sprite_Workable: public ExecBody {
 public:
    void Init() override {
        _sprite1 = Sprite::Create("./test_resources/sword.png", nullptr);
        _sprite2 = Sprite::Create("./test_resources/cube_man.png", nullptr);

        _sprite1->Show();
        _sprite1->MoveTo(200, 100);
        _sprite1->RotateTo(60);
        _sprite1->ResizeTo(300, 300);
        _sprite1->SetColor(0, 255, 0);
        _sprite1->SetOpacity(100);

        _sprite2->Show();
        _sprite2->MoveTo(400, 200);
        _sprite2->Flip(FLIP_HORIZENTAL);
    }

    void EventHandle(SDL_Event&) override {}

    void Step() override {
        _sprite1->MoveBy(10, 0);
        if (_sprite1->GetPosition().x > 800)
            _sprite1->MoveTo(200, 100);
        _sprite1->Draw();
        _sprite1->Update();
        _sprite2->Draw();
        _sprite2->Update();
    }

    void Destroy() override {

    }
    virtual ~Sprite_Workable() = default;

 private:
    Sprite* _sprite1;
    Sprite* _sprite2;
};


int main(int argc, char** argv) {
    App app;
    app.SetTitle("Sprite Workable");

    Sprite_Workable workable;
    app.SetExecBody(&workable);

    app.Run();
    return 0;
}
