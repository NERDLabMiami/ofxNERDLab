//
//  ofxNERDLabClient.cpp
//  ofxNERDLab_Example
//
//  Created by Clay Ewing on 6/13/14.
//
//

#include "ofxNERDLabClient.h"

ofxNERDLabClient::ofxNERDLabClient(string _ip, string _name) {
    ip = _ip;
    name = _name;
}

bool operator== ( const ofxNERDLabClient &n1, const ofxNERDLabClient &n2)
{
    return n1.ip == n2.ip;
}