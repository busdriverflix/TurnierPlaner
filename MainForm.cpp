#include "pch.h"
#include "MainForm.h"

using namespace TournamentPlanner;
using namespace System::Collections::Generic;

void MainForm::FillListBoxWithTeams(array<System::String^>^ teamsList)
{
	TeamsListBox->Items->Clear();

	for each (System::String^ line in teamsList)
	{
		TeamsListBox->Items->Add(line);
	}
}

void MainForm::FillMatchesListBoxWithData(void)
{
	bool firstRound = (RoundComboBox->SelectedIndex == 0);
	int matchDay = MatchDayComboBox->SelectedIndex + 1;

	if (matchDay < 1 || matchDay > NUM_MATCHDAYS_PER_ROUND)
		return;

	MatchesListBox->Items->Clear();

	MatchDay^ selectedMatchDay = nullptr;

	if (firstRound)
		selectedMatchDay = currentGamePlan->firstRoundMatchDays[matchDay - 1];
	else
		selectedMatchDay = currentGamePlan->secondRoundMatchDays[matchDay - 1];

	System::String^ unknownScoreString = "? : ?";

	for each (Match^ match in selectedMatchDay->matches)
	{
		System::String^ scoreString;

		if (match->score.numGoalsHomeTeam == -1 || match->score.numGoalsVisitingTeam == -1)
			scoreString = unknownScoreString;
		else
			scoreString = match->score.numGoalsHomeTeam + " : " + match->score.numGoalsVisitingTeam;

		System::String^ itemString = match->homeTeamName + " - " + match->visitingTeamName + ": " + scoreString;
		MatchesListBox->Items->Add(itemString);
	}
}

bool MainForm::AllResultsEnteredUpToMatchDay(int matchDay)
{
	bool firstRound = (RoundComboBox->SelectedIndex == 0);
	bool result = true;

	for (int matchDayIndex = 0; matchDayIndex < matchDay; matchDayIndex++)
	{
		MatchDay^ currentMatchDay = nullptr;
		if (firstRound)
			currentMatchDay = currentGamePlan->firstRoundMatchDays[matchDayIndex];
		else
			currentMatchDay = currentGamePlan->secondRoundMatchDays[matchDayIndex]; 
		
		for (int j = 0; j < currentMatchDay->matches->Count; ++j)
		{
			Match^ match = currentMatchDay->matches[j];

			// Überprüfe, ob beide Teams ein Ergebnis haben
			if (match->score.numGoalsHomeTeam == -1 || match->score.numGoalsVisitingTeam == -1)
			{
				result = false;
				break;
			}
		}

		if (!result)
			break;
	}

	return result;
}

int MainForm::CompareTeams(KeyValuePair<System::String^, int> teamA, KeyValuePair<System::String^, int> teamB)
{
	return teamB.Value - teamA.Value;
}

List<System::String^>^ MainForm::GenerateRankingTableUpToMatchDay(int matchDay)
{
	Dictionary<System::String^, int>^ teamWins = gcnew Dictionary<System::String^, int>();

	bool firstRound = (RoundComboBox->SelectedIndex == 0);

	for (int i = 0; i <= matchDay; i++)
	{
		MatchDay^ currentMatchDay = firstRound ? currentGamePlan->firstRoundMatchDays[i] : currentGamePlan->secondRoundMatchDays[i];

		for each (Match^ match in currentMatchDay->matches)
		{
			if (match->score.numGoalsHomeTeam == -1 || match->score.numGoalsVisitingTeam == -1)
				continue;

			if (match->score.numGoalsHomeTeam > match->score.numGoalsVisitingTeam)
			{
				if (!teamWins->ContainsKey(match->homeTeamName))
					teamWins[match->homeTeamName] = 0;
				teamWins[match->homeTeamName]++;
			}
			else if (match->score.numGoalsHomeTeam < match->score.numGoalsVisitingTeam)
			{
				if (!teamWins->ContainsKey(match->visitingTeamName))
					teamWins[match->visitingTeamName] = 0;
				teamWins[match->visitingTeamName]++;
			}
		}
	}

	List<KeyValuePair<System::String^, int>>^ sortedTeams = gcnew List<KeyValuePair<System::String^, int>>();

	for each (auto kvp in teamWins)
	{
		sortedTeams->Add(kvp);
	}

	sortedTeams->Sort(gcnew System::Comparison<KeyValuePair<System::String^, int>>(this, &MainForm::CompareTeams));

	List<System::String^>^ rankingList = gcnew List<System::String^>();

	for each (auto kvp in sortedTeams)
	{
		rankingList->Add(kvp.Key + " - " + kvp.Value + " Siege");
	}

	return rankingList;
}

void MainForm::FillRankingTableListBoxWithData(void)
{
	int matchDayIndex = MatchDayComboBox->SelectedIndex;

	if (!AllResultsEnteredUpToMatchDay(matchDayIndex + 1))
	{
		RankingTableListBox->Items->Clear();
		return;
	}

	bool firstRound = (RoundComboBox->SelectedIndex == 0);

	MatchDay^ matchDay = nullptr;

	if (firstRound)
		matchDay = currentGamePlan->firstRoundMatchDays[matchDayIndex];
	else
		matchDay = currentGamePlan->secondRoundMatchDays[matchDayIndex];

	List<System::String^>^ rankedList = GenerateRankingTableUpToMatchDay(matchDayIndex + 1);

	RankingTableListBox->Items->Clear();

	for each (System::String^ team in rankedList)
	{
		RankingTableListBox->Items->Add(team);
	}
}

