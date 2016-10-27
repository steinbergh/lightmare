//
//  watcher.cpp
//  privateEyes
//
//  Created by Henry Steinberg on 10/25/16.
//
//

#include "watcher.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace osc;


Watcher::Watcher() :
mReceiver(12000)
{

}

Watcher::~Watcher() {
    
}

void Watcher::setup() {
//    mReceiver.setListener( "/TSPS/personUpdated",
//      [&]( const osc::Message &msg ){
//          mPersonPosition.x = msg[3].int32();
//          mPersonPosition.y = msg[4].int32();
//      });
//    mReceiver.bind();
//    mReceiver.listen();
}

void Watcher::update() {
    
}
