#ifndef MUSIC_HPP
#define MUSIC_HPP
#include <string>
#include <map>
#include <vector>

#include <SDL_mixer.h>

#include "base/destroyable.hpp"
#include "base/tools.hpp"
using std::string;
using std::map;
using std::vector;

class IMusic: public Destroyable {
 public:
     virtual void SetVolumn(float volumn) const = 0;
     virtual void Play(int loops) = 0;
     virtual void FadeIn(int loops, int ms) = 0;
     virtual void Rewind() = 0;
};

class Music: public IMusic {
 public:
    static Music* Create(string filename);    

    static void StopAllMusic();

    void Play(int loops) override;
    void FadeIn(int loops, int ms) override;
    void Rewind() override;
    void Destroy() override;
    void SetVolumn(float volumn) const override;
    virtual ~Music();

 private:
    Mix_Chunk* _chunk = nullptr;
    int _channel = -1;

    Music() = default;
    void load(string wav_filename);
    
    static vector<Music*> _instances;
};

#endif

