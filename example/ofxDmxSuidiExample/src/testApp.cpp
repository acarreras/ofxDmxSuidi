#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(25);

    dmx.loadRuntimeLibrary();
    dmx.openInterface();
    dmx.dmxPortConfig();

    channelR = 0;
    channelG = 1;
    channelB = 2;

    colorR = colorG = colorB = 0;
    colorH = 0;
    colorDmx.setHue(colorH);
    colorDmx.setSaturation(255);
    colorDmx.setBrightness(255);
}

//--------------------------------------------------------------
void testApp::update(){

    colorR = int(colorDmx.r);
    colorG = int(colorDmx.g);
    colorB = int(colorDmx.b);

    dmx.updateDmxChannel(channelR, colorR);
    dmx.updateDmxChannel(channelG, colorG);
    dmx.updateDmxChannel(channelB, colorB);

    dmx.sendDmxBlockOut();

    colorH++;
    if(colorH > 255){
        colorH = 0;
    }
    colorDmx.setHue(colorH);
}

//--------------------------------------------------------------
void testApp::draw(){

    ofSetWindowTitle("ofxDmxSuidiExample");
    ofBackground(colorR, colorG, colorB);

    ofEnableAlphaBlending();

    ofSetColor(255,255,255,100);
    ofFill();
    ofRect(0,0,ofMap(colorR, 0,255, 0,ofGetWidth()), ofGetHeight()/3);
    ofRect(0,ofGetHeight()/3,ofMap(colorG, 0,255, 0,ofGetWidth()), ofGetHeight()/3);
    ofRect(0,2*ofGetHeight()/3,ofMap(colorB, 0,255, 0,ofGetWidth()), ofGetHeight()/3);

    ofSetColor(255,255,255,255);
    ofSetLineWidth(3);
    ofNoFill();
    ofRect(0,0,ofMap(colorR, 0,255, 0,ofGetWidth()), ofGetHeight()/3);
    ofRect(0,ofGetHeight()/3,ofMap(colorG, 0,255, 0,ofGetWidth()), ofGetHeight()/3);
    ofRect(0,2*ofGetHeight()/3,ofMap(colorB, 0,255, 0,ofGetWidth()), ofGetHeight()/3);


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void testApp::exit(){
    dmx.closeInterface();
}
