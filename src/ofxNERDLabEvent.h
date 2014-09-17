//
//  ofxNERDLabEvent.h
//  ofxNERDLab_Example
//
//  Created by Clay Ewing on 6/13/14.
//
//

#include "ofMain.h"

class ofxNERDLabEvent {
    public:
    string ip;
};

class ofxNERDLabRollCalled {
    public:
    int players;
    float time;
};

class ofxNERDLabJoinEvent : public ofxNERDLabEvent {
    public:
    string name;
    int team_id;
    int player_id;

};

class ofxNERDLabQuitEvent : public ofxNERDLabEvent {
    public:
    int id;
};

class ofxNERDLabMoveEvent : public ofxNERDLabEvent {
    public:
    int id;
    float x;
    float y;
};

class ofxNERDLabRotateEvent : public ofxNERDLabEvent {
    public:
    int id;
    float amount;
};


class ofxNERDLabTapEvent : public ofxNERDLabEvent {
    public:
    int id;
};

class ofxNERDLabReleaseEvent : public ofxNERDLabEvent {
    public:
    int id;
    float time;
    
};

class ofxNERDLabAccelerometerEvent : public ofxNERDLabEvent {
    public:
    int id;
    float x;
    float y;
    float z;
};

class ofxNERDLabAudioInputEvent : public ofxNERDLabEvent {
    public:
    int id;
    float amplitude;
};