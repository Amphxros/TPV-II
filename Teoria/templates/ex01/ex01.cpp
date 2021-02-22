// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>

using namespace std;

template<typename T>
void printwice(T data) {
    cout << "Twice is: " << data * 2 << endl;
}

int main(int ac, char** av) {
    printwice(100);
    printwice(102.22);
    return 0;
}
