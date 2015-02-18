#pragma once

class CHealthSystem
{
	public:
		CHealthSystem();
		~CHealthSystem();
		
		void TakeDMG();
		void RecoverHealth();
	private:
		int health;
};