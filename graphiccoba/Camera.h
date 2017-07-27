#ifndef _H_CAMERA_H_
#define _H_CAMERA_H_

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

using namespace glm;

class Camera {

public:
	Camera();
	~Camera();

	void init(int screenWidth, int screenHeight);
	void update();

	bool isObjectInCameraView(const vec2& position, const vec2& dimension);

	//setter
	void setPosition(vec2& position) { c_position = position;  isCameraNeedUpdate = true; }
	void setscale(float scale) { this->c_scale = scale; isCameraNeedUpdate = true; }

	//getter
	vec2 getPosition() { return c_position; }
	float getScale() { return c_scale; }
	mat4 getCameraMatrix() { return c_cameramatrix; }

	vec2 convertWorldCoordstoScreenCoords(vec2 screenCoords);

private:
	int c_screenWidth;
	int c_screenHeight;
	bool isCameraNeedUpdate;
	float c_scale;
	vec2 c_position;
	mat4 c_cameramatrix;
	mat4 c_orthomatrix;
};

#endif // !_H_CAMERA_H_

