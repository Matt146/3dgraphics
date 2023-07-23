/*#ifndef WORLD_H
#define WORLD_H

#include <eigen3/Eigen/Dense>
#include <vector>
#include <map>
#include <SDL2/SDL.h>

struct Object;

class World {
public:
    uint64_t add_object_to_world(Object& obj, uint64_t obj_id);
    const Object* get_object(uint64_t obj_id);
private:
    // NOTE: all object id's are >= 0
    std::map<uint64_t, Object> objects;
};

#endif // WORLD_H*/