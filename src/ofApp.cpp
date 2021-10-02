#include "ofApp.h"

#include "ecs/SystemLifeCycle.h"
#include "ecs/dataTypes/Positional.h"
#include "ecs/dataTypes/Visuals.h"
#include "ecs/systems/Movement.h"
#include "ecs/systems/Rendering.h"

void FixRiderLogging()
{
    ecs_os_set_api_defaults();
    ecs_os_api_t api = ecs_os_api;
    api.log_ = [](const char *fmt, va_list args){
        vfprintf(stdout, fmt, args);
        fprintf(stdout, "\n");
        fflush(stdout);
    };
    ecs_os_set_api(&api);
}

//--------------------------------------------------------------
void ofApp::setup(){
    FixRiderLogging();
    
    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetBackgroundAuto(false);

    std::vector<LifecycleHandle> Systems{
        Movement::MakeHandle(),
        Rendering::MakeHandle()
    };

    for(auto Hndl : Systems)
    {
        Hndl.RegisterTypes(ECSWorld);
    }
    for(auto Hndl : Systems)
    {
        Hndl.InitGlobals(ECSWorld);
    }
    for(auto Hndl : Systems)
    {
        Hndl.RegisterSystems(ECSWorld);
    }

    Renderer = ECSWorld.component<RenderPhases>().get_ref<RenderPhases>();
}

//--------------------------------------------------------------
void ofApp::update(){
    if(!ECSWorld.progress())
    {
        exit();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    Renderer->Pipeline.each([](flecs::entity RenderSystem)
    {
        flecs::system<>(RenderSystem.world(), RenderSystem).run();
    });
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ecs_trace(0, "Key Pressed %c", key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    ecs_trace(0, "Key Released %c", key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    // ecs_trace(0, "Mouse Moved (%d, %d)", x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    ecs_trace(0, "Mouse Dragged (%d, %d) %d", x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ecs_trace(0, "Mouse Pressed (%d, %d) %d", x, y, button);

    ECSWorld.entity()
        .set<Transform>( {
        {
            static_cast<float>(x),
            static_cast<float>(y)
        }})
        .set<Velocity>({{1, 0, 0}})
        .set<Circle>({{ofColor::aquamarine}, 10});
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    ecs_trace(0, "Mouse Released (%d, %d) %d", x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    ecs_trace(0, "Mouse Entered %d, %d", x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    ecs_trace(0, "Mouse Exited %d, %d", x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    ecs_trace(0, "Resized %d, %d", w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
