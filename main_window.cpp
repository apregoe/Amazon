#include "main_window.h"

#include <QWidget>
#include <QApplication>
#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QRadioButton>
#include <QComboBox>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QListWidget>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iomanip> 
#include <map>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "review.h"
#include "msort.h"
#include "my_datastore.h"

using namespace std;


MainWindow::MainWindow(MyDataStore* ds_) : ds(ds_) {
	//hidding the close buttons
	setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	//outercontainer
	setWindowTitle("Trojan Store");
	outercontainer = new QVBoxLayout();
	setStyleSheet("QWidget {background-color: #000000; color: #ffffff; font-weight: bold;}");
	//searchlayout
	search_layout = new QHBoxLayout();
	search_box_label = new QLabel("Search: ");
	search_box = new QLineEdit();
	and_but = new QPushButton("AND search");
	and_but->setStyleSheet("QPushButton {background-color:#BD2031 ; color: #ffd700; font-weight: bold;}");
	or_but = new QPushButton("OR search");
	or_but->setStyleSheet("QPushButton {background-color:#ffd700 ; color: #BD2031; font-weight: bold;}");
	//Users and viewcart
	Users_viewcart_layout = new QHBoxLayout();
	viewcart_layout = new QHBoxLayout();
	current_user = new QLabel();
	user_label = new QLabel("Loged in as: ");
	user_label->setStyleSheet("QLabel {margin-left: 120px; border: 2px solid red;}");
	viewcart_but = new QPushButton("View Cart");
	viewcart_but->setStyleSheet("QPushButton {background-color:#ffd700 ; color: #BD2031; font-weight: bold;}");

	//Sorting radios, additem and add review button
	Radios_add_review_layout = new QHBoxLayout();
	additem_layout = new QHBoxLayout();
	alphasort_but = new QRadioButton("By Alphabet");
	ratesort_but = new QRadioButton("By Rating");
	Addtocart_but = new QPushButton("Add to Cart");
	Addtocart_but->setStyleSheet("QPushButton {background-color:#ffd700 ; color: #BD2031; font-weight: bold;}");
	Addreview_but = new QPushButton("Write review");
	Addreview_but->setStyleSheet("QPushButton {background-color:#BD2031 ; color: #ffd700; font-weight: bold;}");

	//hits and review list
	hits_label = new QLabel("hits:");
	hits_list= new QListWidget();
	review_label = new QLabel("reviews:");
	review_list = new QListWidget();

	//save and exit button
	save_layout = new QHBoxLayout();
	exit_but = new QPushButton("Exit");
	exit_but->setStyleSheet("QPushButton {background-color:#BD2031 ; color: #ffd700; font-weight: bold;}");
	save_but = new QPushButton("Save to a file");
	save_but->setStyleSheet("QPushButton {background-color:#ffd700 ; color: #BD2031; font-weight: bold;}");
	LogOutButton = new QPushButton("Log Out");
	LogOutButton->setStyleSheet("QPushButton {background-color:#ffd700 ; color: #BD2031; font-weight: bold;}");
	save_input_file = new QLineEdit();

	//main window interface
	search_layout->addWidget(search_box_label);
	search_layout->addWidget(search_box);
	search_layout->addWidget(and_but);
	search_layout->addWidget(or_but);
	outercontainer->addLayout(search_layout);
	Users_viewcart_layout->addWidget(user_label);
	viewcart_layout->addWidget(viewcart_but);
	Users_viewcart_layout->addLayout(viewcart_layout);
	outercontainer->addLayout(Users_viewcart_layout);
	alphasort_but->setChecked(1);
	Radios_add_review_layout->addWidget(alphasort_but);
	Radios_add_review_layout->addWidget(ratesort_but);
	additem_layout->addWidget(Addtocart_but);
	Radios_add_review_layout->addLayout(additem_layout);
	Radios_add_review_layout->addWidget(Addreview_but);
	outercontainer->addLayout(Radios_add_review_layout);
	outercontainer->addWidget(hits_label);
	outercontainer->addWidget(hits_list);
	outercontainer->addWidget(review_label);
	outercontainer->addWidget(review_list);
	save_layout->addWidget(save_but);
	save_layout->addWidget(save_input_file);
	save_layout->addWidget(exit_but);
	save_layout->addWidget(LogOutButton);
	outercontainer->addLayout(save_layout);

	//review window
		review_widget = new QWidget();
		review_window_outercontainer = new QVBoxLayout(review_widget);
		//review for: product name
			review_product_title_label = new QLabel();
		//rating 1 2 3 4
			review_rating_layout = new QHBoxLayout();
			review_rating_label = new QLabel("Rating:");
			one = new QRadioButton("1");
			one->setChecked(1);
			two = new QRadioButton("2");
			three = new QRadioButton("3");
			four = new QRadioButton("4");
			five = new QRadioButton("5");
		//date yyyy-mm-dd
			review_date_layout = new QHBoxLayout();
			review_date_label = new QLabel("Date YYYY-MM-DD");
			review_date_input = new QLineEdit();
			review_date_input->setMaxLength(10);
		//text input
			review_text = new QTextEdit();
		//publish revirew button
			Sendreview_but = new QPushButton("Publish and Exit");
			Onlyexitreview_but = new QPushButton("Exit without publishing");

	review_rating_layout->addWidget(review_rating_label);
	review_rating_layout->addWidget(one);
	review_rating_layout->addWidget(two);
	review_rating_layout->addWidget(three);
	review_rating_layout->addWidget(four);
	review_rating_layout->addWidget(five);
	review_window_outercontainer->addWidget(review_product_title_label);
	review_window_outercontainer->addLayout(review_rating_layout);
	review_date_layout->addWidget(review_date_label);
	review_date_layout->addWidget(review_date_input);
	review_window_outercontainer->addLayout(review_date_layout);
	review_window_outercontainer->addWidget(review_text);
	review_window_outercontainer->addWidget(Sendreview_but);
	review_window_outercontainer->addWidget(Onlyexitreview_but);

	//viewcart window
		viewcart_window = new QWidget();
		viewcart_outercontainer = new QVBoxLayout(viewcart_window);
		//Name Cart
			namecart_buybutton_layout = new QHBoxLayout();
			namecart_layout = new QHBoxLayout();
			QString namecart_qstring =  current_user->text() + " Cart";
			namecart_label = new QLabel(namecart_qstring);
			buycart_but = new QPushButton("Buy Cart");

		//Current balance
			balance_layout =  new QHBoxLayout();
			balance_label = new QLabel();
			balance_remove_layout = new QHBoxLayout();
			current_products_label = new QLabel("Products in cart:");
			remove_item_but = new QPushButton("Remove selected product");

		//Producuts in the cart
			cartproducts_list = new QListWidget();

		//QUIT BUTTON viewcart
			Extitcart_but = new QPushButton("Exit Cart");

	namecart_layout->addWidget(namecart_label);
	namecart_buybutton_layout->addLayout(namecart_layout);
	namecart_buybutton_layout->addWidget(buycart_but);
	viewcart_outercontainer->addLayout(namecart_buybutton_layout);
	balance_layout->addWidget(balance_label);
	viewcart_outercontainer->addLayout(balance_layout);
	balance_remove_layout->addWidget(current_products_label);
	balance_remove_layout->addWidget(remove_item_but);
	viewcart_outercontainer->addLayout(balance_remove_layout);
	viewcart_outercontainer->addWidget(cartproducts_list);
	viewcart_outercontainer->addWidget(Extitcart_but);


	//connections
	setGeometry(200,200, 400,800);
	connect(and_but, SIGNAL(clicked()), this, SLOT(andsearch()));
	connect(or_but, SIGNAL(clicked()), this, SLOT(orsearch()));
	connect(Addreview_but, SIGNAL(clicked()), this, SLOT(write_review()));
	connect(Addtocart_but, SIGNAL(clicked()), this, SLOT(add_to_cart()));
	connect(hits_list, SIGNAL(currentRowChanged(int)),this, SLOT(displayReview()));
	connect(viewcart_but, SIGNAL(clicked()), this, SLOT(cart_window()));
	connect(buycart_but, SIGNAL(clicked()), this, SLOT(buy_cart()));
	connect(save_but, SIGNAL(clicked()), this, SLOT(save_database()));
	connect(Sendreview_but, SIGNAL(clicked()), this, SLOT(save_review()));
	connect(remove_item_but, SIGNAL(clicked()), this, SLOT(remove_product()));
	connect(Extitcart_but, SIGNAL(clicked()), viewcart_window, SLOT(close()));
	connect(Onlyexitreview_but, SIGNAL(clicked()), this, SLOT(close_review()));
	connect(exit_but, SIGNAL(clicked()),this,SLOT(close_amazon()));
	connect(alphasort_but, SIGNAL(toggled(bool)), this, SLOT(changeinsort()));

	setLayout(outercontainer);
 }