Match^ MainForm::GetMatchFromCurrentSelection(void)
{
	bool firstRound = (RoundComboBox->SelectedIndex == 0);
	int matchDayIndex = MatchDayComboBox->SelectedIndex;
	int matchOfDayIndex = MatchesListBox->SelectedIndex;

	if (firstRound)
		return currentGamePlan->firstRoundMatchDays[matchDayIndex]->matches[matchOfDayIndex];
	else
		return currentGamePlan->secondRoundMatchDays[matchDayIndex]->matches[matchOfDayIndex];
}

void MainForm::InitializeAfterTeamsLoad(void)
{
	RoundComboBox->Enabled = true;
	RoundComboBox->SelectedIndex = 0;

	MatchDayComboBox->Enabled = true;
	MatchDayComboBox->SelectedIndex = 0;

	FillMatchesListBoxWithData();
	MatchesListBox->Enabled = true;

	MatchDayLabel->Enabled = true;
	MatchesLabel->Enabled = true;

	ExportGamePlanButton->Enabled = true;
}

System::Void MainForm::ImportTeamsButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ fileDialog = gcnew OpenFileDialog();
	fileDialog->Filter = "Textdateien (*.txt)|*.txt";
	fileDialog->FilterIndex = 1;
	fileDialog->Title = "Mannschaftenliste auswählen";

	if (fileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		array<System::String^>^ teamsList = System::IO::File::ReadAllLines(fileDialog->FileName, System::Text::Encoding::Default);
		FillListBoxWithTeams(teamsList);
		GamePlanGenerator^ gamePlanGenerator = gcnew GamePlanGenerator(teamsList);
		currentGamePlan = gamePlanGenerator->GenerateGamePlan();
		InitializeAfterTeamsLoad();
	}
}

System::Void MainForm::RoundComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	FillMatchesListBoxWithData();
}

System::Void MainForm::MatchDayComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	FillMatchesListBoxWithData();
	FillRankingTableListBoxWithData();
}

System::Void MainForm::MatchesListBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (MatchesListBox->SelectedIndex < 0)
		return;

	Match^ selectedMatch = GetMatchFromCurrentSelection();

	HomeTeamNameLabel->Text = selectedMatch->homeTeamName + ":";
	VisitingTeamNameLabel->Text = selectedMatch->visitingTeamName + ":";

	HomeTeamScoreTextBox->Text = (selectedMatch->score.numGoalsHomeTeam == -1) ? "" : selectedMatch->score.numGoalsHomeTeam.ToString();
	VisitingTeamScoreTextBox->Text = (selectedMatch->score.numGoalsVisitingTeam == -1) ? "" : selectedMatch->score.numGoalsVisitingTeam.ToString();

	HomeTeamScoreTextBox->Enabled = true;
	VisitingTeamScoreTextBox->Enabled = true;
	ApplyScoreButton->Enabled = true;
}

System::Void MainForm::HandleTextBoxKeyPressToAllowNumbersOnly(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
	if (!Char::IsDigit(e->KeyChar) && e->KeyChar != '\b')
	{
		e->Handled = true;
	}
}

System::Void MainForm::ApplyScoreButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	Match^ selectedMatch = GetMatchFromCurrentSelection();

	if (HomeTeamScoreTextBox->Text != "")
		selectedMatch->score.numGoalsHomeTeam = Convert::ToInt32(HomeTeamScoreTextBox->Text);

	if (VisitingTeamScoreTextBox->Text != "")
		selectedMatch->score.numGoalsVisitingTeam = Convert::ToInt32(VisitingTeamScoreTextBox->Text);

	int listBoxIndex = MatchesListBox->SelectedIndex;
	FillMatchesListBoxWithData();
	MatchesListBox->SelectedIndex = listBoxIndex;
}

System::Void MainForm::ExportGamePlanButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ fileDialog = gcnew SaveFileDialog();
	fileDialog->Filter = "Textdateien (*.txt)|*.txt";
	fileDialog->FilterIndex = 1;
	fileDialog->Title = "Spielplan exportieren";

	if (fileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		currentGamePlan->WriteToFile(fileDialog->FileName);
		MessageBox::Show("Spielplan erfolgreich exportiert!");
	}
}

System::Void MainForm::ImportGamePlanButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ fileDialog = gcnew OpenFileDialog();
	fileDialog->Filter = "Textdateien (*.txt)|*.txt";
	fileDialog->FilterIndex = 1;
	fileDialog->Title = "SpielPlan importieren";

	if (fileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		currentGamePlan = GamePlan::ReadFromFile(fileDialog->FileName);
		InitializeAfterTeamsLoad();
		FillListBoxWithTeams(currentGamePlan->teams);
	}
}