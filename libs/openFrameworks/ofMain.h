#pragma once

//--------------------------
// utils
#include "utils/ofConstants.h"
#include "utils/ofFileUtils.h"
#include "utils/ofLog.h"
#include "utils/ofSystemUtils.h"
#include "utils/ofThread.h"
#include "utils/ofURLFileLoader.h"
#include "utils/ofUtils.h"
#include "utils/ofXml.h"

//--------------------------
// types
#include "types/ofBaseTypes.h"
#include "types/ofTypes.h"
#include "types/ofColor.h"
#include "types/ofPoint.h"
#include "types/ofRectangle.h"
#include "types/ofParameter.h"
#include "types/ofParameterGroup.h"

//--------------------------
// math
#include "math/ofMath.h"
#include "math/ofVectorMath.h"

//--------------------------
// communication
#if !defined( TARGET_OF_IOS ) & !defined(TARGET_ANDROID)
	#include "communication/ofSerial.h"
	#include "communication/ofArduino.h"
#endif

//--------------------------
// gl
#include "gl/ofFbo.h"
#include "gl/ofGLRenderer.h"
#include "gl/ofGLUtils.h"
#include "gl/ofLight.h"
#include "gl/ofMaterial.h"
#include "gl/ofShader.h"
#include "gl/ofTexture.h"
#include "gl/ofVbo.h"
#include "gl/ofVboMesh.h"
#include "gl/ofGLProgrammableRenderer.h"
#include "gl/ofGLRenderer.h"

//--------------------------
// graphics
#if !defined( TARGET_OF_IOS ) & !defined(TARGET_ANDROID)
#include "graphics/ofCairoRenderer.h"
#endif
#include "graphics/ofGraphics.h"
#include "graphics/ofImage.h"
#include "graphics/ofPath.h"
#include "graphics/ofPixels.h"
#include "graphics/ofPolyline.h"
#include "graphics/ofRendererCollection.h"
#include "graphics/ofTessellator.h"
#include "graphics/ofTrueTypeFont.h"

//--------------------------
// app
#include "app/ofBaseApp.h"
#include "app/ofAppRunner.h"

//--------------------------
// audio
#include "sound/ofSoundStream.h"
#include "sound/ofSoundPlayer.h"

//--------------------------
// video
#include "video/ofVideoGrabber.h"
#include "video/ofVideoPlayer.h"

//--------------------------
// events
#include "events/ofEvents.h"

//--------------------------
// 3d
#include "3d/of3dUtils.h"
#include "3d/ofCamera.h"
#include "3d/ofEasyCam.h"
#include "3d/ofMesh.h"
#include "3d/ofNode.h"

