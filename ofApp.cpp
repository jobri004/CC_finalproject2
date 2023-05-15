#include "ofApp.h"

#include <functional>


class RectButtonListener {

public:
    // set up callback function type for mouse clicked x,y events
    typedef std::function<bool(int, int)> mouseClickCallbackFunction;

    // constructor -- MUST have all properties set at the start!
    RectButtonListener(ofRectangle& initHitArea, const mouseClickCallbackFunction callbackFunction)
        :
        hitArea(initHitArea), _callbackFunction(callbackFunction), draw(NULL)
    {}
    
    // easy way to run the callback function
    bool operator()(int x, int y) {
        bool result = false;

        // run callback if mouse is inside the rectangle
        if (this->hitArea.inside(x, y))
        {
            result = this->_callbackFunction(x, y);
        }
        return result;
    }

    mouseClickCallbackFunction draw;

    ofRectangle hitArea; // area of button on screen

private:
    mouseClickCallbackFunction _callbackFunction; // function to run
};
// end rectangle button class
typedef struct SliderData {
    SliderData()
        : visible(true), value(0), minValue(0), maxValue(255) {
        // nothing
    }

    bool visible; // is this button visible

    float value; // current value

    float minValue;
    float maxValue;
};

int fadeTicks = 100; // frame to fade out

SliderData sliderData; // will be used for our slider. Global, which isn't ideal -- could store in a queue or vector if desired.


// a list of rectangular areas to click
std::vector<RectButtonListener> rectButtons;

