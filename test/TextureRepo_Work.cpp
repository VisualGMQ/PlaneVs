#include "base/texture_repo.hpp"
#include "engin/stage.hpp"
#include "engin/app.hpp"

#include <iostream>
using namespace std;

class TextureRepo_Work: public Stage {
 public:
    void Init() override {
        SetLogLevel(LOG_ALL);
        _render = Director::GetInstance()->GetRender();
        _repo1 = TextureRepo::CreateFromSheet(_render, "./test_resources/test_pngs/icons.json");
        _repo2 = TextureRepo::CreateFromSheet(_render, "./test_resources/mario/mario.json");
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
    SDL_Renderer* _render = nullptr;

    void drawSheet(TextureRepo* repo, string name, int x, int y) {
        auto texture = repo->Get(name);
        if (texture) {
            irect dst_rect = {x, y, texture->GetSize().w, texture->GetSize().h};
            texture->Draw(_render, nullptr, &dst_rect, nullptr);
        } else {
            Loge("TextureRepo_Work::drawSheet", "%s can't find", name.c_str());
        }
    }

};

int main(int argc, char** argv) {
    TextureRepo_Work workable;

    App app(&workable);
    app.SetTitle("TextureRepo Workale");

    app.Run();
    return 0;
}
