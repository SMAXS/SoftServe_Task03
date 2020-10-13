#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "ProjectAnalyzer.h"
#include "Wexception.h"

int main()
{
	try
	{
		std::wstring directoryPath = LR"(Enter project directory here)";
		std::initializer_list<std::wstring> extensions_for_search = { L".cpp", L".c", L".h", L".hpp" };
		ProjectAnalyzer analyzer{ directoryPath, extensions_for_search };

		clock_t time1 = clock();
		analyzer.AnalyzeProject();
		clock_t time2 = clock();

		clock_t delta = time2 - time1;
		std::wcout << "Analize speed (ms) = " << delta << std::endl;

		std::wcout << analyzer;

		std::wofstream fout{ "Result.txt" };
		fout << analyzer;
		fout.close();
	}
	catch (const Wexception& wex)
	{
		std::wcerr << wex.what() << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::wcerr << ex.what() << std::endl;
	}

	return 0;
}
