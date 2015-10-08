#include "clothing.h"
#include "util.h"
#include <iostream>
#include <fstream>
#include <set>
#include <string> 
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Clothing::Clothing(const string category,
	const string name, double price, int qty,
	const string size, const string brand):
	Product(category, name, price, qty),
	size_(size),
	brand_(brand){}

set<string> Clothing::keywords() const{
	set<string> keyw1 = parseStringToWords(name_ + " " + brand_);
	return keyw1;
}

string Clothing::displayString() const{
	string price = to_string(price_);
	string qty = to_string(qty_);
	return "Name: " + name_ + "\n" + "Quantity left: " +
	qty + "\n" + "price: $" + price;
}

void Clothing::dump(ostream& os) const{
	Product::dump(os);
	os << size_ << "\n" << brand_ <<endl;
}