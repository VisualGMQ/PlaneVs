#include "base/exec_body.hpp"
#include "engin/app.hpp"
#include "engin/texture_repo.hpp"

#include <iostream>
using namespace std;

class TextureRepo_Work: public ExecBody {
 public:
    void Init() override {
        _repo = TextureRepo::CreateFromSheet("./test_resources/test_pngs/icons.json");
    }

    void EventHandle(SDL_Event&) override {}

    void Step() override {
        drawSheet("cloth1", 50, 50);
        drawSheet("cloth2", 150, 50);
        drawSheet("cloth3", 250, 50);
        drawSheet("sword1", 350, 50);
        drawSheet("sword2", 450, 50);
        drawSheet("sword3", 550, 50);
    }

    void Destroy() override {
        TextureRepo::FreeAllRepo();
    }

    virtual ~TextureRepo_Work() = default;
    
 private:
    TextureRepo* _repo = nullptr;

    void drawSheet(string name, int x, int y) {
        auto texture = _repo->Get(name);
        if (texture.has_value()) {
            irect dst_rect = texture->area;
            dst_rect.x = x;
            dst_rect.y = y;
            texture->sheet->Draw(texture->area, dst_rect);
        } else {
            Log("%s can't find", name.c_str());
        }
    }

};

int main(int argc, char** argv) {
    App app;
    app.SetTitle("TextureRepo Workale");

    TextureRepo_Work workable;
    app.SetExecBody(&workable);

    app.Run();
    return 0;
}
