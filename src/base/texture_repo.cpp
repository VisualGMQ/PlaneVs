#include "base/texture_repo.hpp"

void TextureInSheet::Draw(irect* src_rect, irect* dst_rect, color* tex_color, color* key_color) const {
    Draw(src_rect, dst_rect, 0, FLIP_NONE, tex_color, key_color);
}

void TextureInSheet::Draw(irect* src_rect, irect* dst_rect, float degree, FlipEnum flip, color* tex_color, color* key_color) const {
    if (!_sheet) {
        Log("TextureInSheet::Draw sheet is nullptr");
        return;
    }
    irect src_rect_;
    if (!src_rect) {
        src_rect_ = _area;
    } else {
        src_rect_.x = _area.x + src_rect->x;
        src_rect_.y = _area.y + src_rect->y;
        src_rect_.w = GetSize().w;
        src_rect_.h = GetSize().h;
    }
    _sheet->Draw(&src_rect_, dst_rect, degree, flip, tex_color, key_color);
}

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

TextureInSheet* TextureRepo::operator[](string name) {
    return Get(name);
}

TextureInSheet* TextureRepo::Get(string name) {
    if (_textures.find(name) == _textures.end())
        return nullptr;
    return &_textures[name];
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
        _textures[image.GetName()] = TextureInSheet({image.GetPosition().x, image.GetPosition().y, image.GetSize().w, image.GetSize().h}, texture);
    }
}

int TextureRepo::GetSize() const {
    return _textures.size();
}
