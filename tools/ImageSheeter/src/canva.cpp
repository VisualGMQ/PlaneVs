#include "canva.hpp"

void Canva::InitResources(SDL_Window* window) {
    _hint.SetRender(GetRender());
    _hint.InitFont();
    _hint.Hide();
}

string GetNameWithoutExtension(string filename) {
    return filename.substr(0, filename.find('.'));
}

void Canva::onMouseMotion(SDL_Event& event) {
    SDL_Point mouse_pos = {event.motion.x, event.motion.y};
    for (auto& info : _texture_infos) {
        if (info.IsClicked(mouse_pos)) {
            _focused_texture = &info;
            return;
        }
    }
    _focused_texture = nullptr;

    if (_space_pressed) {
        for (auto& info : _texture_infos) {
            info.position.x += event.motion.xrel;
            info.position.y += event.motion.yrel;
        }
    }
}

void Canva::onMouseLeftDown(SDL_Event& event) {
    SDL_Point mouse_pos = {event.motion.x, event.motion.y};
    for (auto& info : _texture_infos) {
        if (info.IsClicked(mouse_pos)) {
            _selected_texture = &info;
            return;
        }
    }
    _selected_texture = nullptr;
}

void Canva::onDrag(SDL_Event& event) {
    if (_selected_texture) {
        _selected_texture->position.x = event.motion.x;
        _selected_texture->position.y = event.motion.y;

        _collied_textures.clear();
        calcCollidTexture();
    }
}

void Canva::calcCollidTexture() {
    _collied_textures.clear();
    for (auto& info : _texture_infos) {
        SDL_Rect rect1 = _selected_texture->GetRectByCenter(),
                 rect2 = info.GetRectByCenter();
        if (info.name != _selected_texture->name && SDL_HasIntersection(&rect1, &rect2)) {
            _collied_textures.push_back(&info);
        }
    }
}

void Canva::Paint() {
    auto render = GetRender();
    SDL_Rect rect;
    for (auto& info : _texture_infos) {
        rect = info.GetRectByCenter();
        SDL_RenderCopy(render, info.texture, nullptr, &rect);
    }
    if (_selected_texture) {
        rect = _selected_texture->GetRectByCenter();
        SDL_RenderCopy(render, _selected_texture->texture, nullptr, &rect);
        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        SDL_RenderDrawRect(GetRender(), &rect);
    }
    if (_focused_texture && _focused_texture != _selected_texture) {
        rect = _focused_texture->GetRectByCenter();
        SDL_RenderCopy(render, _focused_texture->texture, nullptr, &rect);
        SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
        SDL_RenderDrawRect(render, &rect);

    }

    // paint hint
    if (_focused_texture) {
        TextureInfo* info = _focused_texture;
        _hint.SetText(info->name);
        auto hint_size = _hint.GetSize();
        _hint.SetPosition({info->position.x, info->position.y - hint_size.h/2 - info->size.h/2});
        _hint.Show();
    } else {
        _hint.Hide();
    }

    for (auto& info : _collied_textures) {
        rect = info->GetRectByCenter();
        SDL_SetRenderDrawColor(render, 255, 255, 0, 255);
        SDL_RenderDrawRect(render, &rect);
    }
    _hint.Paint();
}

void Canva::onDropFile(SDL_Event&, fs::path file_path) {
    SDL_Log("%s", file_path.c_str());
    if (!fs::exists(file_path)) {
        SDL_Log("%s not exists", file_path.c_str());
        return;
    }
    auto extension = file_path.extension();
    if (extension != ".png" && extension != ".jpg" &&
            extension != ".gif" && extension != "jpeg" &&
            extension != ".bmp") {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "错误的文件", "请拖入图像文件(png,jpg,gif,bmp)", nullptr);
        return;
    }

    for (auto& info : _texture_infos) {
        string name_without_extension = GetNameWithoutExtension(file_path.filename().string());
        if (info.name == name_without_extension) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "重命名的文件", "已经存在同名文件，请将拖入的文件重命名之后再尝试拖入", nullptr);
            return;
        }
    }

    TextureInfo info = loadTexture(file_path);
    if (info.texture)
        _texture_infos.push_back(info);

    for (auto& info : _texture_infos)
        SDL_Log("<has_image=%s, name=%s, pos=(%d, %d), size=(%d, %d)>", info.texture?"true":"false", info.name.c_str(), info.position.x, info.position.y, info.size.w, info.size.h);

    _selected_texture = nullptr;
    _focused_texture = nullptr;
}

void Canva::onKeyDown(SDL_Event& event) {
    if (_selected_texture) {
        if (event.key.keysym.sym == SDLK_DOWN) {
            _selected_texture->position.y += 1;
            calcCollidTexture();
        }
        if (event.key.keysym.sym == SDLK_UP) {
            _selected_texture->position.y -= 1;
            calcCollidTexture();
        }
        if (event.key.keysym.sym == SDLK_LEFT) {
            _selected_texture->position.x -= 1;
            calcCollidTexture();
        }
        if (event.key.keysym.sym == SDLK_RIGHT) {
            _selected_texture->position.x += 1;
            calcCollidTexture();
        }
    }
    if (event.key.keysym.sym == SDLK_SPACE) {
        _space_pressed = true;
    }
    if (event.key.keysym.sym == SDLK_RETURN) {
        SaveImage();
    }
    if (event.key.keysym.sym == SDLK_BACKSPACE) {
        if (_selected_texture && !_texture_infos.empty()) {
            int pos = 0;
            for (; pos < _texture_infos.size(); pos++) {
                if (_texture_infos[pos].name == _selected_texture->name)
                    break;
            }
            if (pos < _texture_infos.size()) {
                auto it = _texture_infos.begin() += pos;
                _texture_infos.erase(it);
                _selected_texture = nullptr;
                _focused_texture = nullptr;
            }
        }
    }
}

void Canva::SaveImage() {
    const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, "不保存" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "保存" }
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };

    auto cur_path = fs::current_path();
    string msg = "文件会保存到"+cur_path.string()+"/image.png\n要保存吗";
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        nullptr, /* .window */
        "要保存吗", /* .title */
        msg.c_str(), /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        return;
    }
    if (buttonid == 1) {
        Img2File("info.txt", "image.png", _texture_infos, {100, 100, 100, 255});
    }
}

void Canva::onKeyUp(SDL_Event& event) {
    if (event.key.keysym.sym == SDLK_SPACE) {
        _space_pressed = false;
    }
}

TextureInfo Canva::loadTexture(fs::path& path) {
    auto render = GetRender();
    SDL_Surface* surface = IMG_Load(path.c_str());
    TextureInfo info = {.name = GetNameWithoutExtension(path.filename().string()), .texture = nullptr, .surface = nullptr, .position = {surface->w/2, surface->h/2}, .size = {surface->w, surface->h}};
    if (!surface) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "error", (string(path.filename().c_str())+" load failed").c_str(), nullptr);
        return info;
    }
    info.surface = surface;
    info.texture = SDL_CreateTextureFromSurface(render, surface);
    if (!info.texture) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "error", "texture create failed", nullptr);
        return info;
    }
    return info;
}

void Canva::Exit() {
}

Canva::~Canva() {
    for (auto& info : _texture_infos) {
        SDL_DestroyTexture(info.texture);
        SDL_FreeSurface(info.surface);
    }
}
