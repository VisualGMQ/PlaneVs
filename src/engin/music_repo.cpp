#include "engin/music_repo.hpp"

list<MusicRepo> MusicRepo::_instances;

MusicRepo* MusicRepo::Create() {
    _instances.emplace_front();
    return &_instances.front();
}

Music* MusicRepo::LoadMusic(string filename) {
    Music* music = Music::Create(filename);
    _musics[Filename2Name(filename)] = music;
    return music;
}

Music* MusicRepo::Get(string name) {
    auto it = _musics.find(name);
    if (it != _musics.end())
        return it->second;
    return nullptr;
}

void MusicRepo::Destroy() {
    _instances.remove_if([&](MusicRepo& repo){ return &repo == this; });
}

MusicRepo::~MusicRepo() {
    for (auto& [key, value] : _musics)
        value->Destroy();
    _musics.clear();
}
