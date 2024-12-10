#include "pch.h"
#include "GamePlan.h"

using namespace TournamentPlanner;

static void WriteMatch(Match^ match, System::IO::StreamWriter^ writer)
{
	System::String^ scoreString;
	if (match->score.numGoalsHomeTeam == -1 || match->score.numGoalsVisitingTeam == -1)
	{
		scoreString = "? : ?";
	}
	else
	{
		scoreString = match->score.numGoalsHomeTeam + " : " + match->score.numGoalsVisitingTeam;
	}

	writer->WriteLine("\t" + match->homeTeamName + " - " + match->visitingTeamName + ": " + scoreString);
}

void GamePlan::WriteToFile(System::String^ filePath)
{
	System::IO::StreamWriter^ writer = gcnew System::IO::StreamWriter(filePath);

	try
	{
		writer->WriteLine("Hinrunde:\n");

		for (int i = 0; i < firstRoundMatchDays->Count; i++)
		{
			writer->WriteLine("Spieltag " + (i + 1) + ":");

			MatchDay^ matchDay = firstRoundMatchDays[i];

			for (int j = 0; j < matchDay->matches->Count; j++)
			{
				Match^ match = matchDay->matches[j];

				WriteMatch(match, writer);
			}

			writer->WriteLine();
		}

		writer->WriteLine("Rückrunde:\n");

		for (int i = 0; i < secondRoundMatchDays->Count; i++)
		{
			writer->WriteLine("Spieltag " + (i + 1) + ":");
			
			MatchDay^ matchDay = secondRoundMatchDays[i];

			for (int j = 0; j < matchDay->matches->Count; j++)
			{
				Match^ match = matchDay->matches[j];

				WriteMatch(match, writer);
			}

			writer->WriteLine();
		}
	}
	finally
	{
		writer->Close();
	}
}

GamePlan^ GamePlan::ReadFromFile(System::String^ filePath)
{
	if (!System::IO::File::Exists(filePath))
	{
		throw gcnew System::IO::FileNotFoundException("Datei nicht gefunden: " + filePath);
	}

    GamePlan^ gamePlan = gcnew GamePlan();
    System::Collections::Generic::List<System::String^>^ teamsList = gcnew System::Collections::Generic::List<System::String^>();

	array<System::String^>^ lines = System::IO::File::ReadAllLines(filePath);

	bool isFirstRound = true;
	MatchDay^ currentMatchDay = nullptr;

    for each (System::String ^ line in lines)
    {
        line = line->Trim();

        if (line->StartsWith("Hinrunde:"))
        {
            isFirstRound = true;
            continue;
        }
        else if (line->StartsWith("Rückrunde:"))
        {
            isFirstRound = false;
            continue;
        }
        else if (line->StartsWith("Spieltag"))
        {
            // Beginne einen neuen Spieltag
            currentMatchDay = gcnew MatchDay();
            if (isFirstRound)
            {
                gamePlan->firstRoundMatchDays->Add(currentMatchDay);
            }
            else
            {
                gamePlan->secondRoundMatchDays->Add(currentMatchDay);
            }
            continue;
        }
        else if (!System::String::IsNullOrEmpty(line))
        {
            array<System::String^>^ parts = line->Split(gcnew array<wchar_t>{':'}, System::StringSplitOptions::RemoveEmptyEntries);

            if (parts->Length >= 2)
            {
                array<System::String^>^ teams = parts[0]->Split('-');

                if (teams->Length == 2)
                {
                    Match^ match = gcnew Match();
                    match->homeTeamName = teams[0]->Trim();
                    match->visitingTeamName = teams[1]->Trim();

                    if (!teamsList->Contains(match->homeTeamName))
                    {
                        teamsList->Add(match->homeTeamName);
                    }
                    if (!teamsList->Contains(match->visitingTeamName))
                    {
                        teamsList->Add(match->visitingTeamName);
                    }
                    
                    if (parts[1]->Trim()->Equals("?"))
                        match->score.numGoalsHomeTeam = -1;
                    else
                        match->score.numGoalsHomeTeam = System::Convert::ToInt32(parts[1]);

                    if (parts[2]->Trim()->Equals("?"))
                        match->score.numGoalsVisitingTeam = -1;
                    else
                        match->score.numGoalsVisitingTeam = System::Convert::ToInt32(parts[2]);

                    currentMatchDay->matches->Add(match);
                }
            }
        }
    }

    gamePlan->teams = teamsList->ToArray();
    return gamePlan;
}