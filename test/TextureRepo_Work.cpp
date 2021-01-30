#include "base/texture_repo.hpp"
#include "engin/exec_body.hpp"
#include "engin/app.hpp"

#include <iostream>
using namespace std;

class TextureRepo_Work: public ExecBody {
 public:
    void Init() override {
        _repo1 = TextureRepo::CreateFromSheet("./test_resources/test_pngs/icons.json");
        _repo2 = TextureRepo::CreateFromSheet("./test_resources/mario/mario.json");
    }

    void EventHandle(SDL_Event&) override {}

    void Step() override {
        drawSheet(_repo1, "cloth1", 50, 50);
        drawSheet(_repo1, "cloth2", 150, 50);
        drawSheet(_repo1, "cloth3", 250, 50);
        drawSheet(_repo1, "sword1", 350, 50);
        drawSheet(_repo1, "sword2", 450, 50);
        drawSheet(_repo1, "sword3", 550, 50);

        drawSheet(_repo2, "Mario_walk1", 150, 150);
        drawSheet(_repo2, "Mario_walk2", 250, 150);
        drawSheet(_repo2, "Mario_walk3", 350, 150);
        drawSheet(_repo2, "Mario_walk4", 450, 150);
        drawSheet(_repo2, "Mario_walk5", 550, 150);
        drawSheet(_repo2, "Mario_walk6", 650, 150);
    }

    void Destroy() override {}

    virtual ~TextureRepo_Work() = default;
    
 private:
    TextureRepo* _repo1 = nullptr;
    TextureRepo* _repo2 = nullptr;

    void drawSheet(TextureRepo* repo, string name, int x, int y) {
        auto texture = repo->Get(name);
        if (texture) {
            irect dst_rect = {x, y, texture->GetSize().w, texture->GetSize().h};
            texture->Draw(nullptr, &dst_rect, nullptr, nullptr);
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
