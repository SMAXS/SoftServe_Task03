#include "pch.h"
#include "CppUnitTest.h"

#include "..\Solution\CodeAnalyzer.h"
#include "..\Solution\FileReader.h"
#include "..\Solution\FilesHolder.h"
#include "..\Solution\ProjectAnalyzer.h"
#include "..\Solution\Wexception.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Task03_ProjectAnalyzer_Tests
{
	TEST_CLASS(TestCodeAnalyzer)
	{
	public:
		// Test 'CodeAnalyzer()'
		TEST_METHOD(TestDefaultConstructor)
		{
			CodeAnalyzer analyzer;

			Assert::AreEqual(analyzer.get_blank_lines(), 0, L"Incorrect default value of blank lines");
			Assert::AreEqual(analyzer.get_code_lines(), 0, L"Incorrect default value of code lines");
			Assert::AreEqual(analyzer.get_comment_lines(), 0, L"Incorrect default value of comment lines");
			Assert::AreEqual(analyzer.get_physical_lines(), 0, L"Incorrect default value of physical lines");
			Assert::IsTrue(analyzer.get_text().empty(), L"Incorrect size of text");
		}

		// Test 'CodeAnalyzer(const std::wstring& text)'
		TEST_METHOD(TestConstuctor)
		{
			wchar_t str[] = L"Some Text";
			CodeAnalyzer analyzer{ str };

			Assert::AreEqual(analyzer.get_blank_lines(), 0, L"Incorrect default value of blank lines");
			Assert::AreEqual(analyzer.get_code_lines(), 0, L"Incorrect default value of code lines");
			Assert::AreEqual(analyzer.get_comment_lines(), 0, L"Incorrect default value of comment lines");
			Assert::AreEqual(analyzer.get_physical_lines(), 0, L"Incorrect default value of physical lines");

			bool ok = analyzer.get_text() == str ? true : false;

			Assert::IsTrue(ok, L"Strings aren't equal");
		}

		// Test 'void StartFullAnalysis()'
		TEST_METHOD(TestStartFullAnalysis)
		{
			wchar_t code[] = LR"(#include <iostream>
using namespace std;

// This is a comment

/* This is another comment*/

int main()
{
	return 0;
})";
			CodeAnalyzer analyzer{ code };

			analyzer.StartFullAnalysis();

			Assert::AreEqual(analyzer.get_blank_lines(), 3, L"Incorrect value of blank lines");
			Assert::AreEqual(analyzer.get_code_lines(), 6, L"Incorrect value of code lines");
			Assert::AreEqual(analyzer.get_comment_lines(), 2, L"Incorrect value of comment lines");
			Assert::AreEqual(analyzer.get_physical_lines(), 11, L"Incorrect value of physical lines");
		}

		// Test 'void CountBlankLines()'
		TEST_METHOD(TestCountBlankLines)
		{
			wchar_t code[] = LR"(#include <iostream>
using namespace std;

// This is a comment

/* This is another comment*/

int main()
{
	return 0;
})";
			CodeAnalyzer analyzer{ code };

			analyzer.CountBlankLines();

			Assert::AreEqual(analyzer.get_blank_lines(), 3, L"Incorrect value of blank lines");
		}

		// Test 'void CountCommentLines()'
		TEST_METHOD(TestCountCommentLines)
		{
			wchar_t code[] = LR"(#include <iostream>
using namespace std;

// This is a comment

/* This is another comment*/

int main()
{
	return 0;
})";
			CodeAnalyzer analyzer{ code };

			analyzer.CountCommentLines();

			Assert::AreEqual(analyzer.get_comment_lines(), 2, L"Incorrect value of comment lines");
		}

		// Test 'void CountCommentLines()'
		TEST_METHOD(TestCountCodeLines)
		{
			wchar_t code[] = LR"(#include <iostream>
using namespace std;

// This is a comment

/* This is another comment*/

int main()
{
	return 0;
})";
			CodeAnalyzer analyzer{ code };

			analyzer.CountCodeLines();

			Assert::AreEqual(analyzer.get_code_lines(), 6, L"Incorrect value of code lines");
		}

		// Test 'void CountPhysicalLines()'
		TEST_METHOD(TestCountPhysicalLines)
		{
			wchar_t code[] = LR"(#include <iostream>
using namespace std;

// This is a comment

/* This is another comment*/

int main()
{
	return 0;
})";
			CodeAnalyzer analyzer{ code };

			analyzer.CountPhysicalLines();

			Assert::AreEqual(analyzer.get_physical_lines(), 11, L"Incorrect value of physical lines");
		}

		// Test 'void Reset()'
		TEST_METHOD(TestReset)
		{
			wchar_t code[] = LR"(#include <iostream>
using namespace std;

// This is a comment

/* This is another comment*/

int main()
{
	return 0;
})";
			CodeAnalyzer analyzer{ code };

			analyzer.StartFullAnalysis();

			analyzer.Reset();

			Assert::AreEqual(analyzer.get_blank_lines(), 0, L"Incorrect default value of blank lines");
			Assert::AreEqual(analyzer.get_code_lines(), 0, L"Incorrect default value of code lines");
			Assert::AreEqual(analyzer.get_comment_lines(), 0, L"Incorrect default value of comment lines");
			Assert::AreEqual(analyzer.get_physical_lines(), 0, L"Incorrect default value of physical lines");
		}

		// Test 'void set_text(const std::wstring& text)'
		TEST_METHOD(Testset_text)
		{
			wchar_t str1[] = L"Some Text";
			CodeAnalyzer analyzer{ str1 };

			wchar_t str2[] = L"Some New Text";

			analyzer.set_text(str2);

			bool ok = analyzer.get_text() == str2 ? true : false;

			Assert::IsTrue(ok, L"Strings aren't equal");
		}

		// Test 'int get_blank_lines() const'
		TEST_METHOD(Testget_blank_lines)
		{
			CodeAnalyzer analyzer;

			Assert::AreEqual(analyzer.get_blank_lines(), 0, L"Incorrect default value of blank lines");
		}

		// Test 'int get_comment_lines() const'
		TEST_METHOD(Testget_comment_lines)
		{
			CodeAnalyzer analyzer;

			Assert::AreEqual(analyzer.get_comment_lines(), 0, L"Incorrect default value of comment lines");
		}

		// Test 'int get_code_lines() const'
		TEST_METHOD(Testget_code_lines)
		{
			CodeAnalyzer analyzer;

			Assert::AreEqual(analyzer.get_code_lines(), 0, L"Incorrect default value of code lines");
		}

		// Test 'int get_blank_lines() const'
		TEST_METHOD(Testget_physical_lines)
		{
			CodeAnalyzer analyzer;

			Assert::AreEqual(analyzer.get_physical_lines(), 0, L"Incorrect default value of physical lines");
		}

		// Test 'const std::wstring& get_text() const'
		TEST_METHOD(Testget_text)
		{
			CodeAnalyzer analyzer;

			Assert::IsTrue(analyzer.get_text().empty(), L"Incorrect size of text");
		}
	};

	TEST_CLASS(TestFileReader)
	{
		// Test 'FilesHolder()'
		TEST_METHOD(TestDefaultConstructor)
		{
			FileReader reader;

			Assert::IsTrue(reader.get_file_path().empty(), L"File path is incorrect");
			Assert::IsTrue(reader.get_read_information().empty(), L"Read information is incorrect");
		}

		// Test 'FileReader(const std::wstring& file_path)'
		TEST_METHOD(TestConstructor)
		{
			const std::wstring file_path{ L"Some file path" };
			FileReader reader{ file_path };

			bool ok = reader.get_file_path() == file_path;
			
			Assert::IsTrue(ok, L"Paths aren't equal");
			Assert::IsTrue(reader.get_read_information().empty(), L"Read information is incorrect");
		}

		// Test 'void StartReading()'
		TEST_METHOD(TestStartReading)
		{
			std::wstring file_path{ LR"(D:\Private\SoftServe\Tasks\Task03 ProjectAnalyzer Class\Solution\UnitTests\TestReading.txt)" };

			FileReader reader{ file_path };

			reader.StartReading();

			Assert::IsTrue(!reader.get_read_information().empty(), L"Information haven't been read");
		}

		// Test 'void Reset()'
		TEST_METHOD(TestReset)
		{
			std::wstring file_path{ LR"(D:\Private\SoftServe\Tasks\Task03 ProjectAnalyzer Class\Solution\UnitTests\TestReading.txt)" };

			FileReader reader{ file_path };

			reader.StartReading();

			reader.Reset();

			Assert::IsTrue(reader.get_file_path().empty(), L"File path haven't been cleared");
			Assert::IsTrue(reader.get_read_information().empty(), L"Information haven't been cleared");
		}

		// Test 'void set_file_path(const std::wstring& file_path)'
		TEST_METHOD(Testset_file_path)
		{
			const std::wstring file_path{ L"Some file path" };
			FileReader reader;
			reader.set_file_path(file_path);

			bool ok = reader.get_file_path() == file_path;

			Assert::IsTrue(ok, L"Paths aren't equal");
		}

		// Test 'const std::wstring& get_read_information() const'
		TEST_METHOD(Testget_read_information)
		{
			std::wstring file_path{ LR"(D:\Private\SoftServe\Tasks\Task03 ProjectAnalyzer Class\Solution\UnitTests\TestReading.txt)" };

			FileReader reader{ file_path };

			reader.StartReading();

			Assert::IsTrue(!reader.get_read_information().empty(), L"Information haven't been read");
		}

		// Test 'const std::wstring& get_file_path() const'
		TEST_METHOD(Testget_file_path)
		{
			std::wstring file_path{ LR"(D:\Private\SoftServe\Tasks\Task03 ProjectAnalyzer Class\Solution\UnitTests\TestReading.txt)" };

			FileReader reader{ file_path };

			Assert::IsTrue(!reader.get_file_path().empty(), L"File path haven't been read");
		}
	};

	TEST_CLASS(TestFilesHolder)
	{
		// Test 'FilesHolder()'
		TEST_METHOD(TestDefaultConstructor)
		{
			FilesHolder holder;

			Assert::IsTrue(holder.get_root_directory().empty(), L"Root directory is incorrect");
		}

		// Test 'FilesHolder(const std::wstring& root_directory, const std::initializer_list<std::wstring>& extensions_for_search)'
		TEST_METHOD(TestConstructor)
		{
			std::wstring root_directory{ L"Some Directory" };
			std::initializer_list<std::wstring> extensions_for_search{ L".e", L".g" };
			FilesHolder holder{ root_directory, extensions_for_search };

			Assert::AreEqual(holder.get_root_directory(), root_directory, L"Root directory is incorrect");

			const std::vector<std::wstring>& m_extensions_for_search = holder.get_extensions_for_search();

			bool ok1 = m_extensions_for_search[0] == L".e";
			bool ok2 = m_extensions_for_search[1] == L".g";

			Assert::IsTrue(ok1, L"First extension is incorrect");
			Assert::IsTrue(ok2, L"Second extension is incorrect");
		}

		// Test 'void StartSearching()'
		TEST_METHOD(TestStartSearching)
		{
			FilesHolder holder;

			bool ok;

			try
			{
				holder.StartSearching();
				ok = false;
			}
			catch (const Wexception&)
			{
				ok = true;
			}

			Assert::IsTrue(ok, L"Root directory is incorrect");
		}

		// Test 'void set_root_directory(const std::wstring& root_directory)'
		TEST_METHOD(set_root_directory)
		{
			FilesHolder holder;

			std::wstring root_directory{ L"Some Directory" };
			holder.set_root_directory(root_directory);

			Assert::AreEqual(holder.get_root_directory(), root_directory, L"Root directory is incorrect");
		}

		// Test 'void set_extensions_for_search(const std::initializer_list<std::wstring>& extensions_for_search)'
		TEST_METHOD(Testset_extensions_for_search)
		{
			std::initializer_list<std::wstring> extensions_for_search{ L".e", L".g" };
			FilesHolder holder;

			holder.set_extensions_for_search(extensions_for_search);

			const std::vector<std::wstring>& m_extensions_for_search = holder.get_extensions_for_search();
			bool ok1 = m_extensions_for_search[0] == L".e";
			bool ok2 = m_extensions_for_search[1] == L".g";

			Assert::IsTrue(ok1, L"First extension is incorrect");
			Assert::IsTrue(ok2, L"Second extension is incorrect");
		}

		// Test 'const std::wstring& get_root_directory() const'
		TEST_METHOD(Testget_root_directory)
		{
			FilesHolder holder;

			Assert::IsTrue(holder.get_root_directory().empty(), L"Root directory is not empty");
		}

		// Test 'const std::vector<std::wstring>& get_special_files() const'
		TEST_METHOD(Testget_special_files)
		{
			FilesHolder holder;

			Assert::IsTrue(holder.get_special_files().empty(), L"Count of special files is incorrect");
		}

		// Test 'const std::vector<std::wstring>& get_extensions_for_search() const'
		TEST_METHOD(Testget_extensions_for_search)
		{
			FilesHolder holder;

			Assert::IsTrue(holder.get_extensions_for_search().empty(), L"Count of extensions is incorrect");
		}
	};

	TEST_CLASS(TestProjectAnalyzer)
	{
		// Test 'ProjectAnalyzer()'
		TEST_METHOD(TestDefaultConstructor)
		{
			ProjectAnalyzer analyzer;

			Assert::IsTrue(analyzer.get_project_path().empty(), L"Incorrect value of project path");
			Assert::AreEqual(analyzer.get_blank_lines(), 0, L"Incorrect count of blank lines)");
			Assert::AreEqual(analyzer.get_comment_lines(), 0, L"Incorrect count of comment lines)");
			Assert::AreEqual(analyzer.get_code_lines(), 0, L"Incorrect count of code lines)");
			Assert::AreEqual(analyzer.get_physical_lines(), 0, L"Incorrect count of physical lines)");
			Assert::AreEqual(analyzer.get_processed_files(), 0, L"Incorrect count of processed files)");
		}

		// Test 'ProjectAnalyzer(const std::wstring& project_path, const std::initializer_list<std::wstring>& extensions_for_search)'
		TEST_METHOD(TestConstructor)
		{
			std::wstring root_directory{ L"Some Directory" };
			std::initializer_list<std::wstring> extensions_for_search{ L".e", L".g" };
			ProjectAnalyzer analyzer{ root_directory, extensions_for_search };

			Assert::AreEqual(analyzer.get_project_path(), root_directory, L"Root directory is incorrect");
		}

		// Test 'void AnalyzeProject()'
		TEST_METHOD(TestAnalyzeProject)
		{
			std::wstring root_directory{ LR"(D:\Private\SoftServe\Tasks\Task03 ProjectAnalyzer Class\Solution\UnitTests)" };
			std::initializer_list<std::wstring> extensions_for_search{ L".cpp", L".h" };
			ProjectAnalyzer analyzer{ root_directory, extensions_for_search };

			analyzer.AnalyzeProject();

			char message[10];
			_itoa_s(analyzer.get_blank_lines(), message, 10);

			Logger::WriteMessage(message);

			Assert::IsTrue(!analyzer.get_project_path().empty(), L"Incorrect value of project path");
			Assert::AreNotEqual(analyzer.get_blank_lines(), 0, L"Incorrect count of blank lines)");
			Assert::AreNotEqual(analyzer.get_comment_lines(), 0, L"Incorrect count of comment lines)");
			Assert::AreNotEqual(analyzer.get_code_lines(), 0, L"Incorrect count of code lines)");
			Assert::AreNotEqual(analyzer.get_physical_lines(), 0, L"Incorrect count of physical lines)");
			Assert::AreNotEqual(analyzer.get_processed_files(), 0, L"Incorrect count of processed files)");
		}

		// Test 'void ResetAmounts()'
		TEST_METHOD(TestResetAmounts)
		{
			ProjectAnalyzer analyzer;

			analyzer.ResetAmounts();

			Assert::AreEqual(analyzer.get_blank_lines(), 0, L"Incorrect count of blank lines)");
			Assert::AreEqual(analyzer.get_comment_lines(), 0, L"Incorrect count of comment lines)");
			Assert::AreEqual(analyzer.get_code_lines(), 0, L"Incorrect count of code lines)");
			Assert::AreEqual(analyzer.get_physical_lines(), 0, L"Incorrect count of physical lines)");
			Assert::AreEqual(analyzer.get_processed_files(), 0, L"Incorrect count of processed files)");
		}

		// Test 'int get_processed_files() const'
		TEST_METHOD(Testget_processed_files)
		{
			ProjectAnalyzer analyzer;

			Assert::AreEqual(analyzer.get_physical_lines(), 0, L"Incorrect count of physical lines)");
		}

		// Test 'int get_blank_lines() const'
		TEST_METHOD(Testget_blank_lines)
		{
			ProjectAnalyzer analyzer;

			Assert::AreEqual(analyzer.get_blank_lines(), 0, L"Incorrect count of blank lines)");
		}

		// Test 'int get_comment_lines() const'
		TEST_METHOD(Testget_comment_lines)
		{
			ProjectAnalyzer analyzer;

			Assert::AreEqual(analyzer.get_comment_lines(), 0, L"Incorrect count of comment lines)");
		}

		// Test 'int get_code_lines() const'
		TEST_METHOD(Testget_code_lines)
		{
			ProjectAnalyzer analyzer;

			Assert::AreEqual(analyzer.get_code_lines(), 0, L"Incorrect count of code lines)");
		}

		// Test 'int get_physical_lines() const'
		TEST_METHOD(Testget_physical_lines)
		{
			ProjectAnalyzer analyzer;

			Assert::AreEqual(analyzer.get_physical_lines(), 0, L"Incorrect count of physical lines)");
		}

		// Test 'const std::wstring& get_project_path() const'
		TEST_METHOD(Testget_project_path)
		{
			ProjectAnalyzer analyzer;

			Assert::IsTrue(analyzer.get_project_path().empty(), L"Incorrect value of project path");
		}

		// Test 'void set_project_path(const std::wstring& project_path)'
		TEST_METHOD(Testset_project_path)
		{
			// holder is a private-field of ProjectAnalyzer
			FilesHolder holder;

			std::wstring root_directory{ L"Some Directory" };
			holder.set_root_directory(root_directory);

			Assert::AreEqual(holder.get_root_directory(), root_directory, L"Root directory is incorrect");
		}

		// Test 'void set_extensions_for_search(const std::initializer_list<std::wstring>& extensions_for_search)'
		TEST_METHOD(Testset_extensions_for_search)
		{
			std::initializer_list<std::wstring> extensions_for_search{ L".e", L".g" };
			FilesHolder holder;

			holder.set_extensions_for_search(extensions_for_search);

			const std::vector<std::wstring>& m_extensions_for_search = holder.get_extensions_for_search();
			bool ok1 = m_extensions_for_search[0] == L".e";
			bool ok2 = m_extensions_for_search[1] == L".g";

			Assert::IsTrue(ok1, L"First extension is incorrect");
			Assert::IsTrue(ok2, L"Second extension is incorrect");
		}
	};

	TEST_CLASS(TestWexception)
	{
		// Test 'explicit Wexception(const wchar_t* message)'
		TEST_METHOD(TestConstructor)
		{
			wchar_t message[] = L"Hello Exception";
			Wexception wexception{ message };

			bool ok = wexception.what() != nullptr;

			Assert::IsTrue(ok, L"Incorrect message");
		}

		// Test 'virtual const wchar_t* what() const noexcept'
		TEST_METHOD(Testwhat)
		{
			wchar_t message[] = L"Hello Exception";
			Wexception wexception{ message };

			bool ok = wexception.what() != nullptr;

			Assert::IsTrue(ok, L"Incorrect message");
		}
	};
}