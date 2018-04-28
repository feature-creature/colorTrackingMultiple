#include "Path.h"

void Path::setup(){


}

void Path::update(){

}

void Path::draw(){
    ofSetLineWidth(2);
    // draw line between points, excluding the last point
    if(verts.size() >= 2){
        for(int i = 0; i < verts.size()-2; i++){
            ofPushStyle();
            ofSetColor(255, ofMap(i,0,50,255,0));
            ofDrawLine(verts[i],verts[i+1]);
            ofPopStyle();
        }
    }
}

void Path::addLocation(int x, int y){
    ofPoint loc = ofPoint(x,y);

    if(verts.size() >= 50){
        verts.pop_back();
    }
    verts.push_front(loc);

}
