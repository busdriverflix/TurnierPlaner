#pragma once

namespace TournamentPlanner {
	ref class TeamsImporter
	{
	public:
		static array<System::String^>^ ReadFromTxtFile(System::String^ filePath);
	};
}