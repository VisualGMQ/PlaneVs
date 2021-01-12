#ifndef VALIDABLE_HPP
#define VALIDABLE_HPP

class Validable {
 public:
     bool IsValid() { return _valid; }
 protected:
     void valid() { _valid = true; }
     void invalid() { _valid = false; }
 private:
     bool _valid = false;
};

#endif

