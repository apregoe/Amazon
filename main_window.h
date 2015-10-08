#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QApplication>
#include <QMessageBox>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <unordered_map>
#include <QPushButton>
#include <QListWidget>
#include <QRadioButton>
#include <QComboBox>
#include <string>
#include <vector>
#include "msort.h"
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "my_datastore.h"

class MainWindow : public QWidget {
	
Q_OBJECT
public:
	MainWindow(MyDataStore*);
	~MainWindow();
	void show(std::string);//exceute the main window
	void add_to_cart(std::string, Product*);

private slots:

	void andsearch();
	void orsearch();
	void displayhits();
	void write_review();
	void displayReview();
	void add_to_cart();
	void cart_window();
	void display_cart();
	void save_database();
	void buy_cart();
	void save_review();
	void remove_product();
	void changeinsort();
	void close_amazon();
	void close_review();

private:
	//Products, carts, hits, comparator,  etc...
	MyDataStore* ds;
	std::vector<Product*> hits;
	std::map<std::string, std::vector<Product*> > Carts;
	std::vector<Review*> reviews_vector;
	AlphaStrComp comp_alpha;
	ReviewComp comp_review;
	RateComt comp_rate;

	//outercontainer
	QVBoxLayout* outercontainer;

	//search and or
	QHBoxLayout* search_layout;
	QLabel* search_box_label;
	QLineEdit* search_box;
	QPushButton* and_but;
	QPushButton* or_but; 

	//Users and viewcart
	QHBoxLayout* Users_viewcart_layout;
	QHBoxLayout* viewcart_layout;
	QLabel* user_label;
	QLabel* current_user;
	QPushButton* viewcart_but;

	//Sorting radios, additem and add review button
	QHBoxLayout* Radios_add_review_layout;
	QHBoxLayout* additem_layout;
	QRadioButton* alphasort_but;
	QRadioButton* ratesort_but;
	QPushButton* Addtocart_but;
	QPushButton* Addreview_but;

	//hits and review list
	QLabel* hits_label;
	QListWidget* hits_list;
	QLabel* review_label;
	QListWidget* review_list;

	//save file and exit button
	QHBoxLayout* save_layout;
	QPushButton* save_but;
	QLineEdit* save_input_file;
	QPushButton* exit_but;
	QPushButton* LogOutButton;

	//review window
		QWidget* review_widget;
		QVBoxLayout* review_window_outercontainer;
		//review for: product name
			QLabel* review_product_title_label;
		//rating 1 2 3 4
			QHBoxLayout* review_rating_layout;
			QLabel* review_rating_label;
			QRadioButton* one;
			QRadioButton* two;
			QRadioButton* three;
			QRadioButton* four;
			QRadioButton* five;
		//date yyyy-mm-dd
			QHBoxLayout* review_date_layout;
			QLabel* review_date_label;
			QLineEdit* review_date_input;
		//review text
			QTextEdit* review_text;
		//Send button
			QPushButton* Sendreview_but;
			QPushButton* Onlyexitreview_but;

	//view cart window
		QWidget* viewcart_window;
		QVBoxLayout* viewcart_outercontainer;
		//Name Cart
			QHBoxLayout* namecart_buybutton_layout;
			QHBoxLayout* namecart_layout;
			QLabel* namecart_label;
			QPushButton* buycart_but;

		//Current balance and products in carts labels
			QHBoxLayout* balance_layout;
			QLabel* balance_label;
			QHBoxLayout* balance_remove_layout;
			QLabel* current_products_label;
			QPushButton* remove_item_but;

		//Producuts in the cart
			QListWidget* cartproducts_list;

		//QUIT BUTTON viewcart
			QPushButton* Extitcart_but;
	public:
		QPushButton* getLogoutButton(){return LogOutButton;}

};

class MyMessageBox : public QMessageBox {
	Q_OBJECT
	public:
	MyMessageBox(std::string title, std::string content){
		setWindowTitle(QString::fromStdString(title));
		setText(QString::fromStdString(content));
		setStyleSheet("QMessageBox{background-color: #BD2031; color: rgb(255, 215, 0); font-weight:bold;}");
		exec();
	}
	MyMessageBox(){
		setStyleSheet("QMessageBox{background-color: #BD2031; color: rgb(255, 215, 0); font-weight:bold;}");
	}
};

class RecWindow : public QWidget {
	Q_OBJECT
	public:
	RecWindow(MainWindow* parent_, Product* p_, std::string u_){
		parent = parent_; product = p_; user = u_;
		setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
		setWindowTitle("Product Recomendation");
		//initializing
		outercontainer = new QVBoxLayout();
		Salute_label = new QLabel("Hello! \n Here is the recommendation of the day:");
		std::string pinfo_string = "Name: "+p_->getName()+"\n"+"Price: $"+
			std::to_string(p_->getPrice())+"\n"+"Average Rating: "+
			std::to_string(p_->getAverage());
		product_info_label = new QLabel(QString::fromStdString(pinfo_string));
		button_layout = new QVBoxLayout();
		noThanks_button = new QPushButton("No Thanks");
		addToCart_button = new QPushButton("Add to Cart");

		//Make it cool bro
		setStyleSheet("QWidget{background-color: #000000; font-weight: bold;}");
		Salute_label->setStyleSheet("QLabel{color: #BD2031;}");
		product_info_label->setStyleSheet("QLabel{color: #ffd700;}");
		noThanks_button->setStyleSheet("QPushButton{background-color:#ffd700;color:#BD2031;}");
		addToCart_button->setStyleSheet("QPushButton{background-color:#BD2031;color:#ffd700;}");

		//layout
		outercontainer->addWidget(Salute_label);
		outercontainer->addWidget(product_info_label);
		button_layout->addWidget(noThanks_button);
		button_layout->addWidget(addToCart_button);
		outercontainer->addLayout(button_layout);
		
		//connect buttons
		connect(addToCart_button, SIGNAL(clicked()), this, SLOT(addtocart()));
		connect(noThanks_button, SIGNAL(clicked()), this, SLOT(exit_()));


		setLayout(outercontainer);
	}

	private slots:
	void addtocart(){
		parent->add_to_cart(user, product);
		exit_();
	}
	void exit_(){
		parent->setEnabled(true);
		this->close();
		delete this;
	}

	private:
	MainWindow* parent;
	Product* product;
	std::string user;

	QVBoxLayout* outercontainer;

	QLabel* Salute_label;
	QLabel* product_info_label;

	QVBoxLayout* button_layout;
	QPushButton* noThanks_button;
	QPushButton* addToCart_button;
};

#endif