#include "pch.h"
#include "TeamsImporter.h"

using namespace TournamentPlanner;

array<System::String^>^ TeamsImporter::ReadFromTxtFile(System::String^ filePath)
{
	if (!System::IO::File::Exists(filePath))
	{
		throw gcnew System::IO::FileNotFoundException("Die angegebene Datei existiert nicht: " + filePath);
	}

	return System::IO::File::ReadAllLines(filePath);
}