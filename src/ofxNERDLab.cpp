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
    startThread(true);
    allowNewClientsToJoin = true;
    currentPlayerRollCall = 0;
    nextRollCall = 0;
}

ofxNERDLab::~ofxNERDLab() {
    stopThread();
}
void ofxNERDLab::setInProgress(bool inProgress) {
    allowNewClientsToJoin = !inProgress;
}

// the thread function
void ofxNERDLab::clearClientList() {
    clients.clear();
}

vector<ofImage> ofxNERDLab::loadImageSet(string set) {
    vector<ofImage> images;
    ofDirectory dir(set);
    dir.allowExt("png");
    dir.sort();
    dir.listDir();
    
    cout << "cleared current images" << endl;
    //imageCounter = 0;
    
    for (int i = 0; i < dir.numFiles(); i++) {
        ofImage img;
        img.loadImage(dir.getFile(i));
        images.push_back(img);
        cout << "creating new image with " << i << endl;
    }
    return images;
}

vector<ofColor> ofxNERDLab::colors() {
    vector<ofColor> colors;
    colors.push_back(ofColor::red);
    colors.push_back(ofColor::blue);
    colors.push_back(ofColor::green);
    colors.push_back(ofColor::white);
    colors.push_back(ofColor::turquoise);
    colors.push_back(ofColor::yellow);
    colors.push_back(ofColor::pink);
    colors.push_back(ofColor::orange);
    colors.push_back(ofColor::olive);
    colors.push_back(ofColor::tan);
    colors.push_back(ofColor::salmon);
    colors.push_back(ofColor::darkRed);
    colors.push_back(ofColor::gold);
    colors.push_back(ofColor::lightBlue);
    colors.push_back(ofColor::lightGreen);
    colors.push_back(ofColor::lightYellow);

    return colors;
}
void ofxNERDLab::rollcall() {
    
    if (ofGetElapsedTimef() > nextRollCall && currentPlayerRollCall < players.size()) {
       // cout << "CURRENT PLAYER ROLL CALL " << currentPlayerRollCall << " OF " << players.size();
        players[currentPlayerRollCall].vibrate();
        ofxNERDLabJoinEvent e;
        e.name = players[currentPlayerRollCall].name;
        e.player_id = currentPlayerRollCall;
        e.team_id = players[e.player_id].tag;
        ofNotifyEvent(playerCalled, e);
        currentPlayerRollCall++;
        nextRollCall = ofGetElapsedTimef() + 1;
    }
    else if (ofGetElapsedTimef() > nextRollCall) {
       // cout << "time elapsed but current player roll call is greater than or equal to amount of players" << endl;
        currentPlayerRollCall = 0;
        ofxNERDLabRollCalled e;
        e.time = ofGetElapsedTimef();
        e.players = players.size();
        ofNotifyEvent(rollCallEnded, e);
    }
    else {
        //cout << "neither rollcall conditions met. elapsed time: " << ofGetElapsedTimef() << " nextRollCall: " << nextRollCall << " current player: " << currentPlayerRollCall << endl;
    }

}
void ofxNERDLab::createFakePlayer() {
    ofxNERDLabPlayer newPlayer = ofxNERDLabPlayer("Fake Player No. " + ofToString(players.size()+1), "127.0.0.1", players.size());
    newPlayer.initialize();
    cout << "Creating Player with Tag " << newPlayer.tag << endl;
    players.push_back(newPlayer);
    ofxNERDLabJoinEvent e;
    e.player_id = newPlayer.tag;
    ofNotifyEvent(clientRequest, e);
}

void ofxNERDLab::newTeam(vector<int> team) {
    teams.push_back(team);
}

void ofxNERDLab::resetTeams() {
    teams.clear();
}
string ofxNERDLab::teamMembers(int teamNum) {
    string team;
    for (int i = 0; i < teams[teamNum].size(); i++) {
        team += players[teams[teamNum][i]].name + "\n";
    }
    return team;
}
void ofxNERDLab::setTeamImageNumber(int teamNum, int imageNum) {
    for (int i = 0; i < teams[teamNum].size(); i++) {
        players[teams[teamNum][i]].setImageNumber(imageNum);
    }
}
void ofxNERDLab::setTeamId(int teamNum) {
    for (int i = 0; i < teams[teamNum].size(); i++) {
        players[teams[teamNum][i]].setId();
    }
    
}

