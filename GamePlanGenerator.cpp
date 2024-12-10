#include "pch.h"
#include "GamePlanGenerator.h"
#include "GamePlan.h"
#include "MatchDay.h"

using namespace TournamentPlanner;
using namespace System::Collections::Generic;

List<GamePlanGenerator::TeamPairIndices>^ GamePlanGenerator::RoundRobinTeamPairs(void)
{
	List<GamePlanGenerator::TeamPairIndices>^ teamPairs = gcnew List<GamePlanGenerator::TeamPairIndices>();

	int numMatchdays = NUM_MATCHDAYS_PER_ROUND;
	int matchesPerDay = NUM_TEAMS_IN_TOURNAMENT / 2;

	for (int matchDay = 0; matchDay < numMatchdays; matchDay++)
	{
		for (int match = 0; match < matchesPerDay; match++)
		{
			int home = (matchDay + match) % (NUM_TEAMS_IN_TOURNAMENT - 1);
			int visiting = (NUM_TEAMS_IN_TOURNAMENT - 1 - match + matchDay) % (NUM_TEAMS_IN_TOURNAMENT - 1);

			// Letztes Team bleibt fest
			if (match == 0)
			{
				visiting = NUM_TEAMS_IN_TOURNAMENT - 1;
			}

			GamePlanGenerator::TeamPairIndices teamPair;
			teamPair.team1Index = home;
			teamPair.team2Index = visiting;
			teamPairs->Add(teamPair);
		}
	}

	return teamPairs;
}

void GamePlanGenerator::GenerateMatchDaysRound1(void)
{
	List<GamePlanGenerator::TeamPairIndices>^ teamPairsIndices = RoundRobinTeamPairs();

	int teamPairIndex = 0;

	for (int i = 0; i < NUM_MATCHDAYS_PER_ROUND; i++)
	{
		MatchDay^ matchDay = gcnew MatchDay();

		for (int j = 0; j < NUM_MATCHES_PER_DAY; j++)
		{
			GamePlanGenerator::TeamPairIndices teamPair = teamPairsIndices[teamPairIndex++];

			Match^ match = gcnew Match();
			match->homeTeamName = this->teamsList[teamPair.team1Index];
			match->visitingTeamName = this->teamsList[teamPair.team2Index];

			matchDay->matches->Add(match);
		}

		this->gamePlan->firstRoundMatchDays->Add(matchDay);
	}
}

void GamePlanGenerator::GenerateMatchDaysRound2(void)
{
	for (int i = 0; i < NUM_MATCHDAYS_PER_ROUND; i++)
	{
		MatchDay^ matchDay = gcnew MatchDay();

		for (int j = 0; j < NUM_MATCHES_PER_DAY; j++)
		{
			Match^ originalMatch = this->gamePlan->firstRoundMatchDays[i]->matches[j];

			Match^ match = gcnew Match();
			match->homeTeamName = originalMatch->visitingTeamName;
			match->visitingTeamName = originalMatch->homeTeamName;

			matchDay->matches->Add(match);
		}

		this->gamePlan->secondRoundMatchDays->Add(matchDay);
	}
}

GamePlan^ GamePlanGenerator::GenerateGamePlan(void)
{
	gamePlan = gcnew GamePlan();
	gamePlan->teams = this->teamsList;

	GenerateMatchDaysRound1();
	GenerateMatchDaysRound2();

	return gamePlan;
}