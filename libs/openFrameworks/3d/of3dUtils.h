#pragma once
#include "ofVectorMath.h"

void ofDrawAxis(float size);

void ofDrawGrid(float scale = 10.0f, float ticks = 5.0f, bool labels = false, bool x = true, bool y = true, bool z = true);
void ofDrawGridPlane(float scale, float ticks = 5.0f, bool labels = false);

void ofDrawArrow(const ofVec3f& start, const ofVec3f& end, float headSize = 0.05f);