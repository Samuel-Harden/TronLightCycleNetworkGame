#pragma once

#include <windows.h>
#include <chrono>
#include <memory>
#include <vector>

class LightCycle;
class LightZone;

using namespace std::literals::chrono_literals;

class TronGame
{
public:
	TronGame(int _no_light_cycles, float& _game_width, float& _game_heigth);
	~TronGame();

	void Tick();

	std::vector<LightCycle*> getLightCycles();
	LightCycle* getLightCycle(int _no);
	std::unique_ptr<LightZone>& getLightZone();

	void resetBikes();
	void resetTiles();

protected:

private:
	std::chrono::steady_clock::time_point updated;

	void createLightCycles(int& _no_lightt_cycles, float _game_width, float _game_height);
	void createLightZone(float& _game_width, float& _game_height);

	float game_size_x;
	float game_size_y;

	std::vector<LightCycle*> m_light_cycles;

	std::unique_ptr<LightZone> light_zone;
};

constexpr float targetFPS = (1 / 15.0f) * 1000;