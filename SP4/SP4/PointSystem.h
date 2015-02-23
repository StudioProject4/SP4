#pragma once

class CPointSystem
{
	public:
		CPointSystem();
		~CPointSystem();
		void PointsReceive(int points);
	private:
		int points;

};