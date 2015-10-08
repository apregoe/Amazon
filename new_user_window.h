#ifndef NEW_USER_WINDOW_H
#define NEW_USER_WINDOW_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QMessageBox>
#include <QApplication>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>
#include <QString>
#include <map>
#include <string>
#include <QPushButton>
#include <iostream>
#include <QColor>
#include "main_window.h"

class NewUserWindow : public QWidget{
	Q_OBJECT
	public:
		typedef std::map<std::string, User*> usersMap;
		NewUserWindow(QWidget*, std::string, int, MyDataStore*);

		//accessors
		QString ageInput(){return age_lineedit->text();}
		QString creditInput(){return credit_lineedit->text();}
		QString typeInput(){return type_lineedit->text();}

	private slots:
		void exit_();
		void close_nosave();
		
	private:

		//user info
		std::string username;
		int hashed_password;
		MyDataStore* ds;


		//layout
		QVBoxLayout* outercontainer;
		QWidget* parent;

		QLabel* salute_label;
		QLabel* age_label;
		QLineEdit* age_lineedit;
		QLabel* credit_label;
		QLineEdit* credit_lineedit;
		QLabel* type_label;
		QLineEdit* type_lineedit;

		QHBoxLayout* buttons_layout;
		QPushButton* close_nosave_button;
		QPushButton* finish_button;
};

#endif