void ofxNERDLab::setTeamColor(int teamNum, ofColor color) {
    for (int i = 0; i < teams[teamNum].size(); i++) {
        players[teams[teamNum][i]].setColor(color);
    }

}

void ofxNERDLab::sendTeamState(int teamNum, int state) {
    for (int i = 0; i < teams[teamNum].size(); i++) {
        players[teams[teamNum][i]].sendState(state);
    }

}

void ofxNERDLab::sendTeamReaction(int teamNum, int reaction) {
    for (int i = 0; i < teams[teamNum].size(); i++) {
        players[teams[teamNum][i]].sendReaction(reaction);
    }

}

void ofxNERDLab::sendTeamInGameStatus(int teamNum, string status) {
    for (int i = 0; i < teams[teamNum].size(); i++) {
        players[teams[teamNum][i]].sendInGameStatus(status);
    }

}
void ofxNERDLab::sendTeamInGameMessage(int teamNum, string message) {
    for (int i = 0; i < teams[teamNum].size(); i++) {
        players[teams[teamNum][i]].sendInGameMessage(message);
    }

}

void ofxNERDLab::sendTeamOutOfGameMessage(int teamNum, string message) {
    for (int i = 0; i < teams[teamNum].size(); i++) {
        players[teams[teamNum][i]].sendOutOfGameMessage(message);
    }
    
}

void ofxNERDLab::setTeamScore(int teamNum, int _score) {
    for (int i = 0; i < teams[teamNum].size(); i++) {
        players[teams[teamNum][i]].setScore(_score);
    }

}
void ofxNERDLab::setTeamControlsEnabled(int teamNum, bool enabled) {
    for (int i = 0; i < teams[teamNum].size(); i++) {
        players[teams[teamNum][i]].setControlsEnabled(enabled);
    }
    
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
                if (allowNewClientsToJoin) {
                    ofxNERDLabJoinEvent e;
                    e.ip = ip;
                    e.name = msg.getArgAsString(0);
                    //this checks against duplicate IPs. Fake players bypass this.
                    if (std::find(clients.begin(), clients.end(), ofxNERDLabClient(ip, e.name)) == clients.end()) {
                        //NOT REGISTERED, ADD TO LIST OF CLIENTS
                        
                        clients.push_back(ofxNERDLabClient(ip, e.name));
                        ofxNERDLabPlayer newPlayer = ofxNERDLabPlayer(e.name, ip, players.size());
                        newPlayer.initialize();
                        players.push_back(newPlayer);
                        e.player_id =newPlayer.tag;
                        cout << "Assigning Tag : " << newPlayer.tag << endl;
                        ofNotifyEvent(clientRequest, e);

                    }
                    else {
                        //trying to rejoin
                        cout << "Got a rejoin" << endl;
                        for (int i = 0; i < players.size(); i++) {
                            if (ip == players[i].ip) {
                                e.player_id = players[i].tag;
                                cout << "matched ip internally, sending join notification";
                                ofNotifyEvent(clientRequest, e);
                                break;
                            }
                                
                        }
                    }
                    
                }
            }
            
            //ALIVE
            
            if (msg.getAddress() == "/alive") {
                ofxNERDLabEvent e;
                e.ip = ip;
                ofNotifyEvent(clientAlive, e);

            }
            if (msg.getAddress() == "/confirm") {
                ofxNERDLabMessageEvent e;
                e.ip = ip;
                e.player_id = msg.getArgAsInt32(0);
                ofNotifyEvent(clientConfirm, e);
            }
            
            if (msg.getAddress() == "/hello") {
                ofxNERDLabJoinEvent e;
                cout << "Got hello" << endl;
                e.ip = ip;
                for (int i = 0; i < clients.size(); i++) {
                    if(ip == clients[i].ip) {
                        //found the client
                        cout << "Found client" << endl;
                        e.name = clients[i].name;
                        e.player_id = i;
                        ofNotifyEvent(clientRejoin, e);
                        break;
                    }
                }
                
            }
            
            //QUIT
            if (msg.getAddress() == "/quit") {
                ofxNERDLabQuitEvent e;
                e.ip = ip;
                e.id = msg.getArgAsInt32(0);
                cout << "Got Quit Message" << endl;
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
            
            if (msg.getAddress() == "/shake") {
                ofxNERDLabAccelerometerEvent e;
                e.ip = ip;
                e.id = msg.getArgAsInt32(0);
                ofNotifyEvent(receivedShake, e);
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