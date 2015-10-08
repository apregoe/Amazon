#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include <iostream>
#include <fstream>
#include <set>
#include <string> 

class Book : public Product{
public:
	Book(const std::string, const std::string,
	double, int, const std::string,
	const std::string);
	~Book();
	std::set<std::string> keywords() const;
	std::string displayString() const;
	void dump(std::ostream& os) const;
private:
	std::string isbn_, author_;
};
#endif
