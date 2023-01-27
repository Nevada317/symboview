#ifndef _SymbolRecordList_H
#define _SymbolRecordList_H


// #include <stdint.h>
// #include <stdbool.h>
// #include <string>
#include <list>

#include "symbolrecord.hpp"


class SymbolRecordList {
	std::list<SymbolRecord> locallist;
	std::list<SymbolRecord> functions;
	std::list<SymbolRecord> undefs;
public:
	SymbolRecordList();

	void Fill(std::string infile);

	std::list<SymbolRecord>* GetFunctions();
	std::list<SymbolRecord>* GetUndefs();
	std::list<SymbolRecord> FindMatching(bool (*criteria) (SymbolRecord& record));
};


#endif /* _SymbolRecordList_H */
