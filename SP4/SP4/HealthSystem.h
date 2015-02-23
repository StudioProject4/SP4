#pragma once

class CHealthSystem
{
	public:
		CHealthSystem();
		~CHealthSystem();
		
		void TakeDMG();
		void RecoverHealth();
		int GetHealth();
	private:
		int health;
};