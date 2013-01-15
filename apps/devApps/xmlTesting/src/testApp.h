#pragma once

#include "ofMain.h"
//#include "ofxXmlSettings.h"

#define NUM_PTS 800


/*
 
 
 addTag() adds a tag by tag + which or by path with an optional value
 setValue() sets a value by tag + which or by path if the tag is present
 getValue() gets a value by tag + which or by path if the tag is present
 clearTagContents() clears the value of a tag AND any children
 removeTag() removes a tag by tag + which or by path
 tagExists() tells whether a tag exists by tag + which or by path
 
 addAttribute() adds an attribute to a tag by tag + which or by path
 removeAttribute() removes an attribute from a tag by tag + which or by path
 setAttribute() sets an attribute on a tag if that tag exists by tag + which or by path
 clearTagAttributes() removes all attibutes from a tag by tag + which or by path
 
 */

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

		ofXml XML;
		ofTrueTypeFont TTF;

		string xmlStructure;
		string message;

		ofPoint dragPts[NUM_PTS];

		int pointCount;
		int lineCount;
		int lastTagNumber;

		float red;
		float green;
		float blue;
};

