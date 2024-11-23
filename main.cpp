#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class FileHandler {
public:
    virtual void Display(const char* path) {
        cout << "Base class: cant define specific behavior" << endl;
    }

    virtual ~FileHandler() = default;
};

class ASCIIFileHandler : public FileHandler {
public:
    void Display(const char* path) override {
        ifstream file(path);
        if (!file.is_open()) {
            cerr << "Cant open file: " << path << endl;
            return;
        }

        char ch;
        cout << "ASCII codes of the file contents:" << endl;
        while (file.get(ch)) {
            cout << static_cast<int>(ch) << " ";
        }
        cout << endl;
        file.close();
    }
};

class BinaryFileHandler : public FileHandler {
public:
    void Display(const char* path) override {
        ifstream file(path, ios::binary);
        if (!file.is_open()) {
            cerr << "Cant open file: " << path << endl;
            return;
        }

        char ch;
        cout << "Binary representation of the file contents:" << endl;
        while (file.get(ch)) {
            for (int i = 7; i >= 0; --i) {
                cout << ((ch >> i) & 1);
            }
            cout << " ";
        }
        cout << endl;
        file.close();
    }
};

int main() {
    FileHandler* handler;

    handler = new ASCIIFileHandler();
    handler->Display("example.txt");
    delete handler;

    handler = new BinaryFileHandler();
    handler->Display("example.txt");
    delete handler;

    return 0;
}
