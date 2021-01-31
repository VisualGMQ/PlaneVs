#include "engin/exec_body.hpp"
#include "engin/app.hpp"
#include "engin/music.hpp"

#include <iostream>
using namespace std;

class Music_Work: public ExecBody {
 public:
    void Init() override {
        _music1 = Music::Create("./test_resources/Mind Control.ogg");
        _music2 = Music::Create("./test_resources/Randomize.wav");
        _music1->FadeIn(0, 5000);
        _music2->Play(0);
        _music2->SetVolumn(0.5);
    }

    void EventHandle(SDL_Event&) override {}

    void Step() override {
    }

    void Destroy() override {
        _music1->Destroy();
        _music2->Destroy();
    }

    virtual ~Music_Work() = default;
    
 private:
    Music* _music1 = nullptr;
    Music* _music2 = nullptr;
};

int main(int argc, char** argv) {
    App app;
    app.SetTitle("Music Workable");

    Music_Work workable;
    app.SetExecBody(&workable);

    app.Run();
    return 0;
}
