#pragma once

#include "ofMain.h"
#include "ofxNERDLab.h"
#include "ofxNERDLabPlayer.h"

#include "Ball.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    

        ofxNERDLab *nerdlab;
        vector<ofxNERDLabPlayer> players;
        vector<Ball> balls;

    /* ofxNERDLab events */

        void move(ofxNERDLabMoveEvent &e);
        void accelerometer(ofxNERDLabAccelerometerEvent &e);
        void tap(ofxNERDLabTapEvent &e);
        void release(ofxNERDLabReleaseEvent &e);
        void audio(ofxNERDLabAudioInputEvent &e);
    
};
