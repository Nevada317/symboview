#ifndef _SymbolTagList_H
#define _SymbolTagList_H

#include "symboltagpair.hpp"

#include <string>
#include <list>

class SymbolTagList {
	std::list<SymbolTagPair*> List;
public:
	SymbolTagPair* GetTagPair(std::string Tag);
	const std::list<SymbolTagPair*> GetList();
	const std::list<std::string> GetAllTags();
};

#endif /* _SymbolTagList_H */
