#include "movie.h"
#include "util.h"
#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;  

Movie::Movie(const string category, const string name, double price, int qty, const string genre, const string rating):
	Product(category, name, price, qty),
	genre_(genre),
	rating_(rating){}

set<string> Movie::keywords() const{
	set<string> keyw_total;
	set<string> keyw1 = parseStringToWords(name_);
	keyw_total = setUnion(keyw1, keyw_total);
	keyw_total.insert(convToLower(genre_));
	return keyw_total;
}

string Movie::displayString()const{
	string price = to_string(price_);
	string qty = to_string(qty_);
	return "Name: " + name_  + "\n" + " Quantity left: " +
	qty + "\n" + "price: $" + price;
}

void Movie::dump(ostream& os) const{
	Product::dump(os);
	os<< genre_ << "\n" << rating_ <<endl;
}