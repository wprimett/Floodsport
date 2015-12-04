#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"

int main() {
	
    //ofAppGlutWindow window;
	ofSetupOpenGL(1280, 980, OF_WINDOW);
	ofRunApp(new ofApp());
	
}
