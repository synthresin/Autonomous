//
//  FlowField.h
//  Autonomous
//
//  Created by 박 성완 on 12. 11. 7..
//
//

#ifndef __Autonomous__FlowField__
#define __Autonomous__FlowField__

#include <iostream>
#include "cinder/Vector.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Perlin.h"

using namespace ci;


class FlowField {

    int cols, rows;
    int resolution;
    Vec2f **field;

    
public:
    FlowField(Vec2f field_);
    void setup();
    void update(float sec);
    void draw();
};

#endif /* defined(__Autonomous__FlowField__) */
