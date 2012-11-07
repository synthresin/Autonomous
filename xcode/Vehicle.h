//
//  Vehicle.h
//  Autonomous
//
//  Created by 박 성완 on 12. 11. 6..
//
//

#ifndef __Autonomous__Vehicle__
#define __Autonomous__Vehicle__

#include <iostream>
#include "cinder/Vector.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;

class Vehicle {
    Vec2f location;
    Vec2f velocity;
    Vec2f acceleration;
    
    float   maxspeed;
    float   maxforce;
    float   r;
    Vec2f targetCenterPos;
    Vec2f currentTarget;
    
public:
    Vehicle();
    Vehicle(const Vec2f loc);
    void seek(const Vec2f target);
    void arrive(const Vec2f target);
    void wander();
    void detectEdge(const Vec2f field);
    void update();
    void draw();
    void applyForce(const Vec2f f);
};
#endif /* defined(__Autonomous__Vehicle__) */
