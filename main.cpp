#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Mode7.h"
#include <memory>

struct Player {
	olc::vf2d pos;
	float angle;
};

// Override base class with your custom functionality
class Window : public olc::PixelGameEngine
{
	Mode7 mode7;
	Player player;

public:
	Window() : mode7(nullptr, nullptr, 1, 0.1, 3.1415/4)
	{
		// Name your application
		sAppName = "Window";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		mode7.floor = new olc::Sprite("track_wide.jpg");
		mode7.roof = new olc::Sprite("sky.jpg");
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame, draws random coloured pixels
		//std::cout << mode7.floor->width<<' '<<mode7.roof->width<<'\n';
		if (GetKey(olc::W).bHeld) {
			player.pos += olc::vf2d(cosf(player.angle) * fElapsedTime*30, sinf(player.angle) * fElapsedTime*30);
		}
		if (GetKey(olc::A).bHeld) {
			player.angle -= fElapsedTime;
		}
		if (GetKey(olc::D).bHeld) {
			player.angle += fElapsedTime;
		}
		if (GetKey(olc::E).bHeld) {
			mode7.halfFov -= fElapsedTime;
		}
		if (GetKey(olc::Q).bHeld) {
			mode7.halfFov += fElapsedTime;
		}
		if (GetKey(olc::R).bHeld) {
			mode7.fNear += fElapsedTime*10;
		}
		if (GetKey(olc::T).bHeld) {
			mode7.fNear -= fElapsedTime*10;
		}
		if (GetKey(olc::F).bHeld) {
			mode7.fFar += fElapsedTime*10;
		}
		if (GetKey(olc::G).bHeld) {
			mode7.fFar -= fElapsedTime*10;
		}

		mode7.draw(*this, player.pos, player.angle);
		return true;
	}
};

int main()
{
	Window win;
	if (win.Construct(256, 240, 4, 4))
		win.Start();
	return 0;
}