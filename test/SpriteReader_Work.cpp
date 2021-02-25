#ifdef _MSC_VER
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#pragma comment(lib, "SDL2_mixer.lib")
#endif

#include "base/image_sheet.hpp"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    ImageSheet sheet = ImageSheet::ReadFromJson("./test_resources/test_pngs/icons.json");
    printf("in sheet %s:\n", sheet.GetImageFilename().c_str());
    for (auto& image : sheet.GetImages()) {
        printf("\t<name, position, size, origin_size> = <%s, (%d, %d), (%d, %d), (%d, %d)>\n",
                image.GetName().c_str(),
                static_cast<int>(image.GetPosition().x), static_cast<int>(image.GetPosition().y),
                static_cast<int>(image.GetSize().w), static_cast<int>(image.GetSize().h),
                static_cast<int>(image.GetOriginSize().w), static_cast<int>(image.GetOriginSize().h));
    }
    return 0;
}
