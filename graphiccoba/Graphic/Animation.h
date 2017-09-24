#ifndef _H_ANIMATION_H_
#define _H_ANIMATION_H_

#include <vector>
#include "ImageTexture.h"
#include "Sprite.h"

using namespace std;
using namespace EngineProject2D;


namespace EngineProject2D {

	struct KeyFrame {

	public:
		KeyFrame(){}
		KeyFrame(float u, float v, float u2, float v2, float width, float height) {
			kf_u = u;
			kf_v = v;
			kf_u2 = u2;
			kf_v2 = v2;
			kf_width = width;
			kf_height = height;
		}

		float kf_u;
		float kf_u2;
		float kf_v;
		float kf_v2;
		float kf_width;
		float kf_height;
	};

	class Animation {

	public:
		Animation(){}
		Animation(string TAG);
		~Animation();

		enum MODE {
			NORMAL,
			REVERSED,
			LOOP,
			REVERSED_LOOP
		};

		void createKeyFrame(ImageTexture imgTexture, int row, int col, int frameDuration = 50.0f, MODE anim_mode = MODE::NORMAL);
		void createKeyFrame(Sprite sprite, int row, int col, int frameDuration = 50.0f, MODE anim_mode = MODE::NORMAL);
		KeyFrame getCurrentKeyFrame(float deltaTime);
		KeyFrame getKeyFrameIndexBased(int index);
		void setKeyFrameStart(int indeks) { this->indeks = indeks; }

	private:
		string a_TAG;
		int a_frame_durations;
		int a_num_frames;
		float a_width;
		float a_height;
		float a_width_per_frame;
		float a_height_per_frame;
		int a_Row;
		int a_Col;
		int indeks = 0;
		float stateTime = 0;
		ImageTexture a_imgTexture;
		Sprite a_sprite;
		vector<KeyFrame> a_keyFrame;
		KeyFrame currentKeyFrame;
	};
}

#endif // !_H_ANIMATION_H_

