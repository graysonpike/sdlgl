#ifndef SDLGL_PHYSICAL_ENTITY_H
#define SDLGL_PHYSICAL_ENTITY_H

#include "entity.h"

class PhysicalEntity : public Entity {
   protected:
    float x, y;
    int w, h;
    void wrap_bounds();
    void clamp();
    float get_center_x() const;
    float get_center_y() const;

   public:
    PhysicalEntity(const std::shared_ptr<Scene>& scene, float x, float y, int w,
                   int h);
    virtual ~PhysicalEntity() = default;
    std::pair<int, int> get_position();
    std::pair<int, int> get_size();
};

#endif
