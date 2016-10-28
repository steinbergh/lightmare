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
mIsOpen(false),
mPupil(nullptr),
mCornea(nullptr)
{
    
}

Eye::~Eye() {
    
}

void Eye::setup(ci::vec2 pos, float radius, int id) {
    mEyeRadius = radius;
    mPupilRadius = radius * .35f;
    mPos = pos;
    
    mStyle = setStyle(id);
    
    switch (mStyle) {
        case Style::STYLE_1: {
            
            auto pupil_img = loadImage( loadAsset( "pupils/pupils_eye01.png" ) );
            mPupil = gl::Texture2d::create( pupil_img );
            
            auto cornea_img = loadImage( loadAsset( "whites/whites_eye01.png" ) );
            mCornea = gl::Texture2d::create( cornea_img );
            
            }
            break;
        
        case Style::STYLE_2: {
            
            auto pupil_img = loadImage( loadAsset( "pupils/pupils_eye02.png" ) );
            mPupil = gl::Texture2d::create( pupil_img );
            
            auto cornea_img = loadImage( loadAsset( "whites/whites_eye02.png" ) );
            mCornea = gl::Texture2d::create( cornea_img );
            
            }
            break;
            
        case Style::STYLE_3: {
            
            auto pupil_img = loadImage( loadAsset( "pupils/pupils_eye03.png" ) );
            mPupil = gl::Texture2d::create( pupil_img );
            
            auto cornea_img = loadImage( loadAsset( "whites/whites_eye03.png" ) );
            mCornea = gl::Texture2d::create( cornea_img );
            
            }
            break;
            
        case Style::STYLE_4: {
            
            auto pupil_img = loadImage( loadAsset( "pupils/pupils_eye04.png" ) );
            mPupil = gl::Texture2d::create( pupil_img );
            
            auto cornea_img = loadImage( loadAsset( "whites/whites_eye04.png" ) );
            mCornea = gl::Texture2d::create( cornea_img );
            
            }
            break;
            
        case Style::STYLE_5: {
            
            auto pupil_img = loadImage( loadAsset( "whites/whites_eye05.png" ) );
            mPupil = gl::Texture2d::create( pupil_img );
            
            auto cornea_img = loadImage( loadAsset( "whites/whites_eye05.png" ) );
            mCornea = gl::Texture2d::create( cornea_img );
            
            }
            break;
            
        default:
            break;
    }
}


Eye::Style Eye::setStyle(int id) {
    return Eye::Style(randInt(0,4));
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
    gl::enableAlphaBlending();
    gl::color(Color(1.0, 1.0, 1.0));

    gl::pushMatrices();
    gl::translate(mPos.value());
    gl::scale(mEyeScale);
    gl::drawSolidCircle(vec2(0.0), mEyeRadius);
    
    gl::translate(vec2(-mEyeRadius));
    gl::color(Color(1.0, 0.0, 0.0));
    Rectf destRect = Rectf(0,0,mEyeRadius*2,mEyeRadius*2);
    gl::draw(mCornea, Area(destRect.getCenteredFit(mCornea->getBounds(), true)), destRect);
    gl::translate(vec2(mEyeRadius));
    
    {
        gl::translate(mPupilPos.value());
        gl::color(Color(1.0, 1.0, 1.0));
        
        gl::translate(vec2(-mEyeRadius));
        Rectf destRect = Rectf(0,0,mEyeRadius*2,mEyeRadius*2);
        gl::draw(mPupil, Area(destRect.getCenteredFit(mPupil->getBounds(), true)), destRect);
        //gl::drawSolidCircle(vec2(0.0), mPupilRadius);
    }
    gl::popMatrices();
    gl::disableAlphaBlending();
    
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

