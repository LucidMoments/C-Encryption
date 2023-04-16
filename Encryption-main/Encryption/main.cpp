#include <iostream>
#include "Encryption.h"
std::vector<int> readFile(char* filename)
{
    std::ifstream file(filename);
    std::vector<int> list;

    int num;

    while (!file.eof())
    {
        file >> num;
        list.push_back(num);
    }

    return list;
}

std::unordered_map<int, char> readKey(char* filename)
{
    FILE* file = fopen(filename, "r");
    std::unordered_map<int, char> keymap;

    char ch;
    int x = 2;
    while (!feof(file))
    {
        ch = getc(file);
        keymap[x] = ch;
        x++;
    }
    return keymap;
}
int main()
{
    char key[] = "key.txt";
    char file[] = "encrypted_text.txt";
    std::unordered_map<int, char> keyMap = readKey(key);
    std::vector<int> encrypted_data = readFile(file);
    Decryption(10019, 1949, encrypted_data, keyMap);
    return 0;
}