void MainWindow::close_amazon(){
	QApplication::quit();
 }
MainWindow::~MainWindow(){}
void MainWindow::close_review(){
	review_widget->close();
	this->setEnabled(true);
	return;
}
void MainWindow::changeinsort(){
	review_list->clear();
	if(hits.size() > 0){
		hits_list->clear();
		if(alphasort_but->isChecked()){
			mergeSort(hits, comp_alpha);
		}
		else{
			mergeSort(hits, comp_rate);
			reverse(hits.begin(), hits.end());
		}

		for(unsigned int i = 0; i < hits.size(); ++i){
			string item = hits[i]->displayString() + "\n" + " avg rating = "+ to_string(hits[i]->getAverage());
			QString qitem = QString::fromStdString(item);
			hits_list->addItem(qitem);
		}
	}
 }
void MainWindow::remove_product(){
	if(cartproducts_list->currentRow() != -1){
		map<string, vector<Product*> >::iterator it = Carts.find(current_user->text().toStdString());
		if(it != Carts.end()){
			it->second.erase(it->second.begin() + cartproducts_list->currentRow());
		}
		review_list->clear();
		display_cart();
	}
 }
void MainWindow::andsearch(){
	if(search_box->text().isEmpty()){
		MyMessageBox msgBox;
		msgBox.setWindowTitle("Search input failed");
		msgBox.setText("Search box is empty, write somethin in it first");
		msgBox.exec();
		return;
	}

	string cmd = search_box->text().toStdString();
	stringstream ss;

	ss << cmd;
	hits.clear();
	vector<string> terms;
	cmd.clear();
	while(ss >> cmd){
		cmd = convToLower(cmd);
		terms.push_back(cmd);
		cmd.clear();
	}
	hits = ds->search(terms, 0);
	displayhits();
 }
