//
//  Vehicle.cpp
//  Autonomous
//
//  Created by 박 성완 on 12. 11. 6..
//
//

#include "Vehicle.h"

Vehicle::Vehicle()
:acceleration(Vec2f::zero()), velocity(Vec2f::zero()), location(Vec2f::zero()), r(6.0f), maxspeed(5.0f), maxforce(0.1)
{

}

Vehicle::Vehicle(const Vec2f loc)
:acceleration(Vec2f::zero()), velocity(randVec2f()), location(loc), r(6.0f), maxspeed(5.0f), maxforce(0.2)
{

}

void Vehicle::applyForce(const Vec2f f)
{
    acceleration += f;
}

void Vehicle::seek(const Vec2f target)
{
    Vec2f desired = target - location;
    //desired.limit(maxspeed);
    desired.limit(maxspeed);
    
    Vec2f steer = desired - velocity;
    steer.limit(maxforce);
    
    applyForce(steer);
}

void Vehicle::arrive(const Vec2f target)
{
    Vec2f desired = target - location;
    
    float d = desired.length();
    desired.normalize();
    
    if ( d > 100 ) {
        desired *= maxspeed;
    } else {
        float m = lmap(d, 0.0f, 100.0f, 0.0f, maxspeed);
        desired *= m;
    }
    
    Vec2f steer = desired - velocity;
    steer.limit(maxforce);
    
    applyForce(steer);
}

void Vehicle::wander() // use with arrive
{
    targetCenterPos =velocity.normalized() * 200.0f +location;
    currentTarget = targetCenterPos + randVec2f() * 50.0f;
    arrive(currentTarget);
}



void Vehicle::update()
{
    velocity += acceleration;
    velocity.limit(maxspeed);
    
    location += velocity;
    
    acceleration *= 0;
}

void Vehicle::detectEdge(const Vec2f field)
{
    //teleport method
//    if (location.x < 0 ) {
//        location.x = field.x;
//    } else if(location.x > field.x) {
//        location.x = 0;
//    }
//    
//    if (location.y < 0 ) {
//        location.y = field.y;
//    } else if(location.y > field.y) {
//        location.y = 0;
//    }
    
    // moving method
    if (location.x < 25 ) {
        Vec2f desired = Vec2f(maxspeed, velocity.y);
        Vec2f steer = desired - velocity;
        steer.limit(maxforce * 3);
        applyForce(steer);
        
    } else if(location.x > field.x -25) {
        Vec2f desired = Vec2f(-maxspeed, velocity.y);
        Vec2f steer = desired - velocity;
        steer.limit(maxforce * 3);
        applyForce(steer);
    }
    
    if (location.y < 25 ) {
        
        Vec2f desired = Vec2f(velocity.x, maxspeed);
        Vec2f steer = desired - velocity;
        steer.limit(maxforce * 3);
        applyForce(steer);
        
    } else if(location.y > field.y - 25) {
        
        Vec2f desired = Vec2f(velocity.x, -maxspeed);
        Vec2f steer = desired - velocity;
        steer.limit(maxforce * 3);
        applyForce(steer);
        
    }
    
}



void Vehicle::draw()
{
    
    float theta = atan2f(velocity.y, velocity.x) + M_PI/2;
    gl::color(0.8, 0.8, 0.8);
    gl::pushMatrices();
    
    gl::translate(location);
    gl::rotate(toDegrees(theta));
    
    gl::begin(GL_TRIANGLE_STRIP);
        gl::vertex(0, -r*2);
        gl::vertex(-r, r*2);
        gl::vertex(r, r*2);
    gl::end();
    
    
    gl::popMatrices();
    gl::drawStrokedCircle(targetCenterPos, 50.0f);
    gl::drawStrokedCircle(currentTarget, 4.0f);
}