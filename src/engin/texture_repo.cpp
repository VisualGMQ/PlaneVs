#include "engin/texture_repo.hpp"

vector<TextureRepo*> TextureRepo::_repos;

void TextureRepo::FreeAllRepo() {
    for (TextureRepo* repo : _repos)
        delete repo;
}

TextureRepo* TextureRepo::CreateEmptyRepo() {
    TextureRepo* repo = new TextureRepo;
    _repos.push_back(repo);
    return repo;
}

TextureRepo* TextureRepo::CreateFromSheet(fs::path sheet) {
    TextureRepo* repo = new TextureRepo;
    repo->AddSheet(sheet);
    _repos.push_back(repo);
    return repo;
}

TextureRepo* TextureRepo::CreateFromDir(fs::path dir) {
    TextureRepo* repo = new TextureRepo;
    if (fs::exists(dir) && fs::is_directory(dir)) {
        for (auto& p : fs::recursive_directory_iterator(dir)) {
            if (p.path().extension() == ".json") {
                repo->AddSheet(p.path());
            }
        }
    }
    _repos.push_back(repo);
    return repo;
}

optional<TextureInSheet> TextureRepo::Get(string name) {
    if (_textures.find(name) == _textures.end())
        return std::nullopt;
    return optional(_textures[name]);
}

optional<TextureInSheet> TextureRepo::operator[](string name) {
    return Get(name);
}

bool TextureRepo::Empty() const {
    return _sheets.empty() && _textures.empty();
}

void TextureRepo::AddSheet(fs::path json_filename) {
    loadSheet(json_filename);
}

void TextureRepo::loadSheet(fs::path sheet_filename) {
    if (!fs::exists(sheet_filename)) {
        Log("%s not exists", sheet_filename.string().c_str());
        return;
    }
    auto image_sheet = ImageSheet::ReadFromJson(sheet_filename);
    string image_filename = image_sheet.GetImageFilename();
    Texture* texture = nullptr;
    if (_sheets.find(image_filename) != _sheets.end()) {
        Log("%s has exists in Repo", image_filename.c_str());
        return;
    }
    texture = new Texture(image_filename);
    _sheets[image_filename] = texture;
    for (const ImageInSheet& image : image_sheet.GetImages()) {
        if (_textures.find(image.GetName()) != _textures.end()) {
            Log("%s has in Repo", image.GetName().c_str());
            continue;
        }
        _textures[image.GetName()] = {.position = image.GetPosition(), .size = image.GetSize(), .sheet = texture};
    }
}

TextureRepo::~TextureRepo() {
    for (auto& [key, texture] : _sheets)
        delete texture;
}
