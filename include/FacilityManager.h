// FacilityManager.h
// Purpose: Manages the facilities, loading them, displaying them, and searching through them
// Author: Tobias

#ifndef FACILITYMANAGER_H
#define FACILITYMANAGER_H

#include <string>
#include <vector>
#include "CampusGraph.h"
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

    public:
        //Loads the facilities from the file, checking each building against the campus graph
        bool load_facilities(const string& filename, const CampusGraph& graph);
        //Displays all the facilities
        void display_facilities() const;
        //Searhces by ID after trimming and converting the input
        void search_by_id(const string& input) const;
        //returns all facilities as a vector
        const vector<Facility>& get_all_facilities() const;
};

#endif // FACILITYMANAGER_H
