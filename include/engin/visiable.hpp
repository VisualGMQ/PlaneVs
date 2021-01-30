#ifndef VISIABLE_HPP
#define VISIABLE_HPP

class Visiable {
 public:
    virtual void Show() { _is_show = true; }
    virtual void Hide() { _is_show = false; }
    virtual bool IsShow() { return _is_show; }
    virtual ~Visiable() = default;

 private:
    bool _is_show = false;
};

#endif

