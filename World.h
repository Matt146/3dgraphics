#ifndef WORLD_H
#define WORLD_H

#include <eigen3/Eigen/Dense>
#include <vector>
#include <map>

struct Object {
    std::vector<Eigen::Vector4d> vertices; // vertices in local coordinates
    Eigen::Vector4d world_position; // position of the object in world space
    double yaw;
    double pitch;
    double roll;

    double scale_x;
    double scale_y;
    double scale_z;
};

class World {
public:
    uint64_t add_object_to_world(Object& obj, uint64_t obj_id);
    const Object* get_object(uint64_t obj_id);
private:
    // NOTE: all object id's are >= 0
    std::map<uint64_t, Object> objects;
};

#endif // WORLD_H