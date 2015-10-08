#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

int hash(std::string c){

	long long int id = 0;
	int i = c.length() -1;
	int j = 0;
	while(i >= 0){
		id += (long long)((int(c[i]))*(pow((long long)128,j)));
		--i;
		++j;
	}
	unsigned int digits[4] = {0};
	for(int i = 3; i >=0; --i){
		digits[i]=id%65521;
		id = id/65521;
	}

	return ((digits[0]*45912)+ (digits[1]*35511) + (digits[2]*65169) +(digits[3]*4625))%65521;
}

#endif