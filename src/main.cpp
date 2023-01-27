#include "symbolrecordlist.hpp"
#include "symboltaglist.hpp"

#include <stdio.h>
#include <string>

using namespace std;

SymbolTagList ByFile;
SymbolTagList ByFun;

static void HandleRecord(SymbolRecord& record) {
	SymbolTagPair* by_file = ByFile.GetTagPair(record.Filename);
	by_file->List.push_back(&record);

	SymbolTagPair* by_function = ByFun.GetTagPair(record.Name);
	by_function->List.push_back(&record);
}

int main(int argc, char *argv[]) {
	(void) argc;
	(void) argv;

	SymbolRecordList ElfSymbol;
	for (int arg = 1; arg < argc; arg++) {
		printf("ARGUMENT: %s\n", argv[arg]);
		ElfSymbol.Fill(argv[arg]);
	}


	for (SymbolRecord& record : *ElfSymbol.GetFunctions()) {
		printf("FF: %s\n", record.Name.c_str());
		HandleRecord(record);
	}
	for (SymbolRecord& record : *ElfSymbol.GetUndefs()) {
		printf("UD: %s\n", record.Name.c_str());
		HandleRecord(record);
	}

	// for (const std::string& record : ByFile.GetAllTags()) {
	// 	int records = ByFile.GetTagPair(record)->List.size();
	// 	printf("File: %s (%d)\n", record.c_str(), records);
	// }

	for (const SymbolTagPair* file : ByFile.GetList()) {
		// int records = ByFile.GetTagPair(record)->List.size();
		printf("File: %s\n", file->Tag.c_str());
		for (auto& item : file->List) {
			printf("  %s\n", item->Name.c_str());
		}
	}

	return 0;
}
