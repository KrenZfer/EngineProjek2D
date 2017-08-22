#include "Animation.h"
#include <iostream>

Animation::Animation(string TAG, int row, int col)
{
	a_Row = row;
	a_Col = col;
	currentKeyFrame = KeyFrame();
	a_TAG = TAG;
}

Animation::~Animation()
{
}

void Animation::createKeyFrame(ImageTexture imgTexture, int frameDuration, MODE anim_mode)
{
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
			cout << "(u, v, u2, v2) (" << u << ", " << v << ", " << u2 << ", " << v2 << ")" << endl;
		}
	}
	cout << "nKeyFrame : " << a_keyFrame.size() << endl;
}

KeyFrame Animation::getCurrentKeyFrame(float deltaTime)
{
	stateTime += deltaTime;

	if (stateTime > a_frame_durations) {
		stateTime = 0;
		indeks++;
		//cout << "indeks" << indeks << endl;
	}

	if (indeks >= a_keyFrame.size())

		indeks = 0;

	currentKeyFrame = a_keyFrame[indeks];

	//cout << "(u, v, u2, v2) (" << currentKeyFrame.kf_u << ", " << currentKeyFrame.kf_v << ", " << currentKeyFrame.kf_u2 << ", " << currentKeyFrame.kf_v2 << ")" << endl;

	return currentKeyFrame;
}


