#include <sstream>
#include <iomanip>
#include "product.h"

using namespace std;

Product::Product(const std::string category, const std::string name, double price, int qty) : 
  name_(name),
  price_(price),
  qty_(qty), 
  category_(category),
  rate_sum(0),
  total_reviews(0)
{}

Product::~Product()
{

}


double Product::getPrice() const
{
  return price_;
}

std::string Product::getName() const
{
  return name_;
}

void Product::subtractQty(int num)
{
  qty_ -= num;
}

int Product::getQty() const
{
  return qty_;
}

/**
 * default implementation...can be overriden in a future
 * assignment
 */ 
bool Product::isMatch(std::vector<std::string>& searchTerms) const
{ 
  return false;
}

void Product::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
}

double Product::getAverage()const{
  if(total_reviews == 0)
    return 0;
  else
    return rate_sum/total_reviews;
}

void Product::addrating(double const temp){
  rate_sum = rate_sum + temp;
  total_reviews = total_reviews + 1;
}

