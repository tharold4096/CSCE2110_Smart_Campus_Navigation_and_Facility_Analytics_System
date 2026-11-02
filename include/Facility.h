// Facility.h

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
        Facility();
        Facility(string id, string name, string building, string type);

        string get_facility_id() const;
        string get_facility_name() const;
        string get_building_name() const;
        string get_category() const;
        void print() const;
};

#endif // FACILITY_H
