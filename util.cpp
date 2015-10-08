#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm> 
#include "util.h"

using namespace std;

void filter_(string&, set<string>&);//primarly and recursive function of finds a punctuation_
void del_marginpunct(string&);//deletes punctuation at end sides of the word
bool punctuation_(string&);//return 1 finds any punctuation_ and changes it from '-' to ' '
void up_to_low(string&);//uppercase to lower case
bool has_middle_punct(string); //return 0 if finds a punctuation, except for '-'

string convToLower(string src) 
{
  transform(src.begin(), src.end(), src.begin(), ::tolower);
  return src;
}

/** Complete the code to convert a string containing a rawWord 
    to a set of words based on the criteria given in the assignment **/
set<string> parseStringToWords(string rawWord) 
{
	set<string> allwords;
	filter_(rawWord, allwords);//all the work is done here
	return allwords;
}
//primsrly function
void filter_(string& word, set<string> & allwords){
	if(punctuation_(word)){//return 1 finds any punctuation_ and changes it from '-' to ' '
		stringstream edited;
		string word1;
		edited << word;
		while(edited >> word1)//"hello-world-blah" is now "hello world blah" 
			filter_(word1, allwords);//recursinve call
	}
	else{
		if(word.size() < 2)
			return;
		string low_word = convToLower(word);//uppercase to lower case
		allwords.insert(low_word);
	}
}

//return 1 finds any punctuation_ and changes it from puntuation to ' '
bool punctuation_(string& word){
	int size = word.size();
	bool punctuation_ = 0;
	for(int i = 1; i < size-1; i++){
		if(ispunct(word[i]) != 0){
			word[i] = ' ';
			punctuation_ = 1;
		}
		else if(word[i] == ' ')
			punctuation_ =1;	
	}
	return punctuation_; //"hello-world,blah" is now "hello world blah" 
}