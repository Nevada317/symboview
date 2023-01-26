#ifndef _SymbolTagList_H
#define _SymbolTagList_H

#include "symbolrecord.hpp"

#include <string>
#include <list>

class SymbolTagList {
public:

	std::string Tag;
	std::list<SymbolRecord> List;

	SymbolTagList(std::string tag) : Tag(tag), List() {};
	SymbolTagList(): SymbolTagList("") {};
};

#endif /* _SymbolTagList_H */
