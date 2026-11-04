// HashTable.cpp
// Purpose: Hash the facilities IDs into the hash table, handling collision and other changes
// Author: Tobias

#include "HashTable.h"
#include "FileUtils.h"

using namespace std;

HashTable::HashTable(int capacity)
{
    if(capacity < 1)
    {
        capacity = DEFAULT_CAPACITY;
    }
    entry_count = 0;
    collision_count = 0;
    buckets.resize(capacity);
}

int HashTable::hash(const string& key) const
{
    string normalized = to_upper(key);
    int capacity = static_cast<int>(buckets.size());
    int h = 0;

    for(char c : normalized)
    {
        h = (h * 31 + static_cast<unsigned char>(c)) % capacity;
    }
    return h;
}

bool HashTable::insert(const Facility& facility)
{
    string key = to_upper(facility.get_facility_id());

    if(contains(key))
    {
        return false;
    }

    vector<Facility>& bucket = buckets[hash(key)];
    if(!bucket.empty())
    {
        collision_count++;
    }
    bucket.push_back(facility);
    entry_count++;
    return true;
}

const Facility* HashTable::find(const string& id) const
{
    string key = to_upper(id);
    const vector<Facility>& bucket = buckets[hash(key)];

    for(const Facility& facility : bucket)
    {
        if(facility.get_facility_id() == key)
        {
            return &facility;
        }
    }
    return nullptr;
}

bool HashTable::contains(const string& id) const
{
    return find(id) != nullptr;
}

int HashTable::get_capacity() const
{
    return static_cast<int>(buckets.size());
}

int HashTable::get_size() const
{
    return entry_count;
}

int HashTable::get_collisions() const
{
    return collision_count;
}
