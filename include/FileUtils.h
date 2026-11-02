// FileUtils.h
// Reading data files and o

#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>
#include <vector>

using namespace std;

//Trims the string
string trim(const string& text);

// splits a line along |
vector<string> split_fields(const string& line);

// Uppercase or lowercase only
string to_upper(const string& text);
string to_lower(const string& text);

// case-insensitive comparison of two strings
bool equals_ignore_case(const string& a, const string& b);

// true if the line is blank or its first non-whitespace character is '#'
bool is_skippable_line(const string& line);

// prints "Warning: <file> line <n>: <reason>"
void print_load_warning(const string& filename, int line_number, const string& reason);

// prints "<file>: <accepted> accepted, <rejected> rejected"
void print_load_summary(const string& filename, int accepted, int rejected);

#endif // FILEUTILS_H
