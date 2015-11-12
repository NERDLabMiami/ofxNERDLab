//
//  ofxNERDLab.h
//  ofxNERDLab_Example
//
//  Created by Clay Ewing on 6/13/14.
//
//

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxNERDLabEvent.h"
#include "ofxNERDLabClient.h"
#include "ofxNERDLabPlayer.h"
//#include "ofxNERDLabTeam.h"

#define SERVER_PORT 9000

class ofxNERDLab : public ofThread {
	
    public:
        ofxNERDLab();
        ~ofxNERDLab();
        ofxOscReceiver server;
        vector<ofxNERDLabClient> clients; //IP, Name <- join info... auto add, remove on quit, reset connections with alive?
//could do players with a tag. tag is internal number, keeps incrementing. would have to search for each player to control them
    
        bool allowNewClientsToJoin;
        vector<ofImage> loadImageSet(string set);
        vector<ofColor> colors();
        void rollcall();
        void clearClientList();
        void threadedFunction();
        void setInProgress(bool inProgress);
        void createFakePlayer();
        void newTeam(vector<int> team);
        void resetTeams();
    
        vector<ofxNERDLabPlayer> players;
        vector< vector<int> > teams;
    
    
    
        void setTeamImageNumber(int teamNum, int imageNum);
        void setTeamId(int teamNum);
        void setTeamColor(int teamNum, ofColor color);
        void sendTeamState(int teamNum, int state);
        void sendTeamReaction(int teamNum, int reaction);
        void sendTeamInGameStatus(int teamNum, string status);
        void sendTeamInGameMessage(int teamNum, string message);
        void sendTeamOutOfGameMessage(int teamNum, string message);
        void setTeamScore(int teamNum, int _score);
        void setTeamControlsEnabled(int teamNum, bool enabled);
        string teamMembers(int teamNum);
    
        // events

        ofEvent<ofxNERDLabJoinEvent> clientRequest; //internal? still available in case they want to customize?
        ofEvent<ofxNERDLabEvent> clientAlive; //internal?
        ofEvent<ofxNERDLabMessageEvent> clientConfirm;
        ofEvent<ofxNERDLabJoinEvent> clientRejoin;
        ofEvent<ofxNERDLabQuitEvent> playerQuit; //internal? or managed but available?
    
        ofEvent<ofxNERDLabRollCalled> rollCallEnded;
        ofEvent<ofxNERDLabJoinEvent> playerCalled;
    
        ofEvent<ofxNERDLabRotateEvent> receivedRotate;
        ofEvent<ofxNERDLabMoveEvent> receivedMove;
        ofEvent<ofxNERDLabTapEvent> receivedTap;
        ofEvent<ofxNERDLabReleaseEvent> receivedRelease;
        ofEvent<ofxNERDLabAccelerometerEvent> receivedAccelerometer;
        ofEvent<ofxNERDLabAccelerometerEvent> receivedShake;
        ofEvent<ofxNERDLabAudioInputEvent> receivedAudioInput;
    private:
    float nextRollCall;
    int currentPlayerRollCall;
};