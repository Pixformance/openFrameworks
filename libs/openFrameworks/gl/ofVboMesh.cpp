#include "ofVboMesh.h"

ofVboMesh::ofVboMesh(){
	usage= GL_STATIC_DRAW;
}

ofVboMesh::ofVboMesh(const ofMesh & mom)
:ofMesh(mom)
{
	usage= GL_STATIC_DRAW;
}

void ofVboMesh::setUsage(int _usage){
	usage = _usage;
}

void ofVboMesh::draw(ofPolyRenderMode drawMode){
	if(!vbo.getIsAllocated()){
		if(getNumVertices()){
			vbo.setVertexData(getVerticesPointer(),getNumVertices(),usage);
		}
		if(getNumColors()){
			vbo.setColorData(getColorsPointer(),getNumColors(),usage);
		}
		if(getNumNormals()){
			vbo.setNormalData(getNormalsPointer(),getNumNormals(),usage);
		}
		if(getNumTexCoords()){
			vbo.setTexCoordData(getTexCoordsPointer(),getNumTexCoords(),usage);
		}
		if(getNumIndices()){
			vbo.setIndexData(getIndexPointer(),getNumIndices(),usage);
		}
		vboNumIndices = getNumIndices();
		vboNumVerts = getNumVertices();
		vboNumColors = getNumColors();
		vboNumTexCoords = getNumTexCoords();
		vboNumNormals = getNumNormals();
	}

	if(haveVertsChanged()){
		if(vboNumVerts!=getNumVertices()){
			vbo.setVertexData(getVerticesPointer(),getNumVertices(),usage);
			vboNumVerts = getNumVertices();
		}else{
			vbo.updateVertexData(getVerticesPointer(),getNumVertices());
		}
	}
	if(haveColorsChanged()){
		if(getNumColors()==0){
			vbo.disableColors();
			vboNumColors = getNumColors();
		}else if(vboNumColors!=getNumColors()){
			vbo.setColorData(getColorsPointer(),getNumColors(),usage);
			vboNumColors = getNumColors();
		}else{
			vbo.enableColors();
			vbo.updateColorData(getColorsPointer(),getNumColors());

		}
	}
	if(haveNormalsChanged()){
		if(getNumNormals()==0){
			vbo.disableNormals();
			vboNumNormals = getNumNormals();
		}else if(vboNumNormals!=getNumNormals()){
			vbo.setNormalData(getNormalsPointer(),getNumNormals(),usage);
			vboNumNormals = getNumNormals();
		}else{
			vbo.enableNormals();
			vbo.updateNormalData(getNormalsPointer(),getNumNormals());
		}
	}
	if(haveTexCoordsChanged()){
		if(getNumTexCoords()==0){
			vbo.disableTexCoords();
			vboNumTexCoords = getNumTexCoords();
		}else if(vboNumTexCoords!=getNumTexCoords()){
			vbo.setTexCoordData(getTexCoordsPointer(),getNumTexCoords(),usage);
			vboNumTexCoords = getNumTexCoords();
		}else{
			vbo.enableTexCoords();
			vbo.updateTexCoordData(getTexCoordsPointer(),getNumTexCoords());
		}
	}
	if(haveIndicesChanged()){
		if(getNumIndices()==0){
			vbo.disableIndices();
			vboNumIndices = getNumIndices();
		}else if(vboNumIndices!=getNumIndices()){
			vbo.setIndexData(getIndexPointer(),getNumIndices(),usage);
			vboNumIndices = getNumIndices();
		}else{
			vbo.enableIndices();
			vbo.updateIndexData(getIndexPointer(),getNumIndices());
		}
	}


	GLuint mode = ofGetGLPrimitiveMode(getMode());
#ifndef TARGET_OPENGLES
	glPushAttrib(GL_POLYGON_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, ofGetGLPolyMode(drawMode));
	if(getNumIndices() && drawMode!=OF_MESH_POINTS){
		vbo.drawElements(mode,getNumIndices());
	}else{
		vbo.draw(mode,0,getNumVertices());
	}
	glPopAttrib();
#else
	if(drawMode == OF_MESH_POINTS){
		vbo.draw(GL_POINTS,0,getNumVertices());
	}else if(drawMode == OF_MESH_WIREFRAME){
		if(getNumIndices()){
			vbo.drawElements(GL_LINES,getNumIndices());
		}else{
			vbo.draw(GL_LINES,0,getNumVertices());
		}
	}else{
		if(getNumIndices() && drawMode!=OF_MESH_POINTS){
			vbo.drawElements(mode,getNumIndices());
		}else{
			vbo.draw(mode,0,getNumVertices());
		}
	}
#endif


}
