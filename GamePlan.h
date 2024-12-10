#pragma once
#include "MatchDay.h"

#define NUM_MATCHDAYS_PER_ROUND 17
#define NUM_TEAMS_IN_TOURNAMENT 18

namespace TournamentPlanner {
	ref class GamePlan
	{
	public:
		array<System::String^>^ teams;
		System::Collections::Generic::List<MatchDay^>^ firstRoundMatchDays;
		System::Collections::Generic::List<MatchDay^>^ secondRoundMatchDays;

		GamePlan()
		{
			this->firstRoundMatchDays = gcnew System::Collections::Generic::List<MatchDay^>(NUM_MATCHDAYS_PER_ROUND);
			this->secondRoundMatchDays = gcnew System::Collections::Generic::List<MatchDay^>(NUM_MATCHDAYS_PER_ROUND);
		}

		void WriteToFile(System::String^ filePath);
		static GamePlan^ ReadFromFile(System::String^ filePath);
	};
}