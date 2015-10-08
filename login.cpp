#include "login.h"
#include "hash.h"
using namespace std;


LogIn::LogIn(MyDataStore* ds_){
	ds = ds_;
	main_window = NULL;
	//shifting log in window
    move(600, 300);
    new_user_window = NULL;//Will be initialized later

	setWindowTitle ("TrojanStore - Log in .v.");
	//css rocks
	setStyleSheet("QWidget{background-color: rgb(0, 0, 0);}");
	outercontainer = new QVBoxLayout(this);

	human_image.load("img/usc.png");
	imagecontainer = new QLabel();
	imagecontainer->setPixmap(QPixmap::fromImage(human_image.scaled(150,150)));
	imagecontainer->setStyleSheet("QLabel{margin: auto; margin-top:0px; margin-bottom:0px;}");//css

	username_layout = new QHBoxLayout();
	password_layout = new QHBoxLayout();
	username_label = new QLabel("Username: ");
	password_label = new QLabel("Password: ");
	username_label->setStyleSheet("QLabel {color: rgb(255, 255, 255);}");
	password_label->setStyleSheet("QLabel {color: rgb(255, 255, 255);}");
	username_text = new QLineEdit();
	username_text->setPlaceholderText("Username");
	username_text->setStyleSheet("QLineEdit {background-color: rgb(255, 215, 0); color: rgb(189, 32, 49);}");//found this on internet, I know it is like CSS :)
	password_text = new QLineEdit();
	password_text->setPlaceholderText("Password");
	password_text->setEchoMode(QLineEdit::Password);//password mode
	password_text->setMaxLength(8);
	password_text->setStyleSheet("QLineEdit {background-color: rgb(189, 32, 49); color:rgb(255, 215, 0);}");//found this on internet.
	
	login_password_buttons_layout = new QHBoxLayout();
	Log_in_button = new QPushButton("Log in");
	Log_in_button->setStyleSheet("QPushButton { background-color: rgb(189, 32, 49); color:rgb(255, 215, 0); font-weight: bold;}");// Yes, is just like css.
	new_user_button = new QPushButton("New User");
	new_user_button->setStyleSheet("QPushButton { background-color: rgb(255, 215, 0); color:rgb(189, 32, 49);font-weight: bold;}");
	quit_button = new QPushButton("Quit");
	quit_button->setStyleSheet("QPushButton { border: 2px solid red; background-color: rgb(0, 0, 0); color:rgb(255, 215, 0);font-weight: bold;}");

	//setting up log in window
	outercontainer->addWidget(imagecontainer);
	username_layout->addWidget(username_label);
	username_layout->addWidget(username_text);
	password_layout->addWidget(password_label);
	password_layout->addWidget(password_text);
	outercontainer->addLayout(username_layout);
	outercontainer->addLayout(password_layout);
	login_password_buttons_layout->addWidget(Log_in_button);
	login_password_buttons_layout->addWidget(new_user_button);
	outercontainer->addLayout(login_password_buttons_layout);
	outercontainer->addWidget(quit_button);
	
	connect(quit_button, SIGNAL(clicked()),this,SLOT(login_exit()));
	connect(Log_in_button, SIGNAL(clicked()), this, SLOT(openMainWindow()));
	connect(new_user_button, SIGNAL(clicked()), this, SLOT(openNewUserWindow()));
	setLayout(outercontainer);
}

void LogIn::logOut(){
	username_text->clear();
	password_text->clear();
	main_window->close();
	this->show();
}

void LogIn::openNewUserWindow(){

	User* it = ds->search_user(username_text->text().toStdString());
	if(it != NULL){
		MyMessageBox prompt("User conflict", "This user already exists, please change it.");
		return;
	}

	if(username_text->text().isEmpty() || password_text->text().isEmpty()){
		MyMessageBox prompt("Input Fail", "You need to fill both inputs");
		return;
	}

	string pass = password_text->text().toStdString();
	//checking if the entered password has whitespace(s)
	for(unsigned int i = 0; i < pass.size(); ++i){
		if(pass[i] == ' '){
			MyMessageBox prompt("Password Fail", "The password cannot have whitespace(s)");
			return;
		}
	}

	if (new_user_window == NULL){
		new_user_window = new NewUserWindow(this, username_text->text().toStdString(),
			::hash(password_text->text().toStdString()), ds);
	}
	else{
		delete new_user_window;
		new_user_window = new NewUserWindow(this, username_text->text().toStdString(),
			::hash(password_text->text().toStdString()), ds);
	}
	new_user_window->show();
}

void LogIn::openMainWindow(){
	string current_input = username_text->text().toStdString();
	string pass_input = password_text->text().toStdString();
	if(current_input.size() == 0){
		MyMessageBox msgBox("Username fail",
		"Username text field is empty.\n Write somethin in it first");
		return;
	}
	else if(pass_input.size()==0){
		MyMessageBox msgBox("Password fail",
		"Password text field is empty.\n Write somethin in it first");
		return;
	}
	User* it = ds->search_user(current_input);
	if(it != NULL){
		main_window = new MainWindow(ds);
		LogOutButton = main_window->getLogoutButton();
		connect(LogOutButton, SIGNAL(clicked()), this, SLOT(logOut()));
		/*the "::" in "::hash(string)" was necessary because it was giving me an error:
		  "error: reference to ‘hash’ is ambiguous"*/
		if(it->assertPass(::hash(pass_input))){
			this->hide();
			main_window->show(current_input);
		}
		else{
			MyMessageBox msgBox("Password fail",
			"Wrong password bro.");
			return;		
		}
	}
	else{
		MyMessageBox msgBox("Username fail",
		"This username does not exists.");
		return;
	}
}