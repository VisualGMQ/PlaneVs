#ifndef MUSIC_REPO_HPP
#define MUSIC_REPO_HPP
#include <string>
#include <map>
#include <list>
#include <vector>

#include "base/destroyable.hpp"
#include "base/tools.hpp"
#include "engin/music.hpp"
using std::list;
using std::map;
using std::string;

class MusicRepo final: public Destroyable {
 public:
    static MusicRepo* Create();

    Music* LoadMusic(string filename);
    Music* Get(string name);
    void Destroy() override;
    ~MusicRepo();
 private:
    map<string, Music*> _musics; 

    static list<MusicRepo> _instances;
};

#endif

