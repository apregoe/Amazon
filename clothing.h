#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include <iostream>
#include <fstream>
#include <set> 
#include <string>

class Clothing : public Product{
public:
	Clothing(const std::string, const std::string,
	double, int, const std::string,
	const std::string);
	std::set<std::string> keywords() const;
	std::string displayString() const;
	void dump(std::ostream& os) const;
private:
	std::string size_, brand_;
};
#endif