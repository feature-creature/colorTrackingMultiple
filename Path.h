#pragma once

#include "ofMain.h"

class Path{
    public:
        //Path();


        void setup();
        void draw();
        void update();

        void addLocation(int x, int y);


        ofColor targetC;
        deque <ofPoint> verts;
};
