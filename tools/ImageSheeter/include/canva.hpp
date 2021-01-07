#ifndef CANVA_HPP
#define CANVA_HPP
#include <string>
#include <vector>
#include <iterator>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "uiobject.hpp"
#include "header.hpp"
#include "label.hpp"
#include "img2file.hpp"
using std::string;
using std::vector;
using std::advance;
namespace fs = std::filesystem;

string GetNameWithoutExtension(string filename);

class Canva final: public UIObject {
 public:
    Canva() = default;
    void InitResources(SDL_Window*);
    void Paint() override;
    void Exit();
    virtual ~Canva();

 protected:
    void onMouseMotion(SDL_Event&) override;
    void onMouseLeftDown(SDL_Event&) override;
    void onDrag(SDL_Event&) override;
    void onDropFile(SDL_Event&, fs::path file_path) override;
    void onKeyDown(SDL_Event&) override;
    void onKeyUp(SDL_Event&) override;

 private:
    vector<TextureInfo> _texture_infos;
    vector<TextureInfo*> _collied_textures;
    TextureInfo* _focused_texture = nullptr;
    TextureInfo* _selected_texture = nullptr;
    Label _hint;
    bool _space_pressed = false;

    TextureInfo loadTexture(fs::path&);
    void calcCollidTexture();
    void SaveImage();
};

#endif
