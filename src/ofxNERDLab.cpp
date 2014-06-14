//
//  ofxNERDLab.cpp
//  ofxNERDLab_Example
//
//  Created by Clay Ewing on 6/13/14.
//
//

#include "ofxNERDLab.h"

ofxNERDLab::ofxNERDLab() {
    server.setup(SERVER_PORT);
    startThread(true, false);
}

ofxNERDLab::~ofxNERDLab() {
    stopThread();
}

// the thread function
void ofxNERDLab::clearClientList() {
    clients.clear();
}

void ofxNERDLab::threadedFunction() {
    
    // start
    
    while(isThreadRunning()) {
        //check all messages
        if(server.hasWaitingMessages()) {
            lock();
            ofxOscMessage msg;
            server.getNextMessage(&msg);
            string ip = msg.getRemoteIp();
            //JOIN

            if (msg.getAddress() == "/join") {
                ofxNERDLabJoinEvent e;
                e.ip = ip;
                e.name = msg.getArgAsString(0);
                
                if (std::find(clients.begin(), clients.end(), ofxNERDLabClient(ip, e.name)) == clients.end()) {
                    //NOT REGISTERED, ADD TO LIST OF CLIENTS
                    clients.push_back(ofxNERDLabClient(ip, e.name));
                }
                
                ofNotifyEvent(clientRequest, e);
            }
            
            //ALIVE
            
            if (msg.getAddress() == "/alive") {
                ofxNERDLabEvent e;
                e.ip = ip;
                ofNotifyEvent(clientAlive, e);

            }
            
            //QUIT
            if (msg.getAddress() == "/quit") {
                ofxNERDLabQuitEvent e;
                e.ip = ip;
                e.id = msg.getArgAsInt32(0);
                ofNotifyEvent(playerQuit, e);
                
            }
            
            //MOVE
            if (msg.getAddress() == "/move") {
                ofxNERDLabMoveEvent e;
                e.ip = ip;
                e.id = msg.getArgAsInt32(0);
                e.x = msg.getArgAsFloat(1);
                e.y = msg.getArgAsFloat(2);
                ofNotifyEvent(receivedMove, e);
            }
            
            if (msg.getAddress() == "/rotate") {
                
                ofxNERDLabRotateEvent e;
                e.ip = ip;
                e.id = msg.getArgAsInt32(0);
                e.amount = msg.getArgAsFloat(1);
                ofNotifyEvent(receivedRotate, e);

            }
            //TAP
            if (msg.getAddress() == "/tap") {
                ofxNERDLabTapEvent e;
                e.ip = ip;
                e.id = msg.getArgAsInt32(0);
                ofNotifyEvent(receivedTap, e);
            }
            
            //RELEASE
            if (msg.getAddress() == "/release") {
                ofxNERDLabReleaseEvent e;
                e.ip = ip;
                e.id = msg.getArgAsInt32(0);
                e.time = msg.getArgAsFloat(1);
                ofNotifyEvent(receivedRelease, e);
            }
            
            //ACCELEROMETER
            if (msg.getAddress() == "/accel") {
                ofxNERDLabAccelerometerEvent e;
                e.ip = ip;
                e.id = msg.getArgAsInt32(0);
                e.x = msg.getArgAsFloat(1);
                e.y = msg.getArgAsFloat(2);
                ofNotifyEvent(receivedAccelerometer, e);
            }
            
            //AUDIO INPUT
            if (msg.getAddress() == "/sound") {
                //sound/id/power
                ofxNERDLabAudioInputEvent e;
                e.ip = ip;
                e.id = msg.getArgAsInt32(0);
                e.amplitude = msg.getArgAsFloat(1);
                ofNotifyEvent(receivedAudioInput, e);
            }

            
            unlock();
        }
    }
}