void MainWindow::orsearch(){
	if(search_box->text().isEmpty()){
		MyMessageBox msgBox;
		msgBox.setWindowTitle("Search input failed");
		msgBox.setText("\" Search box in empty, write somethin in it first\"");
		msgBox.exec();

		return;
	}

	hits.clear();
	string cmd = search_box->text().toStdString();
	stringstream ss;
	ss << cmd;
	vector<string> terms;
	cmd.clear();
	while(ss >> cmd){
		cmd = convToLower(cmd);
		terms.push_back(cmd);
		cmd.clear();
	}
	hits = ds->search(terms, 1);
	displayhits();
 }
void MainWindow::displayhits(){
	review_list->clear();
	if(hits.size() > 0){
		hits_list->clear();
		if(alphasort_but->isChecked()){
			mergeSort(hits, comp_alpha);
		}
		else{
			mergeSort(hits, comp_rate);
			reverse(hits.begin(), hits.end());//from algorith library..
		}

		for(unsigned int i = 0; i < hits.size(); ++i){
			string item = hits[i]->displayString() + "\n" + " avg rating = "+ to_string(hits[i]->getAverage());
			QString qitem = QString::fromStdString(item);
			hits_list->addItem(qitem);
		}
	}
	else{
		hits_list->clear();
		MyMessageBox msgBox;
		msgBox.setWindowTitle("Search Prompt");
		msgBox.setText("No results were found, sorry");
		msgBox.exec();
	}
 }
