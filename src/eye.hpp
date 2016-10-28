//
//  eye.hpp
//  privateEyes
//
//  Created by Henry Steinberg on 10/23/16.
//
//

#ifndef eye_hpp
#define eye_hpp

#include <stdio.h>

#endif /* eye_hpp */

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Tween.h"
#include "cinder/Timeline.h"

typedef std::shared_ptr<class Eye> EyeRef;

class Eye {
    
    
public:
    
    enum class Style {
        STYLE_1 = 0,
        STYLE_2 = 1,
        STYLE_3 = 2,
        STYLE_4 = 3,
        STYLE_5 = 5,
    } mStyle;
    
    Eye();
    ~Eye();
    
    void            setup(ci::vec2 pos = ci::vec2(0.0f), float radius = 0.0f, int id = 0);
    void            draw();
    void            lookAtPoint(ci::vec2 point);
    
    void            setLookAtPoint(ci::vec2 point) {mLookAt = point;}
    
    void            openClose(float distance, float minDistance);
    void            blink(bool open);
    
    Style            setStyle(int id);
    
    ci::TimelineRef getTimeline();
    
    
    ci::Anim<ci::vec2>  mPos, mPupilPos, mEyeScale;

    ci::vec2            mLookAt;
    ci::TimelineRef     mTimeline;
    ci::mat4            mTransform;
    
    ci::gl::Texture2dRef    mPupil,mCornea;
    
    float       mEyeRadius, mPupilRadius, pctOpen;
    bool        mIsOpen;
};
