//
//  FlowField.cpp
//  Autonomous
//
//  Created by 박 성완 on 12. 11. 7..
//
//

#include "FlowField.h"

FlowField::FlowField(Vec2f field_)
:resolution(20)
{
    cols = field_.x /resolution;
    rows = field_.y /resolution;
    
    field = new Vec2f*[cols];
    
    for (int i = 0; i < cols; i++) {
        field[i] = new Vec2f[rows];
//        for (int j = 0; j < rows; j++) {
//            field[i][j] = Vec2f(i,j);
//        }
    }
    
    

}

void FlowField::setup()
{
    float xOffset = 0;
    for (int i = 0; i < cols; i++) {
        float yOffset = 0;
        for (int j = 0 ; j <rows; j++) {
            float noise = Perlin().noise(xOffset, yOffset);
            float angle = lmap(noise, -0.01f, 0.01f, 0.0f, (float)M_2_PI);
            field[i][j] = Vec2f(cosf(angle), sinf(angle));

            yOffset += 0.01;
            std::cout << "noise : " << noise << ", angle : " << angle << std::endl;
        }
        xOffset += 0.01;
    }
}

void FlowField::update(float sec)
{
    float xOffset = (sec + 1000) * 0.05;
    for (int i = 0; i < cols; i++) {
        float yOffset = (sec + 2000) * 0.05;
        for (int j = 0 ; j <rows; j++) {
            float noise = Perlin().noise(xOffset, yOffset);
            float angle = lmap(noise, -0.01f, 0.01f, 0.0f, (float)M_2_PI);
            field[i][j] = Vec2f(cosf(angle), sinf(angle));
            yOffset += 0.01;
            //std::cout << "noise : " << noise << ", angle : " << angle << std::endl;
        }
        xOffset += 0.01;
    }
}

void FlowField::draw()
{
    for (int i =0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            gl::pushMatrices();
            gl::translate(Vec2f(i*resolution + resolution /2, j*resolution + resolution /2));
            gl::rotate(toDegrees(atan2(field[i][j].y, field[i][j].x) - M_PI/2));
            
            gl::begin(GL_TRIANGLE_FAN);
            gl::vertex(0, resolution/2);
            gl::vertex(resolution/5, resolution/4);
            gl::vertex(-resolution/5, resolution/4);
            gl::end();
            gl::drawLine(Vec2f(0,resolution/2), Vec2f(0,-resolution/2));
            

            gl::popMatrices();
        }
    }
}