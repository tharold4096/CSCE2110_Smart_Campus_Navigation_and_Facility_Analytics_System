// FacilityManager.cpp
// Purpose: To load, search, and display the facilities
// Author: Tobias

#include "FacilityManager.h"
#include "FileUtils.h"

#include <cctype>
#include <fstream>
#include <iomanip>
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

bool FacilityManager::load_facilities(const string& filename, const CampusGraph& graph)
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
        //graph returns its stored spelling, or empty if the building is unknown
        string matched_building = graph.getBuildingName(building);
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

//Searches through the facilities by complete name
void FacilityManager::search_by_name(const string& input) const
{
    string name = trim(input);
    int matches = 0;

    //simple scan so matches print in file order
    for (const Facility& facility : facilities)
    {
        if (equals_ignore_case(facility.get_facility_name(), name))
        {
            facility.print();
            matches++;
        }
    }

    if (matches == 0)
    {
        cout << "No facility named " << name << endl;
    }
    cout << "Matches: " << matches << endl;
}

//Searches through the facilities by complete category
void FacilityManager::search_by_category(const string& input) const
{
    string category = trim(input);
    int matches = 0;

    for (const Facility& facility : facilities)
    {
        if (equals_ignore_case(facility.get_category(), category))
        {
            facility.print();
            matches++;
        }
    }

    if (matches == 0)
    {
        cout << "No facilities in category " << category << endl;
    }
    cout << "Matches: " << matches << endl;
}

//Displays the count and percentage of each category
void FacilityManager::category_report() const
{
    if (facilities.empty())
    {
        cout << "No facilities available." << endl;
        cout << "Total: 0" << endl;
        return;
    }

    //parallel vectors keep categories in the order they were first accepted
    vector<string> categories;
    vector<int> counts;

    for (const Facility& facility : facilities)
    {
        bool found = false;
        for (size_t i = 0; i < categories.size(); ++i)
        {
            //grouping ignores case, but keeps the first spelling
            if (equals_ignore_case(categories[i], facility.get_category()))
            {
                counts[i]++;
                found = true;
                break;
            }
        }

        if (!found)
        {
            categories.push_back(facility.get_category());
            counts.push_back(1);
        }
    }

    //finding the longest category so the columns line up
    size_t width = 8;
    for (const string& category : categories)
    {
        if (category.size() > width)
        {
            width = category.size();
        }
    }
    width += 2;

    int total = facilities.size();
    cout << fixed << setprecision(1);
    cout << left << setw(width) << "Category" << right << setw(6) << "Count" << setw(12) << "Percentage" << endl;

    for (size_t i = 0; i < categories.size(); ++i)
    {
        //total is never zero here, the empty case returned above
        double percent = 100.0 * counts[i] / total;
        cout << left << setw(width) << categories[i] << right << setw(6) << counts[i] << setw(11) << percent << "%" << endl;
    }

    cout << left << setw(width) << "Total" << right << setw(6) << total << setw(11) << 100.0 << "%" << endl;
    //putting cout back to the default so later output isnt affected
    cout.unsetf(ios::fixed);
    cout << setprecision(6);
}

const vector<Facility>& FacilityManager::get_all_facilities() const
{
    return facilities;
}
