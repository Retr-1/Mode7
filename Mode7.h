#pragma once
#include "olcPixelGameEngine.h"

class Mode7 {
public:
	olc::Sprite* floor;
	olc::Sprite* roof;
	float fFar;
	float fNear;
	float halfFov;

	void draw(olc::PixelGameEngine& canvas, const olc::vf2d& pos, float angle) {
		olc::vf2d near1 = { pos.x + cosf(angle - halfFov) * fNear, pos.y + sinf(angle - halfFov) * fNear };
		olc::vf2d near2 = { pos.x + cosf(angle + halfFov) * fNear, pos.y + sinf(angle + halfFov) * fNear };
		olc::vf2d far1 = { pos.x + cosf(angle - halfFov) * fFar, pos.y + sinf(angle - halfFov) * fFar };
		olc::vf2d far2 = { pos.x + cosf(angle + halfFov) * fFar, pos.y + sinf(angle + halfFov) * fFar };

		float hScrn = canvas.ScreenHeight() / 2;
		for (int y = 0; y < hScrn; y++) {
			float sampleDepth = y / hScrn;
			olc::vf2d xpos1 = (far1 - near1) / sampleDepth + near1;
			olc::vf2d xpos2 = (far2 - near2) / sampleDepth + near2;
			for (int x = 0; x < canvas.ScreenWidth(); x++) {
				float sampleWidth = x / (float)canvas.ScreenHeight();
				olc::vf2d samplePos = (xpos2 - xpos1) * sampleWidth + xpos1;
				
				if (floor) {
					canvas.Draw(x, y+hScrn, floor->GetPixel(samplePos));
				}

				if (roof) {
					canvas.Draw(x, y, roof->GetPixel(samplePos));
				}
			}
		}
	}

	void setFOV(float fov) {
		halfFov = fov / 2;
	}

	Mode7(olc::Sprite* floor, olc::Sprite* roof, float fFar, float fNear, float halfFov)
		: floor(floor), roof(roof), fFar(fFar), fNear(fNear), halfFov(halfFov)
	{
	}
	Mode7() {}
};

//void mode7(olc::PixelGameEngine& canvas, const olc::Sprite* floor, const olc::Sprite* roof) {
//	
//}