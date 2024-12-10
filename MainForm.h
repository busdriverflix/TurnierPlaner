#pragma once
#include "GamePlan.h"
#include "GamePlanGenerator.h"

namespace TournamentPlanner {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ ImportTeamsButton;
	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::ListBox^ TeamsListBox;
	private: System::Windows::Forms::ComboBox^ RoundComboBox;
	private: System::Windows::Forms::ComboBox^ MatchDayComboBox;
	private: System::Windows::Forms::ListBox^ MatchesListBox;
	private: System::Windows::Forms::Label^ MatchDayLabel;
	private: System::Windows::Forms::Label^ TeamsListBoxLabel;
	private: System::Windows::Forms::Label^ MatchesLabel;
	private: System::Windows::Forms::Label^ HomeTeamNameLabel;


	private: System::Windows::Forms::Label^ VisitingTeamNameLabel;
	private: System::Windows::Forms::TextBox^ HomeTeamScoreTextBox;

	private: System::Windows::Forms::Label^ ScoreLabel;
	private: System::Windows::Forms::TextBox^ VisitingTeamScoreTextBox;
	private: System::Windows::Forms::Button^ ApplyScoreButton;
	private: System::Windows::Forms::Button^ ExportGamePlanButton;
	private: System::Windows::Forms::Button^ ImportGamePlanButton;
	private: System::Windows::Forms::Label^ RankingTableLabel;
	private: System::Windows::Forms::ListBox^ RankingTableListBox;



