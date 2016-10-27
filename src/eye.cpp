//
//  eye.cpp
//  privateEyes
//
//  Created by Henry Steinberg on 10/23/16.
//
//

#include "eye.hpp"
#include "cinder/Rand.h"


using namespace ci;
using namespace ci::app;
using namespace std;

Eye::Eye() :
mEyeRadius(0.0f),
mPupilRadius(0.0f),
mPos(vec2(0.0f)),
mPupilPos(vec2(0.0f)),
mLookAt(0.0f),
mEyeScale(vec2(1, 1.0f)),
mIsOpen(false)
{
    
}

Eye::~Eye() {
    
}

void Eye::setup(ci::vec2 pos, float radius) {
    mEyeRadius = radius;
    mPupilRadius = radius * .35f;
    mPos = pos;
    
}

TimelineRef Eye::getTimeline() {
    if (!mTimeline) {
        mTimeline = Timeline::create();
    }
    if (mTimeline) {
        mTimeline->stepTo(timeline().getCurrentTime());
    }
    return mTimeline;
}

void Eye::openClose(float distance, float minDistance) {
    
    if (distance <  minDistance * 5.f) {
        getTimeline()->apply(&mEyeScale, vec2(1, .5), .5f, EaseOutQuad());
    } else {
        getTimeline()->apply(&mEyeScale, vec2(1, 0.0), .095f, EaseOutQuad());
    }
}

void Eye::blink(bool open) {
    if (open) {

    } else return;
}

void Eye::lookAtPoint(ci::vec2 point) {
    mLookAt = point - mPos.value();
    
    float dx = (point.x - mPos.value().x) * (point.x - mPos.value().x);
    float dy = (point.y - mPos.value().y) * (point.y - mPos.value().y);
    float d = sqrtf(dx + dy);
    
    //openClose(d, mEyeRadius);
    
    if (d >= mEyeRadius) {
        ci::vec2 FromPupilToPerson = mLookAt - mPupilPos.value();
        FromPupilToPerson *= (mEyeRadius - mPupilRadius) / length(FromPupilToPerson);
        mLookAt = FromPupilToPerson;
        //normalize(mLookAt);
    }
    
    getTimeline()->apply(&mPupilPos, mLookAt, .075f, EaseNone());
    
}

void Eye::draw() {
    //left eye
    gl::color(Color(1.0, 1.0, 1.0));
    
    gl::pushMatrices();
    gl::translate(mPos.value());
    gl::scale(mEyeScale);
    gl::drawSolidCircle(vec2(0.0), mEyeRadius);
    {
        gl::translate(mPupilPos.value());
        gl::color(Color(0.0, 0.0, 0.0));
        gl::drawSolidCircle(vec2(0.0), mPupilRadius);
    }
    gl::popMatrices();
    
//    //right eye
//    gl::pushMatrices();
//    gl::color(Color(1.0, 1.0, 1.0));
//    gl::translate(vec2(mPos.value().x + mEyeRadius * 1.125, mPos.value().y));
//    gl::scale(mEyeScale);
//    gl::drawSolidCircle(vec2(0.0), mEyeRadius);
//    {
//        gl::translate(mPupilPos.value());
//        gl::color(Color(0.0, 0.0, 0.0));
//        //gl::scale(vec2(1.0, 2.0));
//        gl::drawSolidCircle(vec2(0.0), mPupilRadius);
//    }
//    gl::popMatrices();
}

