#include "engin/music.hpp"

vector<Music*> Music::_instances;

void Music::StopAllMusic() {
    Mix_HaltChannel(-1);
}

Music* Music::Create(string filename) {
    Music* music = new Music;
    music->load(filename);
    _instances.push_back(music);
    return music;
}

void Music::DestroyAll() {
    for (Music* music : _instances) {
        delete music;
    }
    _instances.clear();
}

void Music::load(string wav_filename) {
    if (_chunk)
        Mix_FreeChunk(_chunk);
    _chunk = Mix_LoadWAV(wav_filename.c_str());
}

void Music::Play(int loops) {
    _channel = Mix_PlayChannel(-1, _chunk, loops);
}

void Music::FadeIn(int loops, int ms) {
    Mix_FadeInChannel(-1, _chunk, loops, ms);
}

void Music::Rewind() {
    Play(0);
}

void Music::SetVolumn(float volumn) const {
    if (_chunk)
        Mix_VolumeChunk(_chunk, MIX_MAX_VOLUME*Clamp(0.0f, 1.0f, volumn));
}

Music::~Music() {
    Mix_FreeChunk(_chunk);
}

void Music::Destroy() {
    auto it = std::find(_instances.begin(), _instances.end(), this);
    if (it != _instances.end()) {
        Music* tmp = *it;
        _instances.erase(it);
        delete tmp;
    }
}
