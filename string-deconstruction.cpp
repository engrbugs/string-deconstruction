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
#include <vector>
#include <cstdio>

#include <algorithm>

using std::cout; using std::cin;
using std::endl; using std::string;

namespace fs = std::filesystem;
using namespace std;

const char* end_sentence[2] = { ".", "”" };

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

int organize_quotes() {
    string line1 = "“He has taken on the role of puppet master, ” Demeter had chided. “Deciding fates as if he were one of the Moirai himself.He should be ashamed.”";
    string line2 = "The girl smiled and asked, “Vanilla latte?”";
    string line3 = "Persephone couldn’t deny she was curious. This was the thrill she’d been seeking—the adventure she craved. “Tell me.”";
    string line4 = "“Excuse me?” Persephone asked.";
    string line5 = "Persephone couldn’t deny she was curious. This was the thrill she’d been seeking—the adventure she craved. “Tell me.”";
    string line6 = "“You are mistaken.”";
    string line7 = "3062-“You left me desperate, swollen with need only for you,” he gritted out. For a moment, she thought he might leave her desperate in return, but then he said, “But I will be a generous lover.”";
    
    string line = line1;
    //count how many quotes the line have.
    std::string::difference_type n = std::count(line.begin(), line.end(), '“');

    vector<string> entry;
    size_t start = 0;
    for (int i = 0; i <= n - 1; i++) {
        cout << i+1 << endl;

        start = line.find('“', start);
        size_t end = line.find('”', start);
        size_t period = line.find('.', end);
        if (start == 0) {
            entry.push_back(line.substr(start, period + 1));
        }
        else if (period == -1) {
            //find the period in reverse
            cout << -1 << endl;
            size_t period = line.rfind('.', start);
            size_t end_quote = line.rfind('”', start);
            cout << period << ' ' << end_quote << endl;
        }

        //replace(entry.begin(), entry.end(), entry[entry.size() - 1], string{ "Bill" });

        /*size_t end = line.find('”', start);


        size_t prior_period = line.rfind('h', start);
        
        size_t period2 = line.find('.', period+1);
        size_t len = line.length();

        cout << prior_period << endl;
        cout << ((period == -1) ? "lll" : "A") << endl;*/

        //cout << loc << " " << end << period << period2 << len << endl;
 
        start++;
    }
    for (vector<string>::iterator t = entry.begin(); t != entry.end(); ++t)
    {
        cout << *t << endl;
    }
    return 0;

    //ifstream file_source(fs::current_path().string() + "\\quotes.txt");
    //if (file_source.is_open())
    //{
    //    string line;
    //    while (getline(file_source, line))
    //    {
    //        std::string::difference_type n = std::count(line.begin(), line.end(), '“');
    //        if (n > 2) cout << line << "\n";
    //        // https://cplusplus.com/reference/string/string/find/
    //    }
    //}
    //return 0;
}

int main()
{
    // 1. // put_numbers();
    // 2. filter_quotes();
    organize_quotes();
    cout << "Current path is " << fs::current_path() << '\n'; // (1)
}
