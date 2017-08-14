#include "Camera.h"

namespace EngineProject2D {
	Camera::Camera() :
		c_position(0.0f, 0.0f),
		c_cameramatrix(1.0f),
		c_orthomatrix(1.0f), c_scale(1.0f),
		isCameraNeedUpdate(true),
		c_screenWidth(800),
		c_screenHeight(600)
	{}

	Camera::~Camera() {}

	void Camera::init(int screenWidth, int screenHeight) {
		c_screenWidth = screenWidth;
		c_screenHeight = screenHeight;
		c_orthomatrix = ortho(-(float)screenWidth/2, (float)screenWidth/2, -(float)screenHeight / 2, (float)screenHeight/2);
	}

	void Camera::update() {
		if (isCameraNeedUpdate) {
			vec3 transl(c_position.x, c_position.y, 0.0f);
			c_cameramatrix = glm::translate(c_orthomatrix, transl);
			vec3 scale(c_scale, c_scale, 0.0f);
			c_cameramatrix = glm::scale(mat4(1.0f), scale) * c_cameramatrix;
			isCameraNeedUpdate = false;
		}
	}

	bool Camera::isObjectInCameraView(const vec2& position, const vec2& dimension) {
		vec2 scaledScreenDimension = vec2(c_screenWidth, c_screenHeight) / c_scale;

		const float MIN_DISTANCEX = dimension.x / 2.0f + scaledScreenDimension.x / 2.0f;
		const float MIN_DISTANCEY = dimension.y / 2.0f + scaledScreenDimension.y / 2.0f;

		vec2 centerPosition = position + (dimension / 2.0f);
		vec2 centerCameraPosition = c_position;

		vec2 distVec = centerPosition - centerCameraPosition;

		float xDepth = MIN_DISTANCEX - abs(distVec.x);
		float yDepth = MIN_DISTANCEY - abs(distVec.y);

		if (xDepth < 0 && yDepth < 0) {
			return false;
		}

		return true;
	}

	vec2 Camera::convertWorldCoordstoScreenCoords(vec2 screenCoords)
	{
		screenCoords.y = c_screenHeight - screenCoords.y;
		screenCoords -= vec2(c_screenWidth / 2, c_screenHeight / 2);
		screenCoords /= c_scale;
		screenCoords += c_position;
		return screenCoords;
	}

}