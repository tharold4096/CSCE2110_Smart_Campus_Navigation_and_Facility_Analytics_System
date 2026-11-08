// main.cpp
// Purpose: Milestone 1 menu and main program loop for the campus facilities project
// Author: Tobias

#include "CampusGraph.h"
#include "DepartmentTree.h"
#include "FacilityManager.h"
#include "FileUtils.h"

#include <cctype>
#include <iostream>
#include <string>

using namespace std;


const int MAX_MENU_OPTION = 9;


// Joins the data directory and a file name into one path
string build_path(const string& dir, const string& file)
{
    if (dir.empty())
    {
        return file;
    }
    if (dir[dir.length() - 1] == '/')
    {
        return dir + file;
    }
    return dir + "/" + file;
}

// Prints the menu
void print_menu()
{
    cout << "=======Campus Facilities Management System=======" << endl;
    cout << "1. View all facilities" << endl;
    cout << "2. Search facility by ID" << endl;
    cout << "3. View campus graph" << endl;
    cout << "4. Display graph counts and degrees" << endl;
    cout << "5. Find reachable buildings (BFS)" << endl;
    cout << "6. Add department" << endl;
    cout << "7. Search department" << endl;
    cout << "8. Display department hierarchy" << endl;
    cout << "9. Run preorder traversal" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter choice: ";
}

// reads menu choice, returning -1 for invalid input, 0 for exit, or 1-9 for valid options
int read_menu_choice()
{
    string line = "";
    if(!getline(cin, line))
    {
        return 0;
    }

    line = trim(line);
    if(line.empty() || line.length() > 2)
    {
        return -1;
    }
    //check for digit
    for (size_t i = 0; i < line.length(); ++i)
    {
        if (!isdigit(static_cast<unsigned char>(line[i])))
        {
            return -1;
        }
    }

    int choice = stoi(line);
    if(choice < 0 || choice > MAX_MENU_OPTION)
    {
        return -1;
    }
    return choice;
}

// Prompts for name and trims it
string read_name(const string& prompt)
{
    cout << prompt;
    string input;
    if(!getline(cin, input))
    {
        return "";
    }
    input = trim(input);

    return input;
}

// Option 2: prompts for an ID and runs the hash table lookup
void handle_search_facility(const FacilityManager& facilities)
{
    string id = read_name("Enter facility ID: ");
    if (id.empty())
    {
        cout << "Error: facility ID cannot be blank." << endl;
        return;
    }
    facilities.search_by_id(id);
}

// Option 5: prompts for a start building and runs BFS
void handle_bfs(const CampusGraph& graph)
{
    string start = read_name("Enter starting building: ");
    if (start.empty())
    {
        cout << "Error: building name cannot be blank." << endl;
        return;
    }
    //graph prints the unknown building message itself
    graph.bfsReachable(start);
}

// Option 6: adds a department, asking for a parent only when the tree already has a root
void handle_add_department(DepartmentTree& departments)
{
    string name = read_name("Enter department name: ");
    if (name.empty())
    {
        cout << "Error: department name cannot be blank." << endl;
        return;
    }
    if (departments.hasDepartment(name))
    {
        cout << "Error: department " << name << " already exists." << endl;
        return;
    }

    //first department becomes the root, so there is no parent to ask for
    if (departments.isEmpty())
    {
        departments.addDepartment(name, "NONE");
        cout << "Added " << name << " as the root department." << endl;
        return;
    }

    string parent = read_name("Enter parent department: ");
    if (parent.empty())
    {
        cout << "Error: parent department cannot be blank." << endl;
        return;
    }
    if (!departments.hasDepartment(parent))
    {
        cout << "Error: parent department " << parent << " not found." << endl;
        return;
    }

    if (departments.addDepartment(name, parent))
    {
        cout << "Added " << name << " under " << parent << "." << endl;
    }
    else
    {
        cout << "Error: could not add department " << name << "." << endl;
    }
}

// Option 7: prompts for a department name and shows its details
void handle_search_department(const DepartmentTree& departments)
{
    string name = read_name("Enter department name: ");
    if (name.empty())
    {
        cout << "Error: department name cannot be blank." << endl;
        return;
    }
    departments.searchDepartment(name);
}

int main(int argc, char* argv[])
{
    //data directory can be passed in, otherwise use data
    string data_dir = "data";
    if (argc > 1)
    {
        data_dir = argv[1];
    }

    CampusGraph graph;
    FacilityManager facilities;
    DepartmentTree departments;

    //buildings have to load before facilities, or every facility is an unknown building
    //a missing file just means that part is empty, so the return values are ignored
    graph.loadBuildings(build_path(data_dir, "buildings.txt"));
    graph.loadConnections(build_path(data_dir, "connections.txt"));
    facilities.load_facilities(build_path(data_dir, "facilities.txt"), graph);
    departments.loadFromFile(build_path(data_dir, "departments.txt"));
    cout << endl;

    int choice = -1;
    while (choice != 0)
    {
        print_menu();
        choice = read_menu_choice();

        switch (choice)
        {
            case 1:
                facilities.display_facilities();
                break;
            case 2:
                handle_search_facility(facilities);
                break;
            case 3:
                graph.displayGraph();
                break;
            case 4:
                graph.displayStatistics();
                break;
            case 5:
                handle_bfs(graph);
                break;
            case 6:
                handle_add_department(departments);
                break;
            case 7:
                handle_search_department(departments);
                break;
            case 8:
                departments.displayHierarchy();
                break;
            case 9:
                departments.preorderTraversal();
                break;
            case 0:
                cout << "Goodbye!" << endl;
                break;
            default:
                //read_menu_choice gives -1 for blank, text, or out of range input
                cout << "Invalid choice: enter a number from 0 to " << MAX_MENU_OPTION << endl;
                break;
        }
        cout << endl;
    }

    return 0;
}
