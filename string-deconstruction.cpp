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
            if (line.find("�") != std::string::npos || 
                line.find("�") != std::string::npos )
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

    cout << " Hello World!\n";
    // 1. // put_numbers();
    filter_quotes(); // 2.
    cout << "Current path is " << fs::current_path() << '\n'; // (1)

}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
