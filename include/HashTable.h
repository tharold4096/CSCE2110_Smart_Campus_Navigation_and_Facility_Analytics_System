// HashTable.h
// Purpose: Hash table outline for hashing
// Author: Tobias

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include "Facility.h"

using namespace std;


class HashTable
{
    private:
        //random prime selected for now
        static const int DEFAULT_CAPACITY = 13;
        vector<vector<Facility>> buckets;
        int entry_count;
        int collision_count;
        int hash(const string& key) const;
    public:
        HashTable(int capacity = DEFAULT_CAPACITY);

        bool insert(const Facility& facility);
        const Facility* find(const string& id) const;
        bool contains(const string& id) const;
        int get_capacity() const;
        int get_size() const;
        int get_collisions() const;
};

#endif // HASHTABLE_H
