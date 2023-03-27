#pragma once

namespace Tmpl8
{
	// Location Utility Class //
	class Location
	{
	public: // Functions //
		void Add(const Location& val) // Function which adds the given value to the current location
		{
			x += val.x;
			y += val.y;
		}
	public: // Operator Assignments //
		bool operator==(const Location& rhs) const { return x == rhs.x && y == rhs.y; }
	public: // Variables //
		int x;
		int y;
	};
};