// Example 3. Finding the Brightest Pixel in an Image

#pragma once
#include "ofMain.h"
#include "Path.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    ofVideoGrabber vidGrabber;
    void mousePressed(int x, int y, int button);
    void keyPressed(int key);

    int count;
    int sumCloseColorsX, sumCloseColorsY;
    int closestColorX, closestColorY;

    int target;

    bool sourceVisible = true;

    vector<ofColor> targetColors;
    vector<float> targetThresholds;
    vector<Path> targetPaths;
};
