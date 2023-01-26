#include "symbolrecordlist.hpp"

#include <stdio.h>
#include <string>

using namespace std;
int main(int argc, char *argv[]) {
	(void) argc;
	(void) argv;

	SymbolRecordList ElfSymbol;
	for (int arg = 1; arg < argc; arg++) {
		printf("ARGUMENT: %s\n", argv[arg]);
		ElfSymbol.Fill(argv[arg]);
	}

	return 0;
}
