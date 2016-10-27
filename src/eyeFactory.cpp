//
//  eyeFactory.cpp
//  privateEyes
//
//  Created by Henry Steinberg on 10/23/16.
//
//

#include "eyeFactory.hpp"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

EyeFactory::EyeFactory() :
mEyeCountX(0),
mEyeCountY(0)
{

}

EyeFactory::~EyeFactory(){

}

void EyeFactory::setup() {
    
}

void EyeFactory::addEye( int xi, int yi ) {
    //float seed = randFloat(35.0,  60.0);
    float x = ( xi + 0.5f ) * getWindowWidth() / mEyeCountX;
    float y = ( yi + 0.5f) * getWindowHeight() / mEyeCountY;
    
    EyeRef eye = EyeRef(new Eye());
    eye->setup(ci::vec2(x, y), randFloat(15.0, 60.0));
    //eye->setup(getWindowCenter(), seed * .5f);
    
    mEyes.push_back(eye);
}

std::vector<EyeRef> EyeFactory::createEyes(int countx, int county) {
    mEyeCountX = countx;
    mEyeCountY = county;
    for( int y=0; y < county; y++ ){
        for( int x=0; x < countx; x++ ){
            if (randInt(0,3) % 2 == 0) {
                addEye( x, y );
            }
        }
    }

    return mEyes;
}

void EyeFactory::updateEyes(const ci::vec2& point) {
    if (!mEyes.empty()) {
        for (const auto& eye : mEyes) {
            eye->lookAtPoint(point);
        }
    } else return;
}


void EyeFactory::drawEyes() {
    if (!mEyes.empty()) {
        for (const auto& eye : mEyes) {
            eye->draw();
        }
    } else return;
}

