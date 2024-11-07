#include <iostream>
#include <string>

using namespace std;

class Exception {
    private:
        string message;
    public:
        Exception(string message){
            this->message = message;
        }
};