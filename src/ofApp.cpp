#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

//ofSetBackgroundAuto(false);
    ofSetVerticalSync(true);
	ofSetFrameRate(60);
    ofBackground(0);

    //SETTING INITIAL VALUES FOR COHESION, SEPARATION AND ALIGNMENT
    cVal = 100.0;
    sVal = 5.0;
    aVal = 8.0;


    //create the particles
    num = 500;

    for(int i =0; i < num; i++){

        Particle p;
        MyParticles.push_back(p);
        MyParticles[i].init();


    }

}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i =0; i < num; i++){
        MyParticles[i].update(MyParticles,cVal,sVal,aVal);
        //INFINITE WALLS APPLIED TO EACH PARTICLE DOESN'T WORK
        //MyParticles[i].infiniteWalls();
        MyParticles[i].bounding();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
   // ofBackground(0,5);
    //ofBackground(255,255,240);
	//ofSetColor(255);

    //note that easy cam gives you the ability to move the "camera" w/ mouse
    ofPushMatrix();

    //UNCOMMENT FOR 3-D:
    //cam.begin();
    //light.enable();
    //ofEnableLighting();
    //glEnable(GL_DEPTH_TEST);

    //DRAWING THE PARTICLES
    for(int i = 0; i < num; i++){
        MyParticles[i].draw();
    }

    //UNCOMMENT FOR 3-D:
    //glDisable(GL_DEPTH_TEST);
    //ofDisableLighting();
    //light.disable();
    //cam.end();
    ofSetColor(255,255,100);


    ofDrawBitmapString("To change cohesion, press: < > | Current Value: " + ofToString(cVal), ofGetWidth()*0.1, 25);
    ofDrawBitmapString("To change separation, press: - + | Current Value: " + ofToString(sVal), ofGetWidth()*0.1, 50);
    ofDrawBitmapString("To change alignment, press: RIGHTARROW LEFTARROW | Current Value: " + ofToString(aVal), ofGetWidth()*0.1, 75);

    ofPopMatrix();

        //UNCOMMENT TO SAVE IMAGES EVERY FRAME
    //string frameCount = ofToString(20000+ofGetFrameNum());
    //string fileName = "Images/" + frameCount + ".png";
    //ofSaveScreen(fileName);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'f'){
        ofToggleFullscreen();
    }

    if(key == 's'){
        string frameCount = ofToString(20000+ofGetFrameNum());
        string fileName = "Images/" + frameCount + ".jpg";
        ofSaveScreen(fileName);
    }



    switch (key) {

		case '>':
		case '.':
			cVal ++;
			break;

		case '<':
		case ',':
			cVal--;
			break;

		case '+':
		case '=':
			sVal+=0.1f;
			break;

		case '-':
			sVal-=0.1f;
			break;

		case OF_KEY_RIGHT:
			aVal++;
			break;

		case OF_KEY_LEFT:
		    if (aVal > 1){
			aVal--;
		    }
			break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
