#ifndef TEXTURE_REPO_HPP
#define TEXTURE_REPO_HPP
#include <map>
#include <optional>
#include <vector>
#include <string>
#include <filesystem>

#include "base/log.hpp"
#include "base/geomentry.hpp"
#include "base/drawable.hpp"
#include "base/texture.hpp"
#include "image_sheet/image_sheet.hpp"
using std::map;
using std::string;
using std::vector;
using std::optional;
namespace fs = std::filesystem;

class TextureInSheet final: public ITexture {
 public:
    TextureInSheet() = default;
    TextureInSheet(irect area, Texture* sheet):_area(area),_sheet(sheet) {}
    isize GetSize() const override { return {_area.w, _area.h}; }
    void Draw(irect* src_rect, irect* dst_rect, color* tex_color, color* key_color) const override;
    void Draw(irect* src_rect, irect* dst_rect, float degree, FlipEnum flip, color* tex_color, color* key_color) const override;

 private:
    irect _area;
    Texture* _sheet = nullptr;
};

class TextureRepo final {
 public:
    friend void DbgPrintTextureRepo(TextureRepo* repo);

    static TextureRepo* CreateEmptyRepo();
    static TextureRepo* CreateFromDir(fs::path dir);
    static TextureRepo* CreateFromSheet(fs::path sheet);
    static void FreeAllRepo();
    ~TextureRepo() = default;
    void AddSheet(fs::path json_filename);
    TextureInSheet* operator[](string name);
    int GetSize() const;
    TextureInSheet* Get(string name);
    bool Empty() const;

 private:
    map<string, TextureInSheet> _textures;
    map<string, Texture*> _sheets;
    static vector<TextureRepo*> _repos;

    TextureRepo() = default;
    void loadSheet(fs::path sheet_filename);
};


void DbgPrintTextureRepo(TextureRepo* repo);

#endif

