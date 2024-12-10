#pragma once
#include "GamePlan.h"

namespace TournamentPlanner {
	ref class GamePlanGenerator
	{
	public:
		GamePlanGenerator(array<System::String^>^ teamsList)
		{
			this->teamsList = teamsList;
		}

		GamePlan^ GenerateGamePlan(void);
	private:
		GamePlan^ gamePlan;
		array<System::String^>^ teamsList;

		value struct TeamPairIndices
		{
			int team1Index, team2Index;
		};

		System::Collections::Generic::List<TeamPairIndices>^ RoundRobinTeamPairs(void);
		void GenerateMatchDaysRound1(void);
		void GenerateMatchDaysRound2(void);
	};
}