void MainWindow::write_review(){
	one->setChecked(1);
	review_date_input->clear();
	review_text->clear();

	if(hits_list->currentRow() == -1){
		MyMessageBox msgBox;
		msgBox.setWindowTitle("Review Prompt");
		msgBox.setText(" First, select a product from the list");
		msgBox.exec();
		return;
	}

	QString product_name("Product name: ");
	review_product_title_label->setText(product_name + 
		QString::fromStdString(hits[hits_list->currentRow()]->getName()));
	review_widget->setWindowTitle(QString::fromStdString(hits[hits_list->currentRow()]->getName()));
	review_widget->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	this->setEnabled(false);
	review_widget->show();
 }
void MainWindow::save_review(){

	Product* temp = hits[hits_list->currentRow()];
	int rating_ = 0;
	if(one->isChecked())
		rating_ = 1;
	else if(two->isChecked())
		rating_ = 2;
	else if(three->isChecked())
		rating_ = 3;
	else if(four->isChecked())
		rating_ = 4;
	else if(five->isChecked())
		rating_ = 5;

	string date_= review_date_input->text().toStdString();
	stringstream ss;
	ss << date_;
	int year;
	int month;
	int day;
	char dash;
	temp->addrating(double(rating_));
	ss >> year;
	if(year < 1000){
		MyMessageBox msgBox;
		msgBox.setWindowTitle("Review Prompt");
		msgBox.setText("Please correctly enter the date YYYY-MM-DD");
		msgBox.exec();
		return;
	}
	ss >> dash;
	if(dash != '-'){
		MyMessageBox msgBox;
		msgBox.setWindowTitle("Review Prompt");
		msgBox.setText("Please correctly enter the date YYYY-MM-DD");
		msgBox.exec();
		return;
	}
	ss >> month;
	if(month > 12){
		MyMessageBox msgBox;
		msgBox.setWindowTitle("Review Prompt");
		msgBox.setText("Please correctly enter the date YYYY-MM-DD");
		msgBox.exec();
		return;
	}
	ss >> dash;
	if(dash != '-'){
		MyMessageBox msgBox;
		msgBox.setWindowTitle("Review Prompt");
		msgBox.setText("Please correctly enter the date YYYY-MM-DD");
		msgBox.exec();
		return;
	}
	ss >> day;
	if(day > 31){
		MyMessageBox msgBox;
		msgBox.setWindowTitle("Review Prompt");
		msgBox.setText("Please correctly enter the date YYYY-MM-DD");
		msgBox.exec();
		return;
	}

	Review* new_review = new Review();
	new_review->prodName = temp->getName();
	new_review->username = current_user->text().toStdString();
	new_review->rating = rating_;
	new_review-> date = review_date_input->text().toStdString();
	new_review->reviewText = review_text->toPlainText().toStdString();

	ds->addReview(new_review);

	review_widget->close();
	this->setEnabled(true);
	displayhits();//update reviews
 }
void MainWindow::displayReview(){
	if(hits_list->currentRow() != -1){
		review_list->clear();
		map<string, vector<Review*> >::iterator it = ds->review_map.find(hits[hits_list->currentRow()]->getName());
		if(it == ds->review_map.end())
			return;
		else{
			mergeSort(it->second, comp_review);
			for(unsigned int i = 1; i <= (it)->second.size(); ++i)
				review_list->addItem(((it)->second.at((it)->second.size() - i))->displayString());
		}
	}
 }
void MainWindow::add_to_cart(string username, Product* prod){
	map<string, vector<Product*> >::iterator it = Carts.find(username);
	if(it == Carts.end()){
		vector<Product*> new_product;
		new_product.push_back(prod);
		Carts.insert(make_pair(username, new_product));
	}
	else{
		(it->second).push_back(prod);
	}
}
void MainWindow::add_to_cart(){

	if(hits_list->currentRow() == -1){
		MyMessageBox msgBox;
		msgBox.setWindowTitle("Add to cart Prompt");
		msgBox.setText(" First, select a product from the list");
		msgBox.exec();
		return;
	}

	string username_string = current_user->text().toStdString();
	map<string, vector<Product*> >::iterator it = Carts.find(username_string);
	if(it == Carts.end()){
		vector<Product*> new_product;
		new_product.push_back(hits[hits_list->currentRow()]);
		Carts.insert(make_pair(username_string, new_product));
	}
	else{
		(it->second).push_back(hits[hits_list->currentRow()]);
	}
 }
