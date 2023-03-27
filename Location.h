#pragma once

namespace Tmpl8
{
	// An all purpose location class //
	class Location
	{
	public: // Class Functions //
		void Add(const Location& val)
		{
			x += val.x;
			y += val.y;
		}
	public: // Class Operator Assignments //
		bool operator==(const Location& rhs) const { return x == rhs.x && y == rhs.y; }
	public: // Class Variables //
		float x;
		float y;
	};
};