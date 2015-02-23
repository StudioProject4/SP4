#pragma once

class CPointSystem
{
	public:
		CPointSystem();
		~CPointSystem();

		void PointsReceive(int points);
		void SetPowerUpActive(bool set);
		int GetPoints();
	private:
		int points;
};