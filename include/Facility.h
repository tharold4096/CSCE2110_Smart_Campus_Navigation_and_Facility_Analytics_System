// Facility.h
// Purpose: The header file for the facilities class
// Author: Tobias

#ifndef FACILITY_H
#define FACILITY_H

#include <string>

using namespace std;

class Facility
{
    private:
        string facility_id;
        string facility_name;
        string building_name;
        string category;

    public:
        //DEfault constructor
        Facility();
        //COnstructor with information assignment
        Facility(string id, string name, string building, string type);

        //returns facility ID
        string get_facility_id() const;
        //returns facility name
        string get_facility_name() const;
        //returns building name
        string get_building_name() const;
        //returns category
        string get_category() const;
        //print function
        void print() const;
};

#endif // FACILITY_H
