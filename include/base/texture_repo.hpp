#ifndef TEXTURE_REPO_HPP
#define TEXTURE_REPO_HPP
#include <map>
#include <forward_list>
#include <string>
#include <filesystem>

#include "base/log.hpp"
#include "base/geo_math.hpp"
#include "base/texture_drawable.hpp"
#include "base/texture.hpp"
#include "base/destroyable.hpp"
#include "base/image_sheet.hpp"
using std::map;
using std::string;
using std::forward_list;
namespace fs = std::filesystem;

class TextureInSheet final: public ITexture {
 public:
    TextureInSheet() = default;
    TextureInSheet(irect area, Texture* sheet):_area(area),_sheet(sheet) {}
    isize GetSize() const override { return {_area.w, _area.h}; }
    void Draw(SDL_Renderer*,irect* src_rect, irect* dst_rect, icolor* tex_color) const override;
    void Draw(SDL_Renderer*, irect* src_rect, irect* dst_rect, float degree, FlipEnum flip, icolor* tex_color) const override;

 private:
    irect _area;
    Texture* _sheet = nullptr;
};

class TextureRepo final: public Destroyable {
 public:
    static TextureRepo* CreateEmptyRepo();
    static TextureRepo* CreateFromDir(SDL_Renderer* render, fs::path dir, icolor* key_color = nullptr);
    static TextureRepo* CreateFromSheet(SDL_Renderer* render, fs::path sheet, icolor* key_color = nullptr);
    static void DestroyAll() {
        _instances.clear();
    }
    ~TextureRepo();
    void AddSheet(SDL_Renderer* render, fs::path json_filename, icolor* key_color);
    TextureInSheet* operator[](string name);
    int GetSize() const;
    TextureInSheet* Get(string name);
    bool Empty() const;
    void Destroy() override;

 private:
    map<string, TextureInSheet> _textures;
    map<string, Texture*> _sheets;
    static forward_list<TextureRepo> _instances;

    TextureRepo() = default;
    void loadSheet(SDL_Renderer* render, fs::path sheet_filename, icolor* key_color);
};


#endif

