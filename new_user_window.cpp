#include "new_user_window.h"
#include <sstream>

using namespace std;

NewUserWindow::NewUserWindow(QWidget* parent_, string name, int p, MyDataStore* ds_) :
	username(name), hashed_password(p){
	move(300,300);
	ds = ds_;
	setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	parent = parent_;
	setStyleSheet("QWidget {background-color: rgb(0, 0, 0); color: #BD2031; font-weight: bold;}");	
	parent->setEnabled( false );
	outercontainer = new QVBoxLayout();

	string x = "Hello " + name +"\n Enter the followig data:";
	QString salute_qstring = QString::fromStdString(x);
	salute_label = new QLabel();
	salute_label->setText(salute_qstring);
	salute_label->setStyleSheet("QLabel {color: #ffd700; font-weight: bold;}");

	age_label = new QLabel("Age:");
	age_lineedit = new QLineEdit();
	age_lineedit->setMaxLength(3);
	age_lineedit->setPlaceholderText("Age");
	age_lineedit->setStyleSheet("QLineEdit {background-color: #ffd700; color:#BD2031; }");

	credit_label = new QLabel("Credit amomunt");
	credit_lineedit = new QLineEdit();
	credit_lineedit->setPlaceholderText("Credit $");
	credit_lineedit->setStyleSheet("QLineEdit {background-color: #ffd700; color:#BD2031; }");

	type_label = new QLabel("User Type:");
	type_lineedit = new QLineEdit();
	type_lineedit->setPlaceholderText("user type: 0 x-or 1");
	type_lineedit->setMaxLength(1);
	type_lineedit->setStyleSheet("QLineEdit {background-color: #ffd700; color:#BD2031; }");

	buttons_layout = new QHBoxLayout();
	finish_button = new QPushButton("Save and Exit");
	finish_button->setStyleSheet("QPushButton {background-color: #BD2031; color: #ffd700; font-weight: bold;}");
	close_nosave_button = new QPushButton("Exit w/o Save");
	close_nosave_button->setStyleSheet("QPushButton {background-color:#ffd700 ; color: #BD2031; font-weight: bold;}");

	outercontainer->addWidget(salute_label);
	outercontainer->addWidget(age_label);
	outercontainer->addWidget(age_lineedit);
	outercontainer->addWidget(credit_label);
	outercontainer->addWidget(credit_lineedit);
	outercontainer->addWidget(type_label);
	outercontainer->addWidget(type_lineedit);
	buttons_layout->addWidget(close_nosave_button);
	buttons_layout->addWidget(finish_button);
	outercontainer->addLayout(buttons_layout);

	connect(finish_button, SIGNAL(clicked()), this, SLOT(exit_()));
	connect(close_nosave_button, SIGNAL(clicked()), this, SLOT(close_nosave()));

	setLayout(outercontainer);
}

void NewUserWindow::exit_(){
	if(age_lineedit->text().isEmpty() || credit_lineedit->text().isEmpty() || type_lineedit->text().isEmpty()){
		MyMessageBox prompt("User data failed", "No input should be empty. User not created");
		return;
	}
	int age;
	stringstream ssage;
	ssage << age_lineedit->text().toStdString();
	ssage >> age;
	if(ssage.fail()){
		MyMessageBox prompt("Age Input fail", "Age should be an integer. User not created");
		return;
	}
	
	int credit;
	stringstream sscredit;
	sscredit << credit_lineedit->text().toStdString();
	sscredit >> credit;
	if(sscredit.fail()){
		MyMessageBox prompt("Credit Input fail", "Credit should be an number. User not created");
		return;
	}

	int type;
	stringstream sstype;
	sstype << type_lineedit->text().toStdString();
	sstype >> type;
	if(sstype.fail()){
		MyMessageBox prompt("Type Input fail", "Credit should be an integer [0,1]. User not created");
		return;
	}

	if((type > 1) || (type < 0)){
		MyMessageBox prompt("Type Input fail", "Type should be an integer [0,1]. User not created");
		return;
	}

	User* newuser = new User(username, age, credit, type, hashed_password);
	ds->addUser(newuser);
	parent->setEnabled(true);
	this->close();
}

void NewUserWindow::close_nosave(){
	MyMessageBox prompt("User ni created", "The user was not created!");
	parent->setEnabled(true);
	this->close();
}