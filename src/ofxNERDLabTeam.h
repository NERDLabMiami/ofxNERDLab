//
//  ofxNERDLabTeam.h
//  ofxNERDLab_Example
//
//  Created by Clay Ewing on 6/13/14.
//
//

#include "ofxNERDLabPlayer.h"


class ofxNERDLabTeam {
    
public:

//    ofxNERDLabTeam(vector<ofxNERDLabPlayer> people);
    int score;
    vector<ofxNERDLabPlayer> *players;
    void setScore(int _score);
    void setScoreName(string _name);

};
