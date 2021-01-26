#ifndef ID_GENERATOR_HPP
#define ID_GENERATOR_HPP
#include "base/log.hpp"

using IdType = unsigned int;

enum PresetResourcesId : IdType {
    ID_ANY = 0,
    SYSTEM_GFXBUF_ID,
    TEXTURE_PROGRAM_ID,
    GEOM_PROGRAM_ID,
    FIRST_ID
};

class HasID {
 public:
     HasID(IdType id) {
         if (id <= FIRST_ID) {
             Log("id duplicated with preset id");
         }
         _id = id;
     }
     IdType GetId() const {
         return _id;
     }
 private:
     IdType _id;
};

#endif

