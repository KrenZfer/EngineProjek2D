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
		Animation(){
			Animation("ANIMATION");
		}
		Animation(string TAG);
		~Animation();

		enum MODE {
			NORMAL,
			REVERSED,
			LOOP,
			REVERSED_LOOP
		};

		void createKeyFrame(ImageTexture imgTexture, int row, int col, int frameDuration = 50.0f, MODE anim_mode = MODE::LOOP);
		void createKeyFrame(Sprite sprite, int row, int col, int frameDuration = 50.0f, MODE anim_mode = MODE::LOOP);
		KeyFrame getCurrentKeyFrame(float deltaTime);
		KeyFrame getKeyFrameIndexBased(int index);
		void setKeyFrameStart(int indeks) { this->indeks = indeks; }

		string getTAG() { return a_TAG; }
		void setTAG(string TAG) { a_TAG = TAG; }

		int getFrameDuration() { return a_frame_durations; }
		void setFrameDuration(int frameDuration) { a_frame_durations = frameDuration; }

		int getRowSpriteSheet() { return a_Row; }
		int getCollumnSpriteSheet() { return a_Col; }



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
		int indeks;
		float stateTime = 0;
		MODE animMode;
		ImageTexture a_imgTexture;
		Sprite a_sprite;
		vector<KeyFrame> a_keyFrame;
		KeyFrame currentKeyFrame;
	};
}

#endif // !_H_ANIMATION_H_