void MainWindow::cart_window(){

	User* it = ds->search_user(current_user->text().toStdString());
	QString balance_qstring = "Current balance: $" +QString::fromStdString(to_string(it->getBalance()));
	balance_label->setText(balance_qstring);
	viewcart_window->setWindowTitle(QString::fromStdString(it->getName()) + " Cart");
	QString namecart_qstring =  current_user->text() + " Cart";
	namecart_label->setText(namecart_qstring);
	display_cart();
	viewcart_window->show();
 }
void MainWindow::display_cart(){
	cartproducts_list->clear();
	map<string, vector<Product*> >::iterator it = Carts.find(current_user->text().toStdString());
	if(it != Carts.end()){
		for(unsigned int i = 0; i < it->second.size(); ++i){
			string item = it->second[i]->displayString();
			QString qitem = QString::fromStdString(item);
			cartproducts_list->addItem(qitem);
		}
	}
 }
void MainWindow::buy_cart(){
	User* user_ = ds->search_user(current_user->text().toStdString());
	map<string, vector<Product*> >::iterator it = Carts.find(current_user->text().toStdString());
	if(it != Carts.end()){
		if(it->second.size() != 0){
			vector<Product*>::iterator it_product = (it->second).begin();
			while(it_product != (it->second).end()){
				if((*it_product)->getQty() >= 1){
					if(user_->getBalance() >= (*it_product)->getPrice()){
						user_->deductAmount((*it_product)->getPrice());
						(*it_product)->subtractQty(1);
						(it->second).erase(it_product);
					}
					else{
						++it_product;
					}
				}
				else{
					++it_product;
				}
			}
		}
		else{
			MyMessageBox msgBox;
			msgBox.setWindowTitle("Buy cart Prompt");
			msgBox.setText("You need to add something, bro");
			msgBox.exec();
			return;
		}
	}
	else{
		MyMessageBox msgBox;
		msgBox.setWindowTitle("Buy cart Prompt");
		msgBox.setText("You need to add something, bro");
		msgBox.exec();
		return;
	}
	QString balance_qstring = "Current balance: $" + QString::fromStdString(to_string(user_->getBalance()));
	balance_label->setText(balance_qstring);
	display_cart();
 }
void MainWindow::save_database(){
	if(save_input_file->text() == ""){
		MyMessageBox msgBox;
		msgBox.setWindowTitle("Save to file Prompt");
		msgBox.setText("I need a filename first, thanks");
		msgBox.exec();
		return;
	}
	else{
		ofstream ofile(save_input_file->text().toStdString().c_str());
	  	ds->dump(ofile);
	  	ofile.close();
		MyMessageBox msgBox;
		msgBox.setWindowTitle("Save to file");
		msgBox.setText(QString("Saved database as: ") + save_input_file->text());
		msgBox.exec();
		save_input_file->clear();
	}
 }
void MainWindow::show(string name){
	current_user->setText(QString::fromStdString(name));
	QString label = QString::fromStdString(user_label->text().toStdString() + " " + current_user->text().toStdString());
	user_label->setText(label);
	User* it = ds->search_user(current_user->text().toStdString());
	QString balance_qstring = "Current balance: $" +QString::fromStdString(to_string(it->getBalance()));
	balance_label->setText(balance_qstring);
	QWidget::show();
	Product* product_recommended = ds->calc_basic_similarities(name);
	if(product_recommended != NULL){
		RecWindow* rec_window = new RecWindow(this, product_recommended, name);
		rec_window->show();
		this->setEnabled(false);
	}
	else if(product_recommended==NULL){
		MyMessageBox m("No recommendation", "Hi "+name+", we could not find any reccomendation.\n Sorry");
	}
 }