/*#include "World.h"
#include <random>
#include <limits>
#include "utils.h"

uint64_t get_rand() {
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<uint64_t> distr;

    return distr(eng);
}

// Adds object to world with a specific object ID to be accessed later,
// but if obj_id < 0, a random object ID is used that hasn't been used before
// Returns -1 on error.
uint64_t World::add_object_to_world(Object& obj, uint64_t obj_id) {
    if (obj_id < 0) {
        bool added = false;
        while (!added) {
            obj_id = get_rand();
            if (!objects.count(obj_id)) {
                objects[obj_id] = obj;
                added = true;
                return obj_id;
            }
        }
    }

    if (!objects.count(obj_id)) {
        objects[obj_id] = obj;
        return obj_id;
    }

    return -1;
}

const Object* World::get_object(uint64_t obj_id) {
    return (const Object*)(&objects[obj_id]);
}*/