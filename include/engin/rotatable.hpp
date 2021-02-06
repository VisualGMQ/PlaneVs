#ifndef ROTATABLE_HPP
#define ROTATABLE_HPP

class Rotatable {
 public:
    virtual void RotateTo(float degree) { _degree = degree; }
    virtual void RotateBy(float delta) { _degree += delta; }
    virtual float GetRotation() const { return _degree; }
    ~Rotatable() = default;

 private:
    float _degree = 0;
};

#endif

