// string-deconstruction.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <Windows.h>
#include "resource.h"
#include <sstream>
#include <iomanip>

using std::cout; using std::cin;
using std::endl; using std::string;

namespace fs = std::filesystem;
using namespace std;

int put_numbers() {
    string line;
    cout << fs::current_path().string() + "\\clean.txt\n";
    ifstream file_source(fs::current_path().string() + "\\clean.txt");
    if (file_source.is_open())
    {
        ofstream dest(fs::current_path().string() + "\\numbered.txt");
        if (dest.is_open())
        {
            int i = 0;
            while (getline(file_source, line))
            {
                i++;
                cout << line << "\n";
                dest << std::setw(4) << std::setfill('0') << i << "-" << line << "\n";
            }
            file_source.close();
            dest.close();
        }
        else cout << "Unable to destination file\n";
    }
    else cout << "Unable to open source file\n";

    return 0;
}

int filter_quotes() {
    ifstream file_source(fs::current_path().string() + "\\numbered.txt");
    if (file_source.is_open())
    {
        string line;
        ofstream file_quotes(fs::current_path().string() + "\\quotes.txt");
        ofstream file_woquotes(fs::current_path().string() + "\\woquotes.txt");
        while (getline(file_source, line))
        {
            if (line.find("”") != std::string::npos)
            {
                file_quotes << line << "\n";
            }
            else
            {
                file_woquotes << line << "\n";
            }

        }
        file_source.close();
        file_quotes.close();
        file_woquotes.close();
    }
    return 0;
}

int main()
{
    // 1. // put_numbers();
    filter_quotes(); // 2.
    cout << "Current path is " << fs::current_path() << '\n'; // (1)
}
