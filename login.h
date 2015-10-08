#ifndef LOGIN_H
#define LOGIN_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QMessageBox>
#include <QApplication>
#include <QLineEdit>
#include <QLabel>
#include <map>
#include <string>
#include <QPushButton>
#include <iostream>
#include <QColor>
#include "my_datastore.h"
#include "new_user_window.h"
#include "main_window.h"

class LogIn : public QWidget{
Q_OBJECT
public:
	typedef std::map<std::string, User*> usersMap;
	LogIn(MyDataStore*);

private slots:
	void login_exit(){QApplication::quit();}
	void openMainWindow();
	void openNewUserWindow();
	void logOut();

private:
	MainWindow* main_window;
	NewUserWindow* new_user_window;
	MyDataStore* ds;

	QVBoxLayout* outercontainer;

	QLabel* imagecontainer;
	QImage human_image;

	QHBoxLayout* username_layout;
	QHBoxLayout* password_layout;
	QLabel* username_label;
	QLabel* password_label;
	QLineEdit* username_text;
	QLineEdit* password_text;

	QHBoxLayout* login_password_buttons_layout;
	QPushButton* Log_in_button;
	QPushButton* new_user_button;
	QPushButton* quit_button;

	QPushButton* LogOutButton;
};

#endif