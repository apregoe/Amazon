#include "login.h"
#include <QApplication>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip> 
#include <map>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "msort.h"
#include "login.h"
#include "my_datastore.h"

using namespace std;

int main(int argc, char* argv[]){

if(argc < 2){
	cerr << "Please specify a database file" << endl;
}

MyDataStore* ds = new MyDataStore;

// Instantiate the parser
DBParser parser;

// Instantiate the individual product parsers we want
parser.addProductParser(new ProductBookParser);
parser.addProductParser(new ProductClothingParser);
parser.addProductParser(new ProductMovieParser);

// Now parse the database to populate the DataStore
if( parser.parse(argv[1], *ds) ){
	cerr << "Error parsing!" << endl;
	return 1;
}

QApplication app(argc, argv);

LogIn login_window(ds);

login_window.show();

app.exec();
delete ds;

return 0;

}