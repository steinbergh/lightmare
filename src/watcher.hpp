//
//  watcher.hpp
//  privateEyes
//
//  Created by Henry Steinberg on 10/25/16.
//
//

#ifndef watcher_hpp
#define watcher_hpp

#include <stdio.h>

#endif /* watcher_hpp */

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/Log.h"
#include "cinder/osc/Osc.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#define USE_UDP 1

#if USE_UDP
using Receiver = osc::ReceiverUdp;
#else
using Receiver = osc::ReceiverTcp;
#endif

typedef std::shared_ptr<class Watcher> WatcherRef;

class Watcher {

public:
    Watcher();
    ~Watcher();
    void setup();
    void update();
    
    osc::ReceiverUdp  mReceiver;
    //vector<Person>  mPeople;
    //Person          mPerson;
    ci::vec2 mPersonPosition;
};
