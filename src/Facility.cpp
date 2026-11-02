// Facility.cpp


#include "Facility.h"
#include <iostream>

using namespace std;

Facility::Facility()
{
    facility_id = "";
    facility_name = "";
    building_name = "";
    category = "";
}

Facility::Facility(string id, string name, string building, string type)
{
    facility_id = id;
    facility_name = name;
    building_name = building;
    category = type;
}

string Facility::get_facility_id() const
{
    return facility_id;
}

string Facility::get_facility_name() const
{
    return facility_name;
}

string Facility::get_building_name() const
{
    return building_name;
}

string Facility::get_category() const
{
    return category;
}

void Facility::print() const
{
    cout << "ID: " << facility_id << " | " << "Name: " << " | " << facility_name << "Building: " << building_name << " | " << "Category: " << category << endl;
}
