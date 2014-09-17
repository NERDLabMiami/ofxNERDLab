//
//  ofxNERDLabPlayer.h
//  ofxNERDLab_Example
//
//  Created by Clay Ewing on 6/13/14.
//
//

#include "ofMain.h"
#include "ofxOsc.h"

#define OFXNERDLAB_CLIENT_PORT 9001

#define OFXNERDLAB_GAME_STATE_WAITING               0
#define OFXNERDLAB_GAME_STATE_PAUSED                1
#define OFXNERDLAB_GAME_STATE_PLAYING               2
#define OFXNERDLAB_GAME_STATE_SHOW_MESSAGE          3
#define OFXNERDLAB_GAME_STATE_IN_PROGRESS_CANT_JOIN 4
#define OFXNERDLAB_GAME_STATE_ROLL_CALL             5
#define OFXNERDLAB_GAME_STATE_ASSIGNING_CONTROLS    6
#define OFXNERDLAB_GAME_STATE_GAME_OVER             7


#define OFXNERDLAB_GAME_CONTROL_MOVE                0
#define OFXNERDLAB_GAME_CONTROL_AUDIO               1
#define OFXNERDLAB_GAME_CONTROL_ACCEL               2
#define OFXNERDLAB_GAME_CONTROL_TAP                 3
#define OFXNERDLAB_GAME_CONTROL_ROTATE              4
#define OFXNERDLAB_GAME_CONTROL_ROTATE_RELEASE      5

#define OFXNERDLAB_REACTION_PULSE                   0
#define OFXNERDLAB_REACTION_ROLL_CALL               1

#define OFXNERDLAB_IMAGE_SET_SQUARE                 0
#define OFXNERDLAB_IMAGE_SET_ABSTRACT               1
#define OFXNERDLAB_IMAGE_SET_HUMANS                 2
#define OFXNERDLAB_IMAGE_SET_TANKS                  3
#define OFXNERDLAB_IMAGE_SET_SUBMARINES             4



class ofxNERDLabPlayer {
    
public:
    ofxNERDLabPlayer(string name, string ip, int tag);
    ofxOscSender *client;
    string name;
    string ip;
    bool controlsEnabled;
    int controlScheme;
    int tag;
    int score;
    string scoreName;
    int imageNumber;
    ofPoint lastPoint;
    bool connected;
    void initialize();
    
    void pause();
    void showMessage();
    void showWaitingScreen();
    void showGameInProgress();
    void rollCall();
    void setControlsEnabled(bool enabled);
    
    void useMovementAsControl();
    void useAudioInputAsControl();
    void useAccelerometerAsControl();
    void useTapAndHoldAsControl();
    void useRotationAsControl();
    void useRotationAndReleaseAsControl();
    
    void pulse();
    void vibrate();
    
    void useImageSet(int imageSet);
    void setImageNumber(int imageNum);
    void setId();
    void setColor(ofColor color);
    void sendState(int state);
    void sendReaction(int reaction);
    void sendControl(int control);
    void sendInGameStatus(string status);
    void sendInGameMessage(string message);
    void sendOutOfGameMessage(string message);
    void sendTimeUntilNextGame(int seconds);
    void setScore(int _score);
    void setScoreName(string _name);
    void resend(int id, string name, int gameState, ofColor color);
    
};
