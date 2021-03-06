#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Vehicle.h"
#include "FlowField.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class AutonomousApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
	void update();
	void draw();
    
    Vehicle v;
    Vec2f mousePos;
    FlowField *f;
    
};

void AutonomousApp::setup()
{
    v = Vehicle(getWindowCenter());
    mousePos = Vec2f::zero();
    f = new FlowField(getWindowSize());
    f->setup();
    
}

void AutonomousApp::mouseDown( MouseEvent event )
{

}

void AutonomousApp::mouseMove( MouseEvent event )
{
    mousePos = event.getPos();
}

void AutonomousApp::update()
{
    //v.arrive(mousePos);
    v.wander();
    v.update();
    v.detectEdge(getWindowSize());
    //f->update(getElapsedSeconds());
}

void AutonomousApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    //f->draw();
    v.draw();
}

CINDER_APP_BASIC( AutonomousApp, RendererGl )
