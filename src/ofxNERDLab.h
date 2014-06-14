//
//  ofxNERDLab.h
//  ofxNERDLab_Example
//
//  Created by Clay Ewing on 6/13/14.
//
//

#include "ofMain.h"
//#include "ofxNERDLabPlayer.h"
//#include "ofxNERDLabTeam.h"
#include "ofxOsc.h"
#include "ofxNERDLabEvent.h"
#include "ofxNERDLabClient.h"

#define SERVER_PORT 9000

class ofxNERDLab : public ofThread {
	
    public:
        ofxNERDLab();
        ~ofxNERDLab();
        ofxOscReceiver server;
        vector<ofxNERDLabClient> clients; //IP, Name <- join info... auto add, remove on quit, reset connections with alive?
//could do players with a tag. tag is internal number, keeps incrementing. would have to search for each player to control them
    
        bool allowNewClientsToJoin;
        void loadImageSet(string set);
        void clearClientList();
        void threadedFunction();
        // events

        ofEvent<ofxNERDLabJoinEvent> clientRequest; //internal? still available in case they want to customize?
        ofEvent<ofxNERDLabEvent> clientAlive; //internal?
        ofEvent<ofxNERDLabQuitEvent> playerQuit; //internal? or managed but available?
        ofEvent<ofxNERDLabRotateEvent> receivedRotate;
        ofEvent<ofxNERDLabMoveEvent> receivedMove;
        ofEvent<ofxNERDLabTapEvent> receivedTap;
        ofEvent<ofxNERDLabReleaseEvent> receivedRelease;
        ofEvent<ofxNERDLabAccelerometerEvent> receivedAccelerometer;
        ofEvent<ofxNERDLabAudioInputEvent> receivedAudioInput;
    private:
    
};