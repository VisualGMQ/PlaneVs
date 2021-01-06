#include "img2file.hpp"

void Img2File(string infofile_filename, string imgfile_filename, const vector<TextureInfo>& texture_infos, SDL_Color keycolor) {
    if (texture_infos.empty())
        return;
    SDL_Point tlpos = {numeric_limits<int>::max(), numeric_limits<int>::max()},
              brpos = {0, 0};
    ofstream file(infofile_filename);
    file << imgfile_filename << endl;
    for (auto& info : texture_infos) {
        SDL_Rect rect = info.GetRectByCenter();
        if (rect.x < tlpos.x)
            tlpos.x = rect.x;
        if (rect.y < tlpos.y)
            tlpos.y = rect.y;
        if (rect.w+rect.x > brpos.x)
            brpos.x = rect.x+rect.w;
        if (rect.h+rect.y > brpos.y)
            brpos.y = rect.y+rect.h;
    }
    for (auto& info : texture_infos) {
        SDL_Rect rect = info.GetRectByCenter();
        file << info.name << " " << rect.x-tlpos.x << " " << rect.y-tlpos.y << " " << rect.w << " " << rect.h << endl;
    }
    file.close();

    SDL_Rect rect = {0, 0, brpos.x-tlpos.x, brpos.y-tlpos.y};
    if (SDL_RectEmpty(&rect)) {
        return;
    }
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, rect.w, rect.h, 32, SDL_PIXELFORMAT_RGBA8888);
    SDL_FillRect(surface, nullptr, SDL_MapRGBA(surface->format, keycolor.r, keycolor.g, keycolor.b, keycolor.a));


    for (auto& info : texture_infos) {
        SDL_Rect dst_rect = info.GetRectByCenter();
        dst_rect.x -= tlpos.x;
        dst_rect.y -= tlpos.y;
        SDL_BlitSurface(info.surface, nullptr, surface, &dst_rect);
    }
    IMG_SavePNG(surface, imgfile_filename.c_str());
    SDL_FreeSurface(surface);
}
