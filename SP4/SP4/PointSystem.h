#pragma once

class CPointSystem
{
	public:

		void PointsReceive(int points);
		//void SetPowerUpActive(bool set);
		int GetPoints();

		static CPointSystem * GetInstance(void);
		static void Drop(void);
	private:
		CPointSystem();
		~CPointSystem();
		int points;

		static CPointSystem * s_instance;
};