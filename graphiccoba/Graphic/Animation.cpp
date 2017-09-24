#include "Animation.h"
#include <iostream>

Animation::Animation(string TAG)
{
	currentKeyFrame = KeyFrame();
	a_TAG = TAG;
}

Animation::~Animation()
{
}

void Animation::createKeyFrame(ImageTexture imgTexture, int row, int col, int frameDuration, MODE anim_mode)
{
	a_Row = row;
	a_Col = col;
	a_frame_durations = frameDuration;
	a_imgTexture = imgTexture;

	a_width = a_imgTexture.width;
	a_height = a_imgTexture.height;

	a_width_per_frame = a_width / a_Col;
	a_height_per_frame = a_height / a_Row;

	for (int i = a_Row - 1; i >= 0; i--) {
		float v = i * a_height_per_frame / a_height;
		float v2 = (a_height_per_frame / a_height);
		for (int j = 0; j < a_Col; j++) {
			float u = j * a_width_per_frame / a_width;
			float u2 = (a_width_per_frame / a_width);
			a_keyFrame.emplace_back(u, v, u2, v2, a_width_per_frame, a_height_per_frame);
		}
	}
}

void EngineProject2D::Animation::createKeyFrame(Sprite sprite, int row, int col, int frameDuration, MODE anim_mode)
{
	a_sprite = sprite;
	createKeyFrame(a_sprite.getTexture(), row, col, frameDuration, anim_mode);
}



KeyFrame Animation::getCurrentKeyFrame(float deltaTime)
{
	stateTime += deltaTime;

	if (stateTime > a_frame_durations) {
		stateTime = 0;
		indeks++;
	}

	if (indeks >= a_keyFrame.size())

		indeks = 0;

	currentKeyFrame = a_keyFrame[indeks];

	return currentKeyFrame;
}

KeyFrame EngineProject2D::Animation::getKeyFrameIndexBased(int index)
{
	if (index >= a_keyFrame.size()) {
		index = a_keyFrame.size() - 1;
	}
	return a_keyFrame[index];
}


