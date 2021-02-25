#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

class Controller {
 public:
    bool IsWorking() const { return _is_working; }
    void TrunOn() { _is_working = true; }
    void TrunOff() { _is_working = false; }

    void Control();
    virtual ~Controller() = default;

 protected:
    virtual void Up() = 0;
    virtual void Down() = 0;
    virtual void Left() = 0;
    virtual void Right() = 0;
    virtual void Fire() = 0;
    virtual void Bomb() = 0;
    virtual void Blast() = 0;

 private:
    bool _is_working = false;
};

#endif

