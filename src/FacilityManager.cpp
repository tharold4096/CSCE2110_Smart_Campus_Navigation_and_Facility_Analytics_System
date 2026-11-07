// FacilityManager.cpp
// Purpose: To load, search, and display the facilities
// Author: Tobias

#include "FacilityManager.h"
#include "FileUtils.h"

#include <cctype>
#include <fstream>
#include <iostream>

using namespace std;

bool FacilityManager::is_valid_facility_id(const string& id) const
{
    // Trimming and to_upper completed, so we can check only format
    if (id.size() != 4)
    {
        return false;
    }

    if (id[0] != 'F')
    {
        return false;
    }

    for (size_t i = 1; i < id.size(); ++i)
    {
        if (!isdigit(static_cast<unsigned char>(id[i])))
        {
            return false;
        }
    }

    return true;
}

string FacilityManager::find_building(const string& name, const vector<string>& buildings) const
{
    // looping over buildings, compare each building with name.
    for(const string& building : buildings)
    {
        if (equals_ignore_case(building, name))
        {
            return building;
        }
    }

    return "";
}

bool FacilityManager::load_facilities(const string& filename, const vector<string>& buildings)
{
    //open the file
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl;
        print_load_summary(filename, 0, 0);
        return false;
    }

    //counters for the lines
    int line_number = 0;
    int accepted = 0;
    int rejected = 0;

    string line;
    vector<string> fields;

    //looping over the lines of the file
    while (getline(file, line))
    {
        line_number++;
        //if the line is empty or a comment skip it
        if (is_skippable_line(line))
        {
            continue;
        }

        fields = split_fields(line);
        //check the number of fields a line has
        if (fields.size() != 4)
        {
            print_load_warning(filename, line_number, "expected 4 fields, found " + to_string(fields.size()));
            rejected++;
            continue;
        }
        //check if any of the fields are empty
        if (fields[0].empty() || fields[1].empty() || fields[2].empty() || fields[3].empty())
        {
            if (fields[0].empty())
            {
                print_load_warning(filename, line_number, "empty ID field");
            }
            else if (fields[1].empty())
            {
                print_load_warning(filename, line_number, "empty name field");
            }
            else if (fields[2].empty())
            {
                print_load_warning(filename, line_number, "empty building field");
            }
            else
            {
                print_load_warning(filename, line_number, "empty category field");
            }
            rejected++;
            continue;
        }

        string id = to_upper(fields[0]);
        if (!is_valid_facility_id(id))
        {
            print_load_warning(filename, line_number, "invalid ID " + id + ": must be F followed by exactly three digits");
            rejected++;
            continue;
        }

        string building = fields[2];
        string matched_building = find_building(building, buildings);
        if (matched_building.empty())
        {
            print_load_warning(filename, line_number, "unknown building " + building);
            rejected++;
            continue;
        }

        if (table.contains(id))
        {
            print_load_warning(filename, line_number, "duplicate facility ID " + id);
            rejected++;
            continue;
        }

        Facility facility(id, fields[1], matched_building, fields[3]);
        table.insert(facility);
        facilities.push_back(facility);
        accepted++;
    }

    print_load_summary(filename, accepted, rejected);
    cout << "(hash capacity " << table.get_capacity() << ", entries " << table.get_size() << ", collisions " << table.get_collisions() << ")" << endl;
    return true;
}

// Displays all facilities
void FacilityManager::display_facilities() const
{
    if (facilities.empty())
    {
        cout << "No facilities loaded." << endl;
        return;
    }
    //printing
    for (const Facility& facility : facilities)
    {
        facility.print();
    }

    cout << "Total facilities: " << facilities.size() << endl;
}

//Searches through the facilities by ID
void FacilityManager::search_by_id(const string& input) const
{
    string id = to_upper(trim(input));

    if (!is_valid_facility_id(id))
    {
        cout << "Invalid format: an ID is F followed by exactly three digits" << endl;
        return;
    }

    const Facility* facility = table.find(id);
    if (facility == nullptr)
    {
        cout << "Not found: no facility with ID " << id << endl;
        return;
    }

    cout << "Found: ";
    facility->print();
}

const vector<Facility>& FacilityManager::get_all_facilities() const
{
    return facilities;
}
