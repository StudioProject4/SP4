#pragma once

class CHealthSystem
{
	public:
		CHealthSystem();
		~CHealthSystem();
		
		void TakeDMG();
		void RecoverHealth();
		int GetHealth();
		void SetHealth(int hp)
		{
			health=hp;
		}
	private:
		int health;
};