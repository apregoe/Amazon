#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <stdio.h>
#include <stdlib.h> 

class Movie : public Product{
public:
	Movie(const std::string, const std::string,
	double, int, const std::string,
	const std::string);
	std::set<std::string> keywords() const;
	std::string displayString() const;
	void dump(std::ostream& os) const;
private:
	std::string genre_, rating_;
};
#endif