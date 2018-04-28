#include "ofApp.h"

//---------------------
void ofApp::setup(){
    
    // initialize video source
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.initGrabber(640,480);

    // initialize target for editing
    target = 0;

    // initialize target colors to track
    targetColors.clear();
    for(int i = 0; i < 8; i++){
        // declare and initialize local, temporary color object 
        ofColor tempColor(255, 182, 193);
        // store in global vector
        targetColors.push_back(tempColor);
    }

    // initialize target thresholds for target colors
    targetThresholds.clear();
    for(int i = 0; i < 8; i++){
        // declare local, temporary color object
        float tempThreshold;
        // initialize
        tempThreshold = 2;
        // store in global vector
        targetThresholds.push_back(tempThreshold);
    } 

    // initialize target tracking paths
    targetPaths.clear();
    for(int i = 0; i < 8; i++){
        // declare a local, temporary path object
        Path tempPath;
        // store in global vector
        targetPaths.push_back(tempPath);
    }
}

//---------------------
void ofApp::update(){
    
    // update current frame data from video source
    vidGrabber.update();
    
    // if current frame data is received and new
    if (vidGrabber.isFrameNew()){


        // iterate through every pixel in a designated area in the current frame
        // row by column - width by height - left to right, top to bottom
        // to store/not store the current pixel's data
        // repeat for each color to track
        // ?? refactor with big O 
        int w = vidGrabber.getWidth();
        int h = vidGrabber.getHeight();
        int b = 8;
        for (int i = 0; i < b; i++){
        
            // clear the previous frame's data 
            // from the 5 global variables that store 
            // the current count of all pixels which have color 'close' to the target color, 
            // the current sums of those pixel's x and y coordinates, and
            // the subsequent current approximate average location (x and y coordinates)
            // of the target color in the frame.
            count = 0;
            sumCloseColorsX = 0;
            sumCloseColorsY = 0;
            closestColorX = 0;
            closestColorY = 0;

            //for (int y=i*(w/b); y<(i+1)*(w/b); y++) {
            //
            // for entire frame
            for (int y=0; y<h; y++) {
                for (int x=0; x<w; x++) {
                
                    // locally store the color data of the current pixel at x,y location
                    ofColor colorAtXY = vidGrabber.getPixels().getColor(x, y);
                    float rAtXY = colorAtXY.r;
                    float gAtXY = colorAtXY.g;
                    float bAtXY = colorAtXY.b;
                

                    // test current pixel data against color targets
                    // calculate color distance between
                    // the current pixel's RGB color values 
                    // and the target color's RGB values
                    // !!ofDist calculates 3D distance between points
                    // via the pythagorean theorem, but instead of traditional x,y,z distance
                    // we calculate r,g,b distance in the same way.
                    // ofDist returns a float
                    float colorDistance = ofDist(rAtXY, gAtXY, bAtXY, targetColors[i].r, targetColors[i].g, targetColors[i].b);
                
                    // if distance between the two RGB colors
                    // is shorter than the current distance threshhold 
                    // then increase the global count of pixels which have 'close' color by 1
                    // and add the current pixel's x and y coordinates to 
                    // the globally stored sum of x and y coordinates 
                    if(colorDistance < targetThresholds[i]){
                        count++;
                        sumCloseColorsX+= x;
                        sumCloseColorsY+= y;
                    }
                
                }
            }
        
        
            // if pixels with 'close' color have been tracked
            // determine the approximate average coordinates of the target color
            // within the current frame.
            // then send the coordinates to the instance of the path class
            // To reduce data noise, do not update the average if it equals 0;
            if (count>0) {
                if( sumCloseColorsX / count > 10 && sumCloseColorsY / count > 10){
                    closestColorX = sumCloseColorsX / count;
                    closestColorY = sumCloseColorsY / count;
                    targetPaths[i].addLocation(closestColorX,closestColorY);
                }
            }
        }
    }
}

//---------------------
void ofApp::draw(){
    ofBackground(0);
    
    // show data
    if(sourceVisible == true){
        // show video 
        vidGrabber.draw(0,0);
        // write the current target over the video feed
        ofDrawBitmapString("color: ", 25, 25);
        ofDrawBitmapString(target, 75, 25);
        // write the current distance threshold value over the video feed
        ofDrawBitmapString((int)targetColors[target].r, 25, 50);
        ofDrawBitmapString((int)targetColors[target].g, 25, 75);
        ofDrawBitmapString((int)targetColors[target].b, 25, 100);
        ofDrawBitmapString(targetThresholds[target], 25, 125);
    }

    // draw each tracked color path 
    for(int i = 0; i < 8; i++){

        // draw paths of the targeted colors
        targetPaths[i].draw();
        // draw a circle at the current approximate averaged location of the target color
        if(!targetPaths[i].verts.empty()){
            ofPushStyle();
            ofNoFill();
            ofDrawEllipse(targetPaths[i].verts[0].x,targetPaths[i].verts[0].y,25,25);
            ofPopStyle();
        }
    }
}

//---------------------
// select the target color via mouse click
// (color of pixel under the mouse's x,y current coordinates) 
void ofApp::mousePressed(int x, int y, int button){
    ofColor tempColor = vidGrabber.getPixels().getColor(x, y);
    targetColors[target].r = tempColor.r;
    targetColors[target].g = tempColor.g;
    targetColors[target].b = tempColor.b;
}

//-----------------------
// increase or decrease the distance threshold
// determining 'closeness'
// between a pixel's color and the target color
void ofApp::keyPressed(int key){
    //UP ARROW
    if (key == OF_KEY_UP) targetThresholds[target]+=1;
    //DOWN ARROW - prevent negatives
    else if (key==OF_KEY_DOWN && targetThresholds[target] > 0) targetThresholds[target]-=1;
    // show or hide the video source
    else if (key=='v')sourceVisible=!sourceVisible;

    else if(key == '0') target = 0;
    else if(key == '1') target = 1;
    else if(key == '2') target = 2;
    else if(key == '3') target = 3;
    else if(key == '4') target = 4;
    else if(key == '5') target = 5;
    else if(key == '6') target = 6;
    else if(key == '7') target = 7;
}
