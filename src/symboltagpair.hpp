#ifndef _SymbolTagPair_H
#define _SymbolTagPair_H

#include "symbolrecord.hpp"

#include <string>
#include <list>

class SymbolTagPair {
public:

	std::string Tag;
	std::list<SymbolRecord*> List;

	SymbolTagPair(std::string tag) : Tag(tag), List() {};
	SymbolTagPair(): SymbolTagPair("") {};
};

#endif /* _SymbolTagList_H */