	private: GamePlan^ currentGamePlan;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->ImportTeamsButton = (gcnew System::Windows::Forms::Button());
			this->TeamsListBox = (gcnew System::Windows::Forms::ListBox());
			this->RoundComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->MatchDayComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->MatchesListBox = (gcnew System::Windows::Forms::ListBox());
			this->MatchDayLabel = (gcnew System::Windows::Forms::Label());
			this->TeamsListBoxLabel = (gcnew System::Windows::Forms::Label());
			this->MatchesLabel = (gcnew System::Windows::Forms::Label());
			this->HomeTeamNameLabel = (gcnew System::Windows::Forms::Label());
			this->VisitingTeamNameLabel = (gcnew System::Windows::Forms::Label());
			this->HomeTeamScoreTextBox = (gcnew System::Windows::Forms::TextBox());
			this->ScoreLabel = (gcnew System::Windows::Forms::Label());
			this->VisitingTeamScoreTextBox = (gcnew System::Windows::Forms::TextBox());
			this->ApplyScoreButton = (gcnew System::Windows::Forms::Button());
			this->ExportGamePlanButton = (gcnew System::Windows::Forms::Button());
			this->ImportGamePlanButton = (gcnew System::Windows::Forms::Button());
			this->RankingTableLabel = (gcnew System::Windows::Forms::Label());
			this->RankingTableListBox = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// ImportTeamsButton
			// 
			this->ImportTeamsButton->Location = System::Drawing::Point(12, 12);
			this->ImportTeamsButton->Name = L"ImportTeamsButton";
			this->ImportTeamsButton->Size = System::Drawing::Size(135, 23);
			this->ImportTeamsButton->TabIndex = 0;
			this->ImportTeamsButton->Text = L"Manschaften laden";
			this->ImportTeamsButton->UseVisualStyleBackColor = true;
			this->ImportTeamsButton->Click += gcnew System::EventHandler(this, &MainForm::ImportTeamsButton_Click);
			// 
			// TeamsListBox
			// 
			this->TeamsListBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->TeamsListBox->FormattingEnabled = true;
			this->TeamsListBox->Location = System::Drawing::Point(12, 70);
			this->TeamsListBox->Name = L"TeamsListBox";
			this->TeamsListBox->Size = System::Drawing::Size(223, 615);
			this->TeamsListBox->TabIndex = 1;
			// 
			// RoundComboBox
			// 
			this->RoundComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->RoundComboBox->Enabled = false;
			this->RoundComboBox->FormattingEnabled = true;
			this->RoundComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Hinrunde", L"Rückrunde" });
			this->RoundComboBox->Location = System::Drawing::Point(241, 70);
			this->RoundComboBox->Name = L"RoundComboBox";
			this->RoundComboBox->Size = System::Drawing::Size(121, 21);
			this->RoundComboBox->TabIndex = 2;
			this->RoundComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::RoundComboBox_SelectedIndexChanged);
			// 
			// MatchDayComboBox
			// 
			this->MatchDayComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->MatchDayComboBox->Enabled = false;
			this->MatchDayComboBox->FormattingEnabled = true;
			this->MatchDayComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(17) {
				L"1", L"2", L"3", L"4", L"5", L"6", L"7",
					L"8", L"9", L"10", L"11", L"12", L"13", L"14", L"15", L"16", L"17"
			});
			this->MatchDayComboBox->Location = System::Drawing::Point(241, 118);
			this->MatchDayComboBox->Name = L"MatchDayComboBox";
			this->MatchDayComboBox->Size = System::Drawing::Size(121, 21);
			this->MatchDayComboBox->TabIndex = 3;
			this->MatchDayComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::MatchDayComboBox_SelectedIndexChanged);
			// 
			// MatchesListBox
			// 
			this->MatchesListBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->MatchesListBox->Enabled = false;
			this->MatchesListBox->FormattingEnabled = true;
			this->MatchesListBox->Location = System::Drawing::Point(368, 70);
			this->MatchesListBox->Name = L"MatchesListBox";
			this->MatchesListBox->Size = System::Drawing::Size(534, 615);
			this->MatchesListBox->TabIndex = 4;
			this->MatchesListBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::MatchesListBox_SelectedIndexChanged);
			// 
			// MatchDayLabel
			// 
			this->MatchDayLabel->AutoSize = true;
			this->MatchDayLabel->Enabled = false;
			this->MatchDayLabel->Location = System::Drawing::Point(242, 102);
			this->MatchDayLabel->Name = L"MatchDayLabel";
			this->MatchDayLabel->Size = System::Drawing::Size(48, 13);
			this->MatchDayLabel->TabIndex = 5;
			this->MatchDayLabel->Text = L"Spieltag:";
			// 
			// TeamsListBoxLabel
			// 
			this->TeamsListBoxLabel->AutoSize = true;
			this->TeamsListBoxLabel->Location = System::Drawing::Point(12, 54);
			this->TeamsListBoxLabel->Name = L"TeamsListBoxLabel";
			this->TeamsListBoxLabel->Size = System::Drawing::Size(78, 13);
			this->TeamsListBoxLabel->TabIndex = 6;
			this->TeamsListBoxLabel->Text = L"Mannschaften:";
			// 
			// MatchesLabel
			// 
			this->MatchesLabel->AutoSize = true;
			this->MatchesLabel->Enabled = false;
			this->MatchesLabel->Location = System::Drawing::Point(365, 54);
			this->MatchesLabel->Name = L"MatchesLabel";
			this->MatchesLabel->Size = System::Drawing::Size(39, 13);
			this->MatchesLabel->TabIndex = 7;
			this->MatchesLabel->Text = L"Spiele:";
			// 
			// HomeTeamNameLabel
			// 
			this->HomeTeamNameLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->HomeTeamNameLabel->AutoSize = true;
			this->HomeTeamNameLabel->Location = System::Drawing::Point(911, 92);
			this->HomeTeamNameLabel->Name = L"HomeTeamNameLabel";
			this->HomeTeamNameLabel->Size = System::Drawing::Size(0, 13);
			this->HomeTeamNameLabel->TabIndex = 9;
			// 
			// VisitingTeamNameLabel
			// 
			this->VisitingTeamNameLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->VisitingTeamNameLabel->AutoSize = true;
			this->VisitingTeamNameLabel->Location = System::Drawing::Point(911, 117);
			this->VisitingTeamNameLabel->Name = L"VisitingTeamNameLabel";
			this->VisitingTeamNameLabel->Size = System::Drawing::Size(0, 13);
			this->VisitingTeamNameLabel->TabIndex = 10;
			// 
			// HomeTeamScoreTextBox
			// 
			this->HomeTeamScoreTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->HomeTeamScoreTextBox->Enabled = false;
			this->HomeTeamScoreTextBox->Location = System::Drawing::Point(1045, 88);
			this->HomeTeamScoreTextBox->Name = L"HomeTeamScoreTextBox";
			this->HomeTeamScoreTextBox->Size = System::Drawing::Size(100, 20);
			this->HomeTeamScoreTextBox->TabIndex = 11;
			this->HomeTeamScoreTextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::HandleTextBoxKeyPressToAllowNumbersOnly);
			// 
			// ScoreLabel
			// 
			this->ScoreLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ScoreLabel->AutoSize = true;
			this->ScoreLabel->Location = System::Drawing::Point(911, 70);
			this->ScoreLabel->Name = L"ScoreLabel";
			this->ScoreLabel->Size = System::Drawing::Size(51, 13);
			this->ScoreLabel->TabIndex = 12;
			this->ScoreLabel->Text = L"Ergebnis:";
			// 
			// VisitingTeamScoreTextBox
			// 
			this->VisitingTeamScoreTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->VisitingTeamScoreTextBox->Enabled = false;
			this->VisitingTeamScoreTextBox->Location = System::Drawing::Point(1045, 114);
			this->VisitingTeamScoreTextBox->Name = L"VisitingTeamScoreTextBox";
			this->VisitingTeamScoreTextBox->Size = System::Drawing::Size(100, 20);
			this->VisitingTeamScoreTextBox->TabIndex = 13;
			this->VisitingTeamScoreTextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::HandleTextBoxKeyPressToAllowNumbersOnly);
			// 
			// ApplyScoreButton
			// 
			this->ApplyScoreButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ApplyScoreButton->Enabled = false;
			this->ApplyScoreButton->Location = System::Drawing::Point(1070, 140);
			this->ApplyScoreButton->Name = L"ApplyScoreButton";
			this->ApplyScoreButton->Size = System::Drawing::Size(75, 23);
			this->ApplyScoreButton->TabIndex = 14;
			this->ApplyScoreButton->Text = L"Anwenden";
			this->ApplyScoreButton->UseVisualStyleBackColor = true;
			this->ApplyScoreButton->Click += gcnew System::EventHandler(this, &MainForm::ApplyScoreButton_Click);
			// 
			// ExportGamePlanButton
			// 
			this->ExportGamePlanButton->Enabled = false;
			this->ExportGamePlanButton->Location = System::Drawing::Point(289, 12);
			this->ExportGamePlanButton->Name = L"ExportGamePlanButton";
			this->ExportGamePlanButton->Size = System::Drawing::Size(130, 23);
			this->ExportGamePlanButton->TabIndex = 15;
			this->ExportGamePlanButton->Text = L"Spielplan exportieren";
			this->ExportGamePlanButton->UseVisualStyleBackColor = true;
			this->ExportGamePlanButton->Click += gcnew System::EventHandler(this, &MainForm::ExportGamePlanButton_Click);
			// 
			// ImportGamePlanButton
			// 
			this->ImportGamePlanButton->Location = System::Drawing::Point(153, 12);
			this->ImportGamePlanButton->Name = L"ImportGamePlanButton";
			this->ImportGamePlanButton->Size = System::Drawing::Size(130, 23);
			this->ImportGamePlanButton->TabIndex = 16;
			this->ImportGamePlanButton->Text = L"Spielplan importieren";
			this->ImportGamePlanButton->UseVisualStyleBackColor = true;
			this->ImportGamePlanButton->Click += gcnew System::EventHandler(this, &MainForm::ImportGamePlanButton_Click);
			// 
			// RankingTableLabel
			// 
			this->RankingTableLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->RankingTableLabel->AutoSize = true;
			this->RankingTableLabel->Location = System::Drawing::Point(911, 192);
			this->RankingTableLabel->Name = L"RankingTableLabel";
			this->RankingTableLabel->Size = System::Drawing::Size(67, 13);
			this->RankingTableLabel->TabIndex = 17;
			this->RankingTableLabel->Text = L"Rangtabelle:";
			// 
			// RankingTableListBox
			// 
			this->RankingTableListBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->RankingTableListBox->FormattingEnabled = true;
			this->RankingTableListBox->Location = System::Drawing::Point(914, 209);
			this->RankingTableListBox->Name = L"RankingTableListBox";
			this->RankingTableListBox->Size = System::Drawing::Size(289, 472);
			this->RankingTableListBox->TabIndex = 18;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1215, 696);
			this->Controls->Add(this->RankingTableListBox);
			this->Controls->Add(this->RankingTableLabel);
			this->Controls->Add(this->ImportGamePlanButton);
			this->Controls->Add(this->ExportGamePlanButton);
			this->Controls->Add(this->ApplyScoreButton);
			this->Controls->Add(this->VisitingTeamScoreTextBox);
			this->Controls->Add(this->ScoreLabel);
			this->Controls->Add(this->HomeTeamScoreTextBox);
			this->Controls->Add(this->VisitingTeamNameLabel);
			this->Controls->Add(this->HomeTeamNameLabel);
			this->Controls->Add(this->MatchesLabel);
			this->Controls->Add(this->TeamsListBoxLabel);
			this->Controls->Add(this->MatchDayLabel);
			this->Controls->Add(this->MatchesListBox);
			this->Controls->Add(this->MatchDayComboBox);
			this->Controls->Add(this->RoundComboBox);
			this->Controls->Add(this->TeamsListBox);
			this->Controls->Add(this->ImportTeamsButton);
			this->Name = L"MainForm";
			this->Text = L"TurnierPlaner";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		void FillListBoxWithTeams(array<System::String^>^ teamsList);
		void InitializeAfterTeamsLoad(void);
		void FillMatchesListBoxWithData(void);
		bool AllResultsEnteredUpToMatchDay(int matchDay);
		int CompareTeams(System::Collections::Generic::KeyValuePair<System::String^, int> teamA, System::Collections::Generic::KeyValuePair<System::String^, int> teamB);
		System::Collections::Generic::List<System::String^>^ GenerateRankingTableUpToMatchDay(int matchDay);
		void FillRankingTableListBoxWithData(void);
		Match^ GetMatchFromCurrentSelection(void);

		System::Void ImportTeamsButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void RoundComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void MatchDayComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void MatchesListBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void HandleTextBoxKeyPressToAllowNumbersOnly(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
		System::Void ApplyScoreButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void ExportGamePlanButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void ImportGamePlanButton_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
