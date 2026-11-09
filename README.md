# CSCE2110_Smart_Campus_Navigation_and_Facility_Analytics_System

CSCE 2110 Smart Campus Navigation System

Description
This project is a C++ program designed to manage campus information. Users can search for facilities as well as explore building connections and organize university departments through a menu-based system.

Features
View and search facilities
Display campus buildings and connections
Find reachable buildings using BFS
Add and search departments
Display department hierarchy

How to Compile
Windows (Developer PowerShell):
cl /EHsc /std:c++17 /Iinclude src\*.cpp /Fe:campus_m1.exe

Linux (UNT CELL):
g++ -std=c++17 -Iinclude src/*.cpp -o campus_m1

How to Run
Windows:
.\campus_m1.exe
Linux:
./campus_m1

The program loads the files from the data folder and displays a menu.
Team Members
Tobias Harold
Adrian Ochoa
Roshan Sharma
See contributions.txt and test_results.txt for more details.
