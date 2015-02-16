#pragma once


class CAI
{

	enum AIState
	{
		ai_idle
	};

	public:
		CAI();
		~CAI();
		void ChangeState();
		void Update();
	private:
		AIState state;
};