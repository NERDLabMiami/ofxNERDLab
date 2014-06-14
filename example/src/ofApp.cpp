#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    nerdlab = new ofxNERDLab();
    ofAddListener(nerdlab->receivedMove, this, &ofApp::move);
    ofAddListener(nerdlab->receivedAccelerometer, this, &ofApp::accelerometer);
    ofAddListener(nerdlab->receivedTap, this, &ofApp::tap);
    ofAddListener(nerdlab->receivedRelease, this, &ofApp::release);
    ofAddListener(nerdlab->receivedAudioInput, this, &ofApp::audio);

}

//--------------------------------------------------------------

void ofApp::move(ofxNERDLabMoveEvent &e) {
    balls[e.id].drift(e.x, e.y);
}

void ofApp::accelerometer(ofxNERDLabAccelerometerEvent &e) {
    cout << "accel!" << endl;
    balls[e.id].drift(e.x, e.y);
}

void ofApp::tap(ofxNERDLabTapEvent &e) {
    balls[e.id].changecolor();
}

void ofApp::release(ofxNERDLabReleaseEvent &e) {
    balls[e.id].grow(e.time);
}

void ofApp::audio(ofxNERDLabAudioInputEvent &e) {
    balls[e.id].grow(e.amplitude);
}



void ofApp::update(){
	for(int i=0; i < balls.size(); i++){
		balls[i].update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i = 0; i< balls.size(); i++){
        balls[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //create players from connected clients
    if (key == ' ') {
        balls.clear();
        players.clear();
        for (int i = 0; i < nerdlab->clients.size(); i++) {
            players.push_back(ofxNERDLabPlayer(nerdlab->clients[i].name, nerdlab->clients[i].ip, players.size()));
            Ball newBall = Ball();
            newBall.init();
            balls.push_back(newBall);
        }

        //initialization and creation have been separated to allow more flexibility
        for (int i = 0; i < players.size(); i++) {
            players[i].initialize();
        }
    
    }

    //allow players to control something
    if (key == 'p') {
        for (int i = 0; i < players.size(); i++) {
            players[i].setPlaying(true);
        }
        
    }
    
    
    //enable movement for all players
    if (key == '1') {
        for (int i = 0; i < players.size(); i++) {
            players[i].useMovementAsControl();
        }
        
    }

    //enable accelerometer for all players
    if (key == '2') {
        for (int i = 0; i < players.size(); i++) {
            players[i].useAccelerometerAsControl();
        }
        
    }
    
    //enable tapping and hold control for all players
    if (key == '3') {
        for (int i = 0; i < players.size(); i++) {
            players[i].useTapAndHoldAsControl();
        }
        
    }
    
    if (key == '4') {
        for (int i = 0; i < players.size(); i++) {
            players[i].useAudioInputAsControl();
        }
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
