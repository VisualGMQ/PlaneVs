#include <iostream>
using namespace std;

#define STRINGERMACRO( x ) #x
#define GenID() (*(int*)(__FILE__)+__LINE__)

int main(int argc, char** argv){
    cout << GenID() << endl;
    cout << GenID() << endl;
    cout << GenID() << endl;
    return 0;
}

