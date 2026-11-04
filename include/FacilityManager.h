// FacilityManager.h
// Purpose:
// Author:

#ifndef FACILITYMANAGER_H
#define FACILITYMANAGER_H

#include <string>
#include <vector>
#include "Facility.h"
#include "HashTable.h"

using namespace std;


class FacilityManager
{
    private:
        vector<Facility> facilities;
        HashTable table;

        //Verify the facility ID is in the correct format
        bool is_valid_facility_id(const string& id) const;
        //FInds the building based on name
        string find_building(const string& name, const vector<string>& buildings) const;

    public:
        //Loads the facilities from the file
        bool load_facilities(const string& filename, const vector<string>& buildings);
        //Displays all the facilities
        void display_facilities() const;
        //Searhces by ID after trimming and converting the input
        void search_by_id(const string& input) const;
        //returns all facilities as a vector
        const vector<Facility>& get_all_facilities() const;
};

#endif // FACILITYMANAGER_H
