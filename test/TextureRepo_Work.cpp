#include "base/exec_body.hpp"
#include "engin/app.hpp"
#include "engin/texture_repo.hpp"

#include <iostream>
using namespace std;

class TextureRepo_Work: public ExecBody {
 public:
     void Init() override {
         _repo = TextureRepo::CreateFromSheet("./test/test_bombs/bomb.json");
     }

     void EventHandle(SDL_Event&) override {}

     void Step() override {
         auto texture = _repo->Get("bomb1");
         // TODO not finish
     }

     void Destroy() override {
         TextureRepo::FreeAllRepo();
     }

     virtual ~TextureRepo_Work() = default;
    
 private:
     TextureRepo* _repo = nullptr;
};

int main(int argc, char** argv) {
    App app;
    app.SetTitle("TextureRepo Workale");

    TextureRepo_Work workable;
    app.SetExecBody(&workable);

    app.Run();
    return 0;
}
