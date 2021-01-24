#ifndef ID_GENERATOR_HPP
#define ID_GENERATOR_HPP

using IdType = unsigned int;

enum PresetResourcesId : IdType {
    INVALID_ID = 0,
    SYSTEM_GFXBUF_ID,
    TEXTURE_PROGRAM_ID,
    GEOM_PROGRAM_ID,
    FIRST_ID
};

class HasID {
 public:
     HasID(IdType id) {
         _id = id;
     }
     IdType GetId() const {
         return _id;
     }
 private:
     IdType _id;
};

inline IdType GenerateId() {
    static IdType _cur_id = FIRST_ID;
    return _cur_id++;
}

#endif

