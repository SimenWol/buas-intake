#pragma once

namespace Tmpl8
{
	class Timer
	{
	public:
		// void Draw();
		void Tick(const float& deltaTime);
	public:
		void SetTime(const float& time_in) { time = time_in; };
	private:
		void TimeUp();
	private:
		float time = 10.0f;
	};
};