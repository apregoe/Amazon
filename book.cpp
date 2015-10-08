#include "book.h"
#include "util.h"
#include <iostream>
#include <fstream>
#include <set>
#include <string>

using namespace std;
 
Book::Book(const string category, const string name,
	double price, int qty, const string isbn,
	const string author) :
	Product(category, name, price, qty),
	isbn_(isbn),
	author_(author){}

Book::~Book(){
}

set<string> Book::keywords() const{
	set<string> keyw_total;
	set<string> keyw1 = parseStringToWords(name_);
	set<string> keyw2 = parseStringToWords(author_);
	keyw_total = setUnion(keyw1, keyw2);
	keyw_total.insert(isbn_);
	return keyw_total;
}

string Book::displayString() const{
	string price = to_string(price_);
	string qty = to_string(qty_);
	return "Name: " + name_ + "\n" + "Quantity left: " +
	qty + "\n" + "price: $" + price;
}

void Book::dump(ostream& os) const{
	Product::dump(os);
	os << isbn_ << "\n" << author_<<endl;
}