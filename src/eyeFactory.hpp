//
//  eyeFactory.hpp
//  privateEyes
//
//  Created by Henry Steinberg on 10/23/16.
//
//

#ifndef eyeFactory_hpp
#define eyeFactory_hpp

#include <stdio.h>
#endif /* eyeFactory_hpp */

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Tween.h"
#include "cinder/Timeline.h"
#include "eye.hpp"

typedef std::shared_ptr<class EyeFactory> EyeFactoryRef;

class EyeFactory {

public:
    EyeFactory();
    ~EyeFactory();
    
    void setup();
    
    std::vector<EyeRef> createEyes(int countx = 1, int county = 1);
    void   drawEyes();
    void   updateEyes(const ci::vec2& point);
    
    void   addEye(int xEye, int yEye);
    
    std::vector<EyeRef>     mEyes;
    std::vector<ci::vec2>   mEyeGrid;
    int                     mEyeCountX, mEyeCountY;
};
