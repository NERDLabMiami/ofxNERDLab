//
//  Ball.h
//  ofxNERDLab_Example
//
// this is pretty much the same ball code in the iOS touch and accel example... I'm lazy :)
//

#include "ofMain.h"

#pragma once

#define BOUNCE_FACTOR			0.7
#define ACCELEROMETER_FORCE		0.02
#define START_RADIUS			20


class Ball{
    
public:
    ofPoint pos;
    ofPoint vel;
    ofColor col;
    ofColor touchCol;
    float radius;
    
    //----------------------------------------------------------------
    void init() {
        pos.set(ofRandomWidth(), ofRandomHeight(), 0);
        vel.set(ofRandomf(), ofRandomf(), 0);
		radius = 20;
        float val1 = ofRandom( 30, 100 );
        float val2 = ofRandom( 30, 100 );
        float val3 = ofRandom( 30, 100 );
        col.set( val1, val2, val3, 120 );
    }
	
    //----------------------------------------------------------------
    void update() {
		cout << radius << endl;
        // add vel to pos
        pos += vel;
		
        // check boundaries
        if(pos.x < radius) {
            pos.x = radius;
            vel.x *= -BOUNCE_FACTOR;
        } else if(pos.x >= ofGetWidth() - radius) {
            pos.x = ofGetWidth() - radius;
            vel.x *= -BOUNCE_FACTOR;
        }
		
        if(pos.y < radius) {
            pos.y = radius;
            vel.y *= -BOUNCE_FACTOR;
        } else if(pos.y >= ofGetHeight() - radius) {
            pos.y = ofGetHeight() - radius;
            vel.y *= -BOUNCE_FACTOR;
        }
    }
	
    //----------------------------------------------------------------
    void draw() {
        ofSetColor(col);
        ofCircle(pos.x, pos.y, radius);
    }
	
    //----------------------------------------------------------------
    void drift(int x, int y) {
        vel.x -= (x * ACCELEROMETER_FORCE);
        vel.y -= (y * ACCELEROMETER_FORCE);
    }
    
    void changecolor() {
        float val1 = ofRandom( 30, 100 );
        float val2 = ofRandom( 30, 100 );
        float val3 = ofRandom( 30, 100 );
        col.set( val1, val2, val3, 120 );

    }
    
    void grow(float amt) {
        radius += amt;
    }
    
    
    
};
