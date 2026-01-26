#include <iostream>
// #include "log_duration.h"
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void ReadStream(std::istream &is = std::cin, std::ostream &os = std::cout)
{
    bool is_cin = &is == &std::cin;
    unsigned char_width = 6, char_height = 8;
    map<char, vector<uint8_t>> char_to_array{
        {' ', {}}, {'!', {}}, {'\"', {}}, {'#', {}}, {'$', {}}, {'%', {}}, {'&', {}}, {'\'', {}}, {'(', {}}, {')', {}},
        {'*', {}}, {'+', {}}, {',', {}},  {'-', {}}, {'.', {}}, {'/', {}}, {'0', {}}, {'1', {}},  {'2', {}}, {'3', {}},
        {'4', {}}, {'5', {}}, {'6', {}},  {'7', {}}, {'8', {}}, {'9', {}}, {':', {}}, {';', {}},  {'<', {}}, {'=', {}},
        {'>', {}}, {'?', {}}, {'@', {}},  {'A', {}}, {'B', {}}, {'C', {}}, {'D', {}}, {'E', {}},  {'F', {}}, {'G', {}},
        {'H', {}}, {'I', {}}, {'J', {}},  {'K', {}}, {'L', {}}, {'M', {}}, {'N', {}}, {'O', {}},  {'P', {}}, {'Q', {}},
        {'R', {}}, {'S', {}}, {'T', {}},  {'U', {}}, {'V', {}}, {'W', {}}, {'X', {}}, {'Y', {}},  {'Z', {}}, {'a', {}},
        {'b', {}}, {'c', {}}, {'d', {}},  {'e', {}}, {'f', {}}, {'g', {}}, {'h', {}}, {'i', {}},  {'j', {}}, {'k', {}},
        {'l', {}}, {'m', {}}, {'n', {}},  {'o', {}}, {'p', {}}, {'q', {}}, {'r', {}}, {'s', {}},  {'t', {}}, {'u', {}},
        {'v', {}}, {'w', {}}, {'x', {}},  {'y', {}}, {'z', {}}};
    os << "std::map<char, std::vector<uint8_t>> font = {" << std::endl;
    for (auto &[ch, arr] : char_to_array)
    {
        if (ch == 'A')
        {
            std::cout << "capturing.." << std::endl;
        }
        if (!is)
            break;
        if (is_cin)
            std::cout << "Enter signature for character " << ch << std::endl;
        arr.resize(char_width, 0);
        std::string buffer;
        for (unsigned row = 0; row < char_height; ++row)
        {

            is >> buffer;
            buffer.resize(char_width, 0);
            for (unsigned column = 0; column < char_width; column++)
            {
                if (buffer.at(column) != '0' && buffer.at(column))
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
        os << "{\'" << ch << "\', {";
        for (unsigned col = 0; col < char_width; col++)
        {
            if (!is_first && col != 7)
            {
                os << ", ";
            }
            os << "0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
               << static_cast<unsigned>(arr.at(col));
            is_first = false;
        }
        os << "}}";
        if (ch != 'z')
            os << ",";
        os << std::endl;
    }
    os << "};" << std::endl;
}

void Test()
{
    std::cout << "Testing.." << std::endl;
    std::stringstream iss;
    iss << "000000" << std::endl;
    iss << "111100" << std::endl;
    iss << "100010" << std::endl;
    iss << "100010" << std::endl;
    iss << "101100" << std::endl;
    iss << "101000" << std::endl;
    iss << "100100" << std::endl;
    iss << "100010" << std::endl;
    std::stringstream oss;
    ReadStream(iss, oss);
    std::cout << oss.str();
}

int main()
{
    Test();
    std::string user_response;
    std::cout << "this program parses binary font into map" << std::endl
              << "correct example for implementation of char 0:" << std::endl
              << "000000" << std::endl
              << "011100" << std::endl
              << "100010" << std::endl
              << "100010" << std::endl
              << "100010" << std::endl
              << "100010" << std::endl
              << "100010" << std::endl
              << "011100" << std::endl
              << std::endl
              << "just make a file with such symbols or enter everything manually." << std::endl;
    std::cout << "do you want to use binary file? yes|no : ";
    std::cin >> user_response;
    std::cout << std::endl;
    std::ifstream fin;
    std::ofstream fout;

    if (user_response == "yes")
    {
        std::cout << "mode : automated." << std::endl;
        std::cout << "please enter relative address to this file : " << std::endl;
        cin >> user_response;
        if (filesystem::exists(user_response))
        {
            std::cout << "opening file... ";
            fin.open(user_response);
            if (fin.is_open())
            {
                std::cout << "open" << std::endl;
            }
            else
            {
                std::cout << "error. Aborting." << std::endl;
                return 0;
            }
        }
        else
        {
            std::cout << "incorrect path. aborting..." << std::endl;
            return 0;
        }
    }
    else
    {
        std::cout << "mode : manual." << std::endl;
    }
    std::cout << "do you want to output it in a file? yes|no : ";
    cin >> user_response;
    std::cout << std::endl;
    if (user_response == "yes")
    {
        std::cout << "please enter the filename and this [file].txt will be the output near this executable."
                  << std::endl;
        cin >> user_response;
        user_response.append(".txt");
        if (filesystem::exists(user_response))
        {
            std::cout << "file already exists. aborting..." << std::endl;
            return 0;
        }
        else
        {
            std::cout << "opening file... ";
            fout.open(user_response);
            if (fout.is_open())
            {
                std::cout << "file is open." << std::endl;
            }
            else
            {
                std::cout << "error. Aborting..." << std::endl;
                if (fin.is_open())
                {
                    fin.close();
                }
                return 0;
            }
        }
    }

    if (fin.is_open())
    {
        if (fout.is_open())
        {
            ReadStream(fin, fout);
        }
        else
        {
            ReadStream(fin);
        }
    }
    else
    {
        if (fout.is_open())
        {
            ReadStream(std::cin, fout);
        }
        else
        {
            ReadStream();
        }
    }
    if (fin.is_open())
        fin.close();
    if (fout.is_open())
        fout.close();
    std::cout << "parsing done. closing..." << std::endl;
    return 0;
}
