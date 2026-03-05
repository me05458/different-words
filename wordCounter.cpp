#include <iostream>
#include "String.h"
using namespace std;

int main() {
    String s = String("cat", 3);
    cout <<s.charAt(0)<<"|"<<s.charAt(1)<<"|"<<s.charAt(2)<<"|"<< endl;
    return 0;
}
