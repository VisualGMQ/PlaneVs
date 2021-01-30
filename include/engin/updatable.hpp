#ifndef UPDATABLE_HPP
#define UPDATABLE_HPP

class Updatable {
 public:
     virtual void Update() = 0;
     virtual ~Updatable() = default;
};

#endif

