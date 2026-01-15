#include <iostream>
// #include "log_duration.h"
#include <cassert>
#include <filesystem>
#include <map>
#include <string>
#include <vector>
using namespace std;

int main()
{
    map<char, vector<uint8_t>> char_to_array{
        {'A', {}}, {'B', {}}, {'C', {}}, {'D', {}}, {'E', {}}, {'F', {}}, {'G', {}}, {'H', {}}, {'I', {}},
        {'J', {}}, {'K', {}}, {'L', {}}, {'M', {}}, {'N', {}}, {'O', {}}, {'P', {}}, {'Q', {}}, {'R', {}},
        {'S', {}}, {'T', {}}, {'U', {}}, {'V', {}}, {'W', {}}, {'X', {}}, {'Y', {}}, {'Z', {}}, {'0', {}},
        {'1', {}}, {'2', {}}, {'3', {}}, {'4', {}}, {'5', {}}, {'6', {}}, {'7', {}}, {'8', {}}, {'9', {}},
    };
    unsigned char_width = 6, char_height = 8;
    for (auto &[ch, arr] : char_to_array)
    {
        std::cout << "Enter signature for character " << ch << std::endl;
        arr.resize(char_width, 0);
        std::string buffer;
        for (unsigned row = 0; row < char_height; ++row)
        {
            cin >> buffer;
            for (unsigned column = 0; column < char_width; column++)
            {
                if (buffer.at(column) != '0')
                {
                    arr[column] |= 0x01 << row;
                }
                else
                {
                    arr[column] &= ~(0x01 << row);
                }
            }
        }
        bool is_first = true;
        cout << "{\'" << ch << "\', {";
        for (unsigned col = 0; col < char_width; col++)
        {
            if (!is_first && col != 7)
            {
                cout << ", ";
            }
            cout << std::hex << std::uppercase << static_cast<unsigned>(arr.at(col));
            is_first = false;
        }
        cout << "}},";
        cout << std::endl;
    }
}
