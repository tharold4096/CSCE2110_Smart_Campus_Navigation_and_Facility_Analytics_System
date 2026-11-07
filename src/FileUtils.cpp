// FileUtils.cpp
// Purpose: Parsing data file assisted class
// Author: Tobias

#include "FileUtils.h"

#include <cctype>
#include <iostream>

using namespace std;

static bool is_trim_char(char c)
{
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

string trim(const string& text)
{
    size_t start = 0;
    size_t end = text.size();

    while (start < end && is_trim_char(text[start]))
    {
        start++;
    }
    while (end > start && is_trim_char(text[end - 1]))
    {
        end--;
    }
    return text.substr(start, end - start);
}

vector<string> split_fields(const string& line)
{
    vector<string> fields;
    string current;

    for (char c : line)
    {
        if (c == '|')
        {
            fields.push_back(trim(current));
            current.clear();
        }
        else
        {
            current += c;
        }
    }
    fields.push_back(trim(current));
    return fields;
}

string to_upper(const string& text)
{
    string result = text;
    for (char& c : result)
    {
        c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
    }
    return result;
}

string to_lower(const string& text)
{
    string result = text;
    for (char& c : result)
    {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    return result;
}

bool equals_ignore_case(const string& a, const string& b)
{
    return to_lower(a) == to_lower(b);
}

bool is_skippable_line(const string& line)
{
    string trimmed = trim(line);
    return trimmed.empty() || trimmed[0] == '#';
}

void print_load_warning(const string& filename, int line_number, const string& reason)
{
    cout << "Warning: " << filename << " line " << line_number << ": " << reason << endl;
}

void print_load_summary(const string& filename, int accepted, int rejected)
{
    cout << filename << ": " << accepted << " accepted, " << rejected << " rejected" << endl;
}