//--------------------------------------------------------------
void ofApp::setup(){

    ofRectangle buttonArea(
        ofGetWidth() / 2, ofGetHeight() / 2,
        ofGetWidth() / 12, ofGetHeight() / 12
    );

    // add a 'button' quickly
    rectButtons.push_back(
        RectButtonListener(
            buttonArea,
            [](int mx, int my) {
                fadeTicks = 200;
                return true;
            }
        )
    );

    buttonArea.setPosition(ofGetWidth() / 10, ofGetHeight() / 10);

    // add a 'button' -- sets up the hit area on screen
    RectButtonListener btn2(
        buttonArea,
        [](int mx, int my) {
            fadeTicks = 50;
            return true;
        }
    );

    glm::vec3 ctr = buttonArea.getCenter();

    // this code is run every time the button is run
    btn2.draw = [ctr](int mx, int my) {
        ofFill(); ofSetColor(255,100,200,100);
        ofDrawCircle(ctr.x, ctr.y, 20);
//        ofDrawCircle(ctr.x + 450, ctr.y - 50, 20);
//        ofDrawCircle(ctr.x-10, ctr.y-3, 50);
        return true;
    };

     //Another draw:
//    [buttonArea, btn2](int x, int y) {
//        if (buttonArea.inside(x, y))
//        {
//            // draw button:
//            ofFill(); ofSetColor(255,0,0,100);
//        }
//        else {
//            // draw button:
//            ofFill(); ofSetColor(255);
//        }
//        ofDrawRectangle(btn2.hitArea);
//        return true;
//    };
    

    rectButtons.push_back(btn2);
    
    RectButtonListener btn3(
        buttonArea,
        [](int mx, int my) {
            fadeTicks = 50;
            return true;
        }
    );
    
    rectButtons.push_back(btn2);
    
    

    // this code is run every time the button is run
    btn3.draw = [ctr](int mx, int my) {
        ofFill(); ofSetColor(255,100,200,100);
        ofDrawCircle(ctr.x * 2, ctr.y, 20);
//        ofDrawCircle(ctr.x + 450, ctr.y - 50, 20);
//        ofDrawCircle(ctr.x-10, ctr.y-3, 50);
        return true;
    };
    
    rectButtons.push_back(btn3);
    
    RectButtonListener btn4(
        buttonArea,
        [](int mx, int my) {
            fadeTicks = 50;
            return true;
        }
    );
    
    

    // this code is run every time the button is run
    btn4.draw = [ctr](int mx, int my) {
        ofFill(); ofSetColor(255,100,200,100);
        ofDrawCircle(ctr.x * 5, ctr.y, 20);
//        ofDrawCircle(ctr.x + 450, ctr.y - 50, 20);
//        ofDrawCircle(ctr.x-10, ctr.y-3, 50);
        return true;
    };
    
    rectButtons.push_back(btn4);
    
    RectButtonListener btn5(
        buttonArea,
        [](int mx, int my) {
            fadeTicks = 50;
            return true;
        }
    );
    
    

    // this code is run every time the button is run
    btn5.draw = [ctr](int mx, int my) {
        ofFill(); ofSetColor(255,100,200,100);
        ofDrawCircle(ctr.x * 6, ctr.y, 20);
//        ofDrawCircle(ctr.x + 450, ctr.y - 50, 20);
//        ofDrawCircle(ctr.x-10, ctr.y-3, 50);
        return true;
    };
    
    rectButtons.push_back(btn5);
    
    sliderData.value = 128;

        // add a 'button' -- sets up the hit area on screen
        RectButtonListener btn6(
            buttonArea,
            [buttonArea](int mx, int my) {

                // scale the height of the click in this hit area to the range of the slider
                sliderData.value = (buttonArea.getMaxY() - my)/buttonArea.getHeight() * sliderData.maxValue;
                
                fadeTicks = 50;
                return true;
            }
        );
    
    buttonArea.setPosition(ofGetWidth() / 2, ofGetHeight() / 1.5);

        // this code is run every time the button is run
        btn6.draw = [buttonArea](int mx, int my) {
            ofNoFill();
            ofSetLineWidth(2);
            ofSetColor(255,255); // slider background
            ofDrawRectangle(buttonArea);
            ofFill();
            ofSetColor(250, 180); // slider background
            float sliderPercent = (sliderData.value - sliderData.minValue) / (float) (sliderData.maxValue - sliderData.minValue);
            float leftCoord = buttonArea.getX();
            float topCoord = buttonArea.getMaxY() - buttonArea.getHeight() * sliderPercent;

            cout << "slider percent: " << sliderPercent << endl;

            //ofNoFill();
            ofSetColor(180, 255);
            ofBeginShape();
            ofVertex(leftCoord, topCoord);
            ofVertex(leftCoord + buttonArea.getWidth(), topCoord);
            ofVertex(buttonArea.getBottomRight());
            ofVertex(buttonArea.getBottomLeft());
            ofEndShape(true);

            return true;
        };

        /*
        // Another draw:
        [buttonArea](int x, int y) {
            if (buttonArea.inside(x, y))
            {
                // draw button:
                ofFill(); ofSetColor(255,0,0,100);
            }
            else {
                // draw button:
                ofFill(); ofSetColor(255);
            }
            ofDrawRectangle(btn2.hitArea);
            return true;
        };
        */

    rectButtons.push_back(btn6);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    if (fadeTicks > 0) {
        fadeTicks = fadeTicks - 1;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(fadeTicks);

    // draw button:
    ofFill(); ofSetColor(100,100,240);

    for (std::vector<RectButtonListener>::const_iterator rectButton = rectButtons.begin(); rectButton != rectButtons.end(); ++rectButton) {
        if ((*rectButton).draw != NULL) {
            (*rectButton).draw(mouseX,mouseY);
        }
        else {
            //default draw
            if ((*rectButton).hitArea.inside(mouseX, mouseY)) {
                ofFill(); ofSetColor(255,100);
            }
            else {
                ofFill(); ofSetColor(255);
            }
            
            ofDrawRectangle((*rectButton).hitArea);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    // go through all callbacks and run them -- if they return true, mouse was inside
    for (std::vector<RectButtonListener>::iterator rectButton = rectButtons.begin(); rectButton != rectButtons.end(); ++rectButton) {
        bool result = (*rectButton)(x,y);

        if (result) cout << "hit one! " << endl;

    }
    cout << "pressed: " << fadeTicks << endl;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
