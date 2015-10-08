#ifndef REVIEW_H
#define REVIEW_H
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <string>
#include <QString>

/**
 * Models a review for the product identified by prodName
 */
struct Review
{
  Review() :  prodName(""),username(""), rating(0), date(""), reviewText(""){ }
  Review(std::string& prod, 
    std::string& username_,
	 int& rate,
	 std::string& d, 
	 std::string& review_text) :
    prodName(prod), 
    username(username_),
    rating(rate), 
    date(d), 
    reviewText(review_text){}

  void dump(std::ostream& os){
    os<<prodName<<std::endl<<rating<<" "<<username<<" "<<date<<" "<<reviewText<<std::endl;
  }

  QString displayString(){
    QString info = "Rating: " + QString::fromStdString(std::to_string(rating)) + "\n" +
      " Date: " + QString::fromStdString(date) + "\n    " + QString::fromStdString(reviewText);

    return info;
  }

  bool operator<(const Review rhs) const{
    char temp;
    int this_year;
    int rhs_year;
    int this_month;
    int rhs_month;
    int this_day;
    int rhs_day;
    std::stringstream ss;
    ss << this->date;
    ss >> this_year; // yyyy-mm-dd
    ss >> temp; // -mm-dd
    ss >> this_month; //mm-dd
    ss >> temp; // -dd
    ss >> this_day; // dd

    std::stringstream rhs_ss;
    rhs_ss << rhs.date;
    rhs_ss >> rhs_year;
    rhs_ss >> temp;
    rhs_ss >> rhs_month;
    rhs_ss >> temp;
    rhs_ss >> rhs_day;


    if(this_year < rhs_year){
      return 1;
    }
    else if(this_year > rhs_year){
      return 0;
    }
    else if(rhs_year == this_year){
      if(this_month < rhs_month)
        return 1;
      else if(this_month > rhs_month)
        return 0;
      else if (this_month == rhs_month){
        if(this_day < rhs_day)
          return 1;
        else
          return 0;
      }
    }
    return 0;//never reached
  }
  
  std::string prodName;
  std::string username;
  int rating;
  std::string date;
  std::string reviewText;
};

#endif
