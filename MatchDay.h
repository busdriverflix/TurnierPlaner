#pragma once

#include "Match.h"

#define NUM_MATCHES_PER_DAY 9

namespace TournamentPlanner {
	ref class MatchDay
	{
	public:
		System::Collections::Generic::List<Match^>^ matches;

		MatchDay()
		{
			matches = gcnew System::Collections::Generic::List<Match^>(NUM_MATCHES_PER_DAY);
		}
	};
}