#include "engin/stage.hpp"
#include "engin/app.hpp"
#include "engin/music_repo.hpp"

#include <iostream>
using namespace std;

class Music_Work: public Stage {
 public:
    void Init() override {
        _repo = MusicRepo::Create();
        Music* music1, *music2;
        music1 = _repo->LoadMusic("./test_resources/Mind Control.ogg");
        music2 = _repo->LoadMusic("./test_resources/Randomize.wav");
        music1->FadeIn(0, 5000);
        music2->Play(0);
        music2->SetVolumn(0.5);
    }

    void EventHandle(SDL_Event&) override {}

    void Step() override {
    }

    void Destroy() override {
        _repo->Destroy();
    }

    virtual ~Music_Work() = default;
    
 private:
    MusicRepo* _repo = nullptr;
};

int main(int argc, char** argv) {
    Music_Work workable;

    App app(&workable);
    app.SetTitle("Music Workable");

    app.Run();
    return 0;
}
