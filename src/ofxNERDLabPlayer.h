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

#define OFXNERDLAB_GAME_STATE_WAITING          0
#define OFXNERDLAB_GAME_STATE_PAUSED           1
#define OFXNERDLAB_GAME_STATE_PLAYING          2
#define OFXNERDLAB_GAME_STATE_SHOW_MESSAGE     3

#define OFXNERDLAB_GAME_CONTROL_MOVE           0
#define OFXNERDLAB_GAME_CONTROL_AUDIO          1
#define OFXNERDLAB_GAME_CONTROL_ACCEL          2
#define OFXNERDLAB_GAME_CONTROL_TAP            3
#define OFXNERDLAB_GAME_CONTROL_ROTATE         4


#define OFXNERDLAB_IMAGE_SET_SQUARE            0
#define OFXNERDLAB_IMAGE_SET_ABSTRACT          1
#define OFXNERDLAB_IMAGE_SET_HUMANS            2
#define OFXNERDLAB_IMAGE_SET_TANKS             3



class ofxNERDLabPlayer {
    
public:
    ofxNERDLabPlayer(string name, string ip, int tag);
    ofxOscSender client;
    string name;
    string ip;
    int tag;
    int score;
    bool connected;
    void initialize();
    
    void pause();
    void showMessage();
    void showWaitingScreen();
    void setPlaying(bool playing);
    
    void useMovementAsControl();
    void useAudioInputAsControl();
    void useAccelerometerAsControl();
    void useTapAndHoldAsControl();
    void useRotationAsControl();
    
    void useImageSet(int imageSet);
    
    
    void sendState(int state);
    void sendControl(int control);
    void sendScore(int score);
    void sendGameName(string gameName);
    void sendMessage(string message);
    
    
};
