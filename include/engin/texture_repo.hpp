#ifndef TEXTURE_REPO_HPP
#define TEXTURE_REPO_HPP
#include <map>
#include <optional>
#include <vector>
#include <string>
#include <filesystem>

#include "base/header.hpp"
#include "engin/texture.hpp"
#include "image_sheet/image_sheet.hpp"
using std::map;
using std::string;
using std::vector;
using std::optional;
namespace fs = std::filesystem;

struct TextureInSheet {
    Point position;
    Size size;
    Texture* sheet;
};

class TextureRepo final {
 public:
     static TextureRepo* CreateEmptyRepo();
     static TextureRepo* CreateFromDir(fs::path dir);
     static TextureRepo* CreateFromSheet(fs::path sheet);
     static void FreeAllRepo();
     ~TextureRepo();
     void AddSheet(fs::path json_filename);
     optional<TextureInSheet> operator[](string name);
     optional<TextureInSheet> Get(string name);
     bool Empty() const;
 private:
     map<string, TextureInSheet> _textures;
     map<string, Texture*> _sheets;
     static vector<TextureRepo*> _repos;

     TextureRepo() = default;
     void loadSheet(fs::path sheet_filename);
};

#endif

