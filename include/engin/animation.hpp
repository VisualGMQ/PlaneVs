#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "engin/sprite.hpp"
#include "engin/sprite_sheet_cache.hpp"
#include <vector>
using std::vector;


// NOTE abstract class Spritable?
// NOTE abstract Factory<>?

// logic of Animation provided by frames(sprites)
class Animation final {
 public:
     Animation();
     ~Animation() = default;
     void SetPosition(int x, int y);
     void AddFrame(Sprite* frame, int delay);
     void Play() { _is_playing = true; }
     void Pause() { _is_playing = false; }
     void Stop() {
         Pause();
         _cur_frame = 0;
     }
     void Draw();
     void Update();

 private:
    vector<Sprite*> _frames;
    bool _is_playing = false;
    bool _is_loop = false;
    int _cur_frame = 0;
};

#endif

