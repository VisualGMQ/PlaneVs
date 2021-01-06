#ifndef IMG2FILE_HPP
#define IMG2FILE_HPP
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include "header.hpp"
#include "SDL.h"
#include "SDL_image.h"
using std::ofstream;
using std::vector;
using std::string;
using std::numeric_limits;
using std::endl;

void Img2File(string infofile_filename, string imgfile_filename, const vector<TextureInfo>& texture_infos, SDL_Color keycolor);

#endif

