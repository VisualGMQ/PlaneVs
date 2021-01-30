#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <forward_list>

#include <glm/glm.hpp>

#include "engin/sprite.hpp"
#include "engin/drawable.hpp"
#include "engin/updatable.hpp"
#include "engin/visiable.hpp"

using std::forward_list;
using glm::ivec2;
using glm::vec2;

class Animation final: virtual public Visiable, public Drawable, public Updatable {
 public:
    static Animation* Create();

    enum {
        LOOP_INFINITE = -1,
        LOOP_NOLOOP = 0
    };
    void Rotate(float degree);
    float GetRotation() const { return _degree; }
    void Move(int x, int y);
    ivec2 GetPosition() const { return _position; }
    void SetFlip(FlipEnum flip);
    FlipEnum GetFlip() const { return _flip; }
    void Scale(float scale_x, float scale_y);
    vec2 GetScale() const { return _scale; }
    void Show() override;
    void Hide() override;
    void EnableRestoreOriginFrame() { _restore_origin = true; }
    void DisableRestoreOriginFrame() { _restore_origin = false; }
    bool IsRestoreOriginFrame() const { return _restore_origin; }
    void SetKeyColor(int r, int g, int b);
    void SetColor(int r, int g, int b);
    void SetOpacity(int value);

    void AddFrame(Sprite* sprite, int time);
    void SetLoop(int loop) { _loop = loop; }
    int GetLoop() { return _loop; }
    void Play() { _is_playing = true; }
    void Pause() { _is_playing = false; }
    bool IsPlaying() { return _is_playing; }
    void Stop() {
        Pause();
        _cur_idx = 0;
        _timer = 0;
    }
    int Length() const { return _frames.size(); }
    void Draw() override;
    void Update() override;
    virtual ~Animation() = default;

 private:
    struct Frame {
        Sprite* sprite = nullptr;
        int time = 0;
    };

    vector<Frame> _frames;
    int _cur_idx = 0;
    int _timer = 0;
    bool _is_playing = false;
    bool _restore_origin = false;
    int _loop = 0;

    static forward_list<Animation> _instances;

    ivec2 _position;
    vec2 _scale = vec2(1, 1);
    FlipEnum _flip = FLIP_NONE;
    float _degree = 0;

    Animation() = default;
    void updateAnimation();
    void updateSprite();
};

#endif
