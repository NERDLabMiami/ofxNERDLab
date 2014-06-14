//
//  ofxNERDLabClient.h
//  ofxNERDLab_Example
//
//  Created by Clay Ewing on 6/13/14.
//
//

#include "ofMain.h"

class ofxNERDLabClient {
    public:
        ofxNERDLabClient(string ip, string name);
        string name;
        string ip;
        friend bool operator== ( const ofxNERDLabClient &n1, const ofxNERDLabClient &n2);
};

