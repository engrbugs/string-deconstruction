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

std::string tail(std::string const& source, size_t const length) {
    if (length >= source.size()) { return source; }
    return source.substr(source.size() - length);
}

int organize_quotes() {
    string line1 = "“He has taken on the role of puppet master, ” Demeter had chided. “Deciding fates as if he were one of the Moirai himself.He should be ashamed.”";
    string line2 = "The girl smiled and asked, “Vanilla latte?”";
    string line3 = "Persephone couldn’t deny she was curious. This was the thrill she’d been seeking—the adventure she craved. “Tell me.”";
    string line4 = "“Excuse me?” Persephone asked.";
    string line5 = "“I get that,” Lexa said. “Man, your mother is a bitch,” she said and then hunkered down as if she expected lightning to strike her. “Will she kill me for saying that?”";
    string line6 = "“You are mistaken.”";
    string line7 = "“You left me desperate, swollen with need only for you,” he gritted out. For a moment, she thought he might leave her desperate in return, but then he said, “But I will be a generous lover.”";
    
    //count how many quotes the line have.
    

    string line;
    ifstream file_source(fs::current_path().string() + "\\quotes.txt");
    if (file_source.is_open())
    {

        while (getline(file_source, line))
        {
            string number = line.substr(0, 5);
            line = tail(line, line.length() - 5); // remove the '####-'
            //line = "“Not at all.” Adonis smiled at her. “Ready?”";
            std::string::difference_type n = std::count(line.begin(), line.end(), '“');
            vector<string> entry;
            size_t start = 0;
            int m = 0;
            for (int i = 0; i <= n - 1; i++) {
                // look for start and end quote, then period after the it.
                start = line.find('“', start);
                size_t end = line.find('”', start);
                size_t period = line.find('.', end);
                size_t len = line.length();

                if (start == 0 && end + 1 != len) {
                    entry.push_back(line.substr(start, period + 1));
                }
                else if (start == 0 && end + 1 == len) {
                    entry.push_back(line);
                }
                // no period onward
                else if (period == -1) {
                    //find the period in reverse
                    size_t rperiod = line.rfind('.', start - 3);
                    size_t end_quote = line.rfind('”', start);
                    // if no period also backward
                    if (entry.size() != 0 && rperiod < end_quote) {
                        replace(entry.begin(), entry.end(), entry[entry.size() - 1], entry[entry.size() - 1] + ' ' + line.substr(start, end + 1));
                    }
                    else if (entry.size() != 0 && rperiod < end_quote || 
                        rperiod == -1 && end_quote != -1) {
                        // merge the last entry with this quote.
                        replace(entry.begin(), entry.end(), entry[entry.size() - 1], entry[entry.size() - 1] + ' ' + line.substr(start, end + 1));

                    }
                    else if (rperiod == -1 && end_quote == -1) {
                        entry.push_back(line);
                    }
                    else {
                        entry.push_back(line.substr(rperiod + 2, end + 1));
                    }
                }
                start++;
            }
            for (vector<string>::iterator t = entry.begin(); t != entry.end(); ++t)
            {
                cout << number << *t << endl;
            }
        }
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
