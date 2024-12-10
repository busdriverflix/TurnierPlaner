#pragma once

namespace TournamentPlanner {
	ref class Match
	{
	public:
		System::String^ homeTeamName;
		System::String^ visitingTeamName;

		value struct Score
		{
			int numGoalsHomeTeam, numGoalsVisitingTeam;
		};

		Score score = { -1, -1 };

		Match() { }

		Match(System::String^ homeTeamName, System::String^ visitingTeamName)
		{
			this->homeTeamName = homeTeamName;
			this->visitingTeamName = visitingTeamName;
		}
	};
}