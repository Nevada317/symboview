#include "symboltaglist.hpp"

const std::list<SymbolTagPair*> SymbolTagList::GetList() {
	return List;
}

const std::list<std::string> SymbolTagList::GetAllTags() {
	std::list<std::string> res;
	for (SymbolTagPair* item : List) {
		res.push_back(item->Tag);
	}
	return res;
}

SymbolTagPair* SymbolTagList::GetTagPair(std::string Tag) {
	for (SymbolTagPair* item : List) {
		if (item->Tag == Tag) {
			return item;
		}
	}
	SymbolTagPair* newOne = new SymbolTagPair(Tag);
	List.push_back(newOne);
	return newOne;
}
