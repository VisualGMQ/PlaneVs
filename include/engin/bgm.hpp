#ifndef BGM_HPP
#define BGM_HPP
#include <string>

#include <SDL_mixer.h>

#include "base/log.hpp"
#include "base/tools.hpp"
using std::string;

class Bgm {
 public:
    static void Load(string filename);
    static void Play(int loops);
    static bool IsPlaying();
    static void FadeIn(int loops, int ms);
    static void Pause();
    static void Stop();
    static void Rewind();
    static void FadeOut(int ms);
    static void Destroy();
    static void SetVolumn(float volumn);

 private:
    static Mix_Music* _music;
    
};

#endif

