#include "base/texture_repo.hpp"

void TextureInSheet::Draw(SDL_Renderer* render, irect* src_rect, irect* dst_rect, icolor* tex_color) const {
    Draw(render, src_rect, dst_rect, 0, FLIP_NONE, tex_color);
}

void TextureInSheet::Draw(SDL_Renderer* render, irect* src_rect, irect* dst_rect, float degree, FlipEnum flip, icolor* tex_color) const {
    if (!_sheet) {
        Logw("TextureInSheet::Draw", "TextureInSheet::Draw sheet is nullptr");
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
    _sheet->Draw(render, &src_rect_, dst_rect, degree, flip, tex_color);
}

forward_list<TextureRepo> TextureRepo::_instances;

TextureRepo* TextureRepo::CreateEmptyRepo() {
    _instances.push_front(TextureRepo());
    return &_instances.front();
}

TextureRepo* TextureRepo::CreateFromSheet(SDL_Renderer* render, fs::path sheet, icolor* key_color) {
    _instances.push_front(TextureRepo());
    TextureRepo& repo = _instances.front();
    repo.AddSheet(render, sheet, key_color);
    return &repo;
}

TextureRepo* TextureRepo::CreateFromDir(SDL_Renderer* render, fs::path dir, icolor* key_color) {
    _instances.push_front(TextureRepo());
    TextureRepo& repo = _instances.front();
    if (fs::exists(dir) && fs::is_directory(dir)) {
        for (auto& p : fs::recursive_directory_iterator(dir)) {
            if (p.path().extension() == ".json") {
                repo.AddSheet(render, p.path(), key_color);
            }
        }
    }
    return &repo;
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

void TextureRepo::AddSheet(SDL_Renderer* render, fs::path json_filename, icolor* key_color) {
    loadSheet(render, json_filename, key_color);
}

void TextureRepo::loadSheet(SDL_Renderer* render, fs::path sheet_filename, icolor* key_color) {
    if (!fs::exists(sheet_filename)) {
        Logw("TextureRepo::loadSheet" ,"%s not exists", sheet_filename.string().c_str());
        return;
    }
    auto image_sheet = ImageSheet::ReadFromJson(sheet_filename);
    string image_filename = image_sheet.GetImageFilename();
    if (_sheets.find(image_filename) != _sheets.end()) {
        Logw("TextureRepoi::loadSheet", "%s has exists in Repo", image_filename.c_str());
        return;
    }
    SDL_Surface* surface = IMG_Load(image_filename.c_str());
    if (key_color)
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, key_color->r, key_color->g, key_color->b));
    SDL_Texture* tex = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    Texture* texture = Texture::Create(tex);
    _sheets[image_filename] = texture;
    for (const ImageInSheet& image : image_sheet.GetImages()) {
        if (_textures.find(image.GetName()) != _textures.end()) {
            Logw("TextureRepo::loadSheet", "%s has in Repo", image.GetName().c_str());
            continue;
        }
        _textures[image.GetName()] = TextureInSheet({image.GetPosition().x, image.GetPosition().y, image.GetSize().w, image.GetSize().h}, texture);
    }
}

int TextureRepo::GetSize() const {
    return _textures.size();
}

TextureRepo::~TextureRepo() {
    for (auto& [key, value] : _sheets)
        value->Destroy();
}

void TextureRepo::Destroy() {
    _instances.remove_if([&](TextureRepo& repo){ return &repo == this; });
}
