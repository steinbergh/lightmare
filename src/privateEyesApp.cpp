#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/Log.h"
#include "cinder/Timeline.h"
#include "cinder/osc/Osc.h"

#include "eyeFactory.hpp"
//#include "watcher.cpp"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace osc;

#define USE_UDP 1

#if USE_UDP
using Receiver = osc::ReceiverUdp;
#else
using Receiver = osc::ReceiverTcp;
#endif



class privateEyesApp : public App {
    struct Person {
        int          id;
        ci::vec2    pos;
    };

public:
    privateEyesApp();
	void setup() override;
	void mouseMove( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    EyeFactoryRef mEyeFactory;
    ci::vec2 mPointToTrack, mMovDelta;
    Receiver mReceiver;
    
    std::vector<Person> mPeople;
    bool mUseMouse = true;
};

privateEyesApp::privateEyesApp() :
mReceiver( 12000 ){

}

void privateEyesApp::setup()
{
    
    setFullScreen(true);
    mEyeFactory = EyeFactoryRef(new EyeFactory());
    mEyeFactory->setup();
    mEyeFactory->createEyes(5,6);
    
    if (!mUseMouse) {
        mReceiver.setListener( "/TSPS/personUpdated/",
          [&]( const osc::Message &msg ){
              //Person newPerson;
              //newPerson.id    = msg[0].int32();
              //mPeople.push_back(newPerson);
    //          if (!mPeople.empty()) {
    //              mPeople[0].pos * vec2(getWindowSize()) = mPointToTrack;
    //          } else {
    //              newPerson.pos * vec2(getWindowSize()) = mPointToTrack;
    //          }
              mPointToTrack = vec2(msg[3].flt() * getWindowWidth(), msg[4].flt() * getWindowHeight());
          });
        
    //    mReceiver.setListener( "/TSPS/personWillLeave/",
    //      [&]( const osc::Message &msg ){
    //          int idToLeave = msg[0].int32();
    //         
    //          if (!mPeople.empty()) {
    //              for (auto it = mPeople.begin(); it != mPeople.end(); ++it) {
    //                  if (it->id == idToLeave) {
    //                      mPeople.erase(it);
    //                  }
    //              }
    //          }
    //      });
        
    
        mReceiver.bind();
        mReceiver.listen();
    }
}

void privateEyesApp::mouseMove( MouseEvent event )
{
    if (mUseMouse) {
        const ci::vec2 currentPosition = event.getPos();
        const ci::vec2 delta = mPointToTrack == ci::vec2(0) ? ci::vec2(0) : currentPosition - mPointToTrack;
        
        mMovDelta = delta;
        
        mPointToTrack = currentPosition;
        //console() << dot(mMovDelta, mPointToTrack) << endl;
    }

}

void privateEyesApp::update()
{
    //console() << mPointToTrack << endl;
    const ci::vec2 currentPosition = mPointToTrack;
    const ci::vec2 delta = mPointToTrack == ci::vec2(0) ? ci::vec2(0) : currentPosition - mPointToTrack;
    
    mMovDelta = delta;
    
    mPointToTrack = currentPosition;
    mEyeFactory->updateEyes(mPointToTrack);
    
    //console() << mPointToTrack << endl;
}

void privateEyesApp::draw()
{
    
    gl::pushMatrices();
	gl::clear( Color( 0, 0, 0 ) );
    mEyeFactory->drawEyes();
    gl::color(Color(1,0,0));
    
    //shows the direction of movement
    gl::drawLine(mPointToTrack, mPointToTrack + (mMovDelta * vec2(10)));
    gl::popMatrices();

}

CINDER_APP( privateEyesApp, RendererGl(RendererGl::Options().msaa(8)) )
