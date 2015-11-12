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
    client = new ofxOscSender();
    controlsEnabled = false;
}


void ofxNERDLabPlayer::initialize() {
    client->setup(ip, OFXNERDLAB_CLIENT_PORT);
//    sendState(OFXNERDLAB_GAME_STATE_WAITING);

}

void ofxNERDLabPlayer::setId() {
    ofxOscMessage msg;
    cout << "Setting ID, Player Tag is " << tag << endl;
    msg.setAddress("set");
    msg.addStringArg("id");
    msg.addIntArg(tag);
//    msg.setRemoteEndpoint(ip, OFXNERDLAB_CLIENT_PORT);
    client->sendMessage(msg);
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

void ofxNERDLabPlayer::showGameInProgress() {
    sendState(OFXNERDLAB_GAME_STATE_IN_PROGRESS_CANT_JOIN);
}

void ofxNERDLabPlayer::rollCall() {
    sendReaction(OFXNERDLAB_GAME_STATE_ROLL_CALL);
}

void ofxNERDLabPlayer::pulse() {
    sendReaction(OFXNERDLAB_REACTION_PULSE);
    
}

void ofxNERDLabPlayer::vibrate() {
    sendReaction(OFXNERDLAB_REACTION_ROLL_CALL);
    
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
void ofxNERDLabPlayer::useRotationAndReleaseAsControl(){
    sendControl(OFXNERDLAB_GAME_CONTROL_ROTATE_RELEASE);
}
void ofxNERDLabPlayer::sendBackground(int background) {

    ofxOscMessage msg;
    msg.setAddress("/set");
    msg.addStringArg("background");
    msg.addIntArg(background);
    client->sendMessage(msg);
    msg.clear();

}

void ofxNERDLabPlayer::resend(int id, string _name, int gameState, ofColor color) {
    name = _name;
    ofxOscMessage msg;
    msg.setAddress("/rejoin");
    msg.addIntArg(id); //PLAYER ID
    msg.addIntArg(gameState); //GAME STATE
    msg.addIntArg(controlScheme); //CONTROLS
    msg.addIntArg(controlsEnabled); //CONTROLS ENABLED
    msg.addIntArg(color.r);
    msg.addIntArg(color.g);
    msg.addIntArg(color.b);
    msg.addIntArg(currentImageSet);
    msg.addIntArg(imageNumber);
    client->sendMessage(msg);
    msg.clear();
}
void ofxNERDLabPlayer::startWithParameters(int imageSet, int imageNum, ofColor color, string scoreDescription, int startScore, int control) {
    currentImageSet = imageSet;
    imageNumber = imageNum;
    playerColor = color;
    scoreName = scoreDescription;
    score = startScore;
    controlScheme = control;
    ofxOscMessage msg;
    msg.setAddress("/start");
    msg.addIntArg(tag);
    msg.addIntArg(currentImageSet);
    msg.addIntArg(imageNumber);
    msg.addStringArg(scoreName);
    msg.addIntArg(score);
    msg.addIntArg(playerColor.r);
    msg.addIntArg(playerColor.g);
    msg.addIntArg(playerColor.b);
    msg.addIntArg(controlScheme);
    client->sendMessage(msg);
    msg.clear();
    
}

void ofxNERDLabPlayer::confirm_message(string message) {
    ofxOscMessage msg;
    msg.setAddress("/confirmed");
    msg.addStringArg(message);
    client->sendMessage(msg);
    msg.clear();
}


void ofxNERDLabPlayer::useImageSet(int imageSet){
    currentImageSet = imageSet;
    ofxOscMessage msg;
    msg.setAddress("/set");
    msg.addStringArg("images");
    msg.addIntArg(imageSet);
    client->sendMessage(msg);
    msg.clear();
}

void ofxNERDLabPlayer::setImageNumber(int _imageNumber) {
    imageNumber = _imageNumber;
    ofxOscMessage msg;
    msg.setAddress("/set");
    msg.addStringArg("image");
    msg.addIntArg(_imageNumber);
    client->sendMessage(msg);
    msg.clear();
}

void ofxNERDLabPlayer::setControlsEnabled(bool enabled) {
    ofxOscMessage msg;
    msg.setAddress("/set");
    msg.addStringArg("control_enabled");
    if (enabled) {
        msg.addIntArg(1);
        controlsEnabled = true;
    }
    else {
        msg.addIntArg(0);
        controlsEnabled = false;
    }
    client->sendMessage(msg);
    msg.clear();
//    sendState(OFXNERDLAB_GAME_STATE_PLAYING);
}

void ofxNERDLabPlayer::setColor(ofColor color) {
    ofxOscMessage msg;
    msg.setAddress("/set");
    msg.addStringArg("color");
    int r = color.r;
    int g = color.g;
    int b = color.b;
    
    msg.addIntArg(r);
    msg.addIntArg(g);
    msg.addIntArg(b);
    client->sendMessage(msg);
    msg.clear();
}

void ofxNERDLabPlayer::sendState(int state) {
    ofxOscMessage msg;
    msg.setAddress("/set");
    msg.addStringArg("state");
    msg.addIntArg(state);
    client->sendMessage(msg);
    msg.clear();
}

void ofxNERDLabPlayer::sendReaction(int reaction) {
    ofxOscMessage msg;
    msg.setAddress("/set");
    msg.addStringArg("reaction");
    msg.addIntArg(reaction);
    client->sendMessage(msg);
    msg.clear();
}

void ofxNERDLabPlayer::sendControl(int control) {
    ofxOscMessage msg;
    msg.setAddress("/set");
    msg.addStringArg("control");
    msg.addIntArg(control);
    controlScheme = control;
    client->sendMessage(msg);
    
    msg.clear();

}

void ofxNERDLabPlayer::setScore(int _score) {
    score = _score;
    ofxOscMessage msg;
    msg.setAddress("/set");
    msg.addStringArg("score");
    msg.addIntArg(_score);
    client->sendMessage(msg);
    msg.clear();
}

void ofxNERDLabPlayer::setScoreName(string _name) {
    scoreName = _name;
    ofxOscMessage msg;
    msg.setAddress("/set");
    msg.addStringArg("score_name");
    msg.addStringArg(_name);
    client->sendMessage(msg);
    msg.clear();
}


void ofxNERDLabPlayer::sendTimeUntilNextGame(int seconds) {
    ofxOscMessage msg;
    msg.setAddress("/set");
    msg.addStringArg("wait");
    msg.addIntArg(seconds);
    client->sendMessage(msg);
}

void ofxNERDLabPlayer::sendInGameStatus(string status) {
    ofxOscMessage msg;
    msg.setAddress("/set");
    msg.addStringArg("status");
    msg.addStringArg(status);
    client->sendMessage(msg);
}

void ofxNERDLabPlayer::sendInGameMessage(string message) {
    ofxOscMessage msg;
    msg.setAddress("/set");
    msg.addStringArg("ingamemessage");
    msg.addStringArg(message);
    client->sendMessage(msg);
}

void ofxNERDLabPlayer::sendOutOfGameMessage(string message) {
    cout << "Sending Message to " << ip << endl;
//    client->setup(ip, OFXNERDLAB_CLIENT_PORT);

    ofxOscMessage msg;
    msg.setAddress("/set");
    msg.addStringArg("outgamemessage");
    msg.addStringArg(message);
    cout << "Message Packaged" << endl;
    msg.setRemoteEndpoint(ip, OFXNERDLAB_CLIENT_PORT);
    client->sendMessage(msg);
    msg.clear();
    cout << "Message Sent" << endl;
}
