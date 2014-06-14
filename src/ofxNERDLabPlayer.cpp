//
//  ofxNERDLabPlayer.cpp
//  ofxNERDLab_Example
//
//  Created by Clay Ewing on 6/13/14.
//
//

#include "ofxNERDLabPlayer.h"

ofxNERDLabPlayer::ofxNERDLabPlayer(string _name, string _ip, int _tag) {
    ip = _ip;
    name = _name;
    score = 0;
    tag = _tag;
}


void ofxNERDLabPlayer::initialize() {
    client.setup(ip, OFXNERDLAB_CLIENT_PORT);
    ofxOscMessage msg;
    msg.setAddress("set");
    msg.addStringArg("id");
    msg.addIntArg(tag);
    msg.setRemoteEndpoint(ip, OFXNERDLAB_CLIENT_PORT);
    client.sendMessage(msg);
    msg.clear();
    
}

void ofxNERDLabPlayer::pause() {
    sendState(OFXNERDLAB_GAME_STATE_PAUSED);
}

void ofxNERDLabPlayer::showMessage() {
    sendState(OFXNERDLAB_GAME_STATE_SHOW_MESSAGE);
}

void ofxNERDLabPlayer::showWaitingScreen() {
    sendState(OFXNERDLAB_GAME_STATE_WAITING);
}

void ofxNERDLabPlayer::useMovementAsControl() {
    sendControl(OFXNERDLAB_GAME_CONTROL_MOVE);
}

void ofxNERDLabPlayer::useAudioInputAsControl() {
    sendControl(OFXNERDLAB_GAME_CONTROL_AUDIO);
}
void ofxNERDLabPlayer::useAccelerometerAsControl(){
    sendControl(OFXNERDLAB_GAME_CONTROL_ACCEL);
}
void ofxNERDLabPlayer::useTapAndHoldAsControl() {
    sendControl(OFXNERDLAB_GAME_CONTROL_TAP);
}
void ofxNERDLabPlayer::useRotationAsControl() {
    sendControl(OFXNERDLAB_GAME_CONTROL_ROTATE);
}

void ofxNERDLabPlayer::useImageSet(int imageSet){
    ofxOscMessage msg;
    msg.setAddress("set");
    msg.addStringArg("images");
    msg.addIntArg(imageSet);
    client.sendMessage(msg);
    msg.clear();
}


void ofxNERDLabPlayer::setPlaying(bool playing) {
    ofxOscMessage msg;
    msg.setAddress("set");
    msg.addStringArg("playing");
    if (playing) {
        msg.addIntArg(1);
    }
    else {
        msg.addIntArg(0);
    }
    client.sendMessage(msg);
    msg.clear();
    sendState(OFXNERDLAB_GAME_STATE_PLAYING);
}

void ofxNERDLabPlayer::sendState(int state) {
    ofxOscMessage msg;
    msg.setAddress("set");
    msg.addStringArg("state");
    msg.addIntArg(state);
    client.sendMessage(msg);
    msg.clear();
}


void ofxNERDLabPlayer::sendControl(int control) {
    ofxOscMessage msg;
    msg.setAddress("set");
    msg.addStringArg("control");
    msg.addIntArg(control);
    client.sendMessage(msg);
    msg.clear();

}

void ofxNERDLabPlayer::sendScore(int score) {
    ofxOscMessage msg;
    msg.setAddress("set");
    msg.addStringArg("score");
    msg.addIntArg(score);
    client.sendMessage(msg);
}

void ofxNERDLabPlayer::sendGameName(string gameName) {
    ofxOscMessage msg;
    msg.setAddress("set");
    msg.addStringArg("game");
    msg.addStringArg(gameName);
    client.sendMessage(msg);
}

void ofxNERDLabPlayer::sendMessage(string message) {
    ofxOscMessage msg;
    msg.setAddress("set");
    msg.addStringArg("instructions");
    msg.addStringArg(message);
    client.sendMessage(msg);
}
