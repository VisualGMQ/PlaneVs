#include "engin/bgm.hpp"

Mix_Music* Bgm::_music = nullptr;

void Bgm::Load(string filename) {
    if (_music)
        Mix_FreeMusic(_music);
    _music = Mix_LoadMUS(filename.c_str());
    if (!_music)
        Logw("Bgm::Load", "%s load failed", filename.c_str());
}

void Bgm::Play(int loops) {
    if (_music)
        Mix_PlayMusic(_music, loops);
}

bool Bgm::IsPlaying() {
    return Mix_PlayingMusic();
}

void Bgm::Rewind() {
    Mix_RewindMusic();
}

void Bgm::Pause() {
    Mix_PauseMusic();
}

void Bgm::Stop() {
    Mix_RewindMusic();
}

void Bgm::FadeOut(int ms) {
    Mix_FadeOutMusic(ms);
}

void Bgm::FadeIn(int loops, int ms) {
    Mix_FadeInMusic(_music, loops, ms);
}

void Bgm::Destroy() {
    Mix_FreeMusic(_music);
}

void Bgm::SetVolumn(float volumn) {
    volumn = Clamp(0.0f, 1.0f, volumn);
    Mix_VolumeMusic(MIX_MAX_VOLUME*volumn);
}
