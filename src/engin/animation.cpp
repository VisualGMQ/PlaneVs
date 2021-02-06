#include "engin/animation.hpp"

forward_list<Animation> Animation::_instances;

Animation* Animation::Create() {
    Animation animation;
    _instances.push_front(animation);
    return &_instances.front();
}

void Animation::AddFrame(Sprite* sprite, int time) {
    if (!sprite)
        Logw("Animation::AddFrame", "Animation::AddFrame sprite == nullptr");
    if (time < 0)
        Logw("Animation::AddFrame", "Animation::AddFrame time must >= 0");
    Frame frame;
    frame.sprite = sprite->Copy();
    frame.time = time;
    _frames.push_back(frame);
}

void Animation::MoveTo(int x, int y) {
    for (int i = 0; i < _frames.size(); i++) {
        if (_frames.at(i).sprite)
            _frames.at(i).sprite->MoveTo(x, y);
    }
    ISprite::MoveTo(x, y);
}

void Animation::MoveTo(ivec2 pos) {
    MoveTo(pos.x, pos.y);
}

void Animation::MoveBy(int offset_x, int offset_y) {
    MoveTo(GetPosition().x+offset_x, GetPosition().y+offset_y);
}

void Animation::MoveBy(ivec2 offset) {
    MoveBy(offset.x, offset.y);
}

void Animation::RotateTo(float degree) {
    for (Frame& frame : _frames) {
        if (frame.sprite)
            frame.sprite->RotateTo(degree);
    }
    Rotatable::RotateTo(degree);
}

void Animation::RotateBy(float delta) {
    RotateTo(GetRotation()+delta);
}

void Animation::SetFlip(FlipEnum flip) {
    for (Frame& frame : _frames) {
        if (frame.sprite)
          frame.sprite->SetFlip(flip);
    }
    _flip = flip;
}

void Animation::Scale(float scale_x, float scale_y) {
    Assertm(scale_x > 0, "Animation::Scale", "Animation::Scale scale_x must > 0");
    Assertm(scale_y > 0, "Animation::Scale", "Animation::Scale scale_y must > 0");
    for (Frame& frame : _frames) {
        if (frame.sprite) {
            isize size = frame.sprite->GetOriginSize();
            size.w *= scale_x;
            size.h *= scale_y;
            frame.sprite->ResizeTo(size);
        }
    }
    _scale.x = scale_x;
    _scale.y = scale_y;
}

void Animation::SetKeyColor(int r, int g, int b) {
    for (Frame& frame : _frames) {
        if (frame.sprite)
            frame.sprite->SetKeyColor(r, g, b);
    }
}

void Animation::SetColor(int r, int g, int b) {
    for (Frame& frame : _frames) {
        if (frame.sprite)
            frame.sprite->SetColor(r, g, b);
    }
}

void Animation::SetOpacity(int value) {
    for (Frame& frame : _frames) {
        if (frame.sprite)
            frame.sprite->SetOpacity(value);
    }
}

void Animation::Show() {
    for (int i = 0; i < _frames.size(); i++) {
        if (_frames.at(i).sprite)
            _frames.at(i).sprite->Show();
    }
    Visiable::Show();
}

void Animation::Hide() {
    for (Frame& frame : _frames)
        if (frame.sprite)
            frame.sprite->Hide();
    Visiable::Hide();
}

void Animation::draw() {
    if (_cur_idx >= 0 && _cur_idx < _frames.size())
        if (_frames.at(_cur_idx).sprite)
            _frames.at(_cur_idx).sprite->Draw();
}

void Animation::update() {
    updateAnimation();
    updateSprite();
}

void Animation::updateAnimation() {
    if (IsPlaying()) {
        if (_timer < _frames.at(_cur_idx).time) {
            _timer++;
        } else {
            _timer = 0;
            _cur_idx++;
        }
    }
    if (_cur_idx >= Length()) {
        if (GetLoop() == -1 ||GetLoop() > 0) {
            if (GetLoop() > 0) {
                _loop--;
            }
            Stop();
            Play();
        } else {
            Stop();
            if (!IsRestoreOriginFrame()) {
                _cur_idx = _frames.size()-1;
            }
        }
    } 
}

void Animation::updateSprite() {
    if (_cur_idx >= 0 && _cur_idx < _frames.size())
        if (_frames.at(_cur_idx).sprite)
            _frames.at(_cur_idx).sprite->Update();
}

Animation* Animation::Copy() {
    Animation* ani = Animation::Create();
    *ani = *this;
    ani->_frames.clear();
    for (int i = 0; i < this->_frames.size(); i++) {
        ani->AddFrame(this->_frames[i].sprite, this->_frames[i].time);
    }
}

ISprite* Animation::CopyISprite() {

}
