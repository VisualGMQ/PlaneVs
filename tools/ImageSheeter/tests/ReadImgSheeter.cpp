#include "read_imgsheet.hpp"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    cout << "filename:";
    string filename;
    cin >> filename;
    SheeterInfo info = ReadImageSheeter(filename);
    cout << "image filename:" << info.img_filename << endl;
    for (auto& i : info.img_infoes) {
        cout << "<name, x, y, w, h> = <" << i.name << ", " << i.x << ", " << i.y << ", " << i.w << ", " << i.h << ">" << endl;
    }
}
