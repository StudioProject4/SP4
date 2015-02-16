#pragma once


class CAI
{

	enum AIState
	{
		AI_NONE,
		AI_IDLE,
		AI_TOTAL
	};

	public:
		CAI();
		~CAI();
		void ChangeState();
		void Update();
	private:
		AIState state;
};