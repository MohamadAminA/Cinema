#ifndef ADMIN_LOGIN_H
#define ADMIN_LOGIN_H
#include "QString"
#include <QMainWindow>
#include "QFile"
#include "QTextStream"
#include <QMessageBox>
#include <QDialog>
#include "admin.h"
#include "mainwindow.h"

namespace Ui {
class admin_login;
}

class admin_login : public QMainWindow
{
	Q_OBJECT

public:
	explicit admin_login(QWidget *parent = 0);
	~admin_login();
	class Admin_User{
	public:
		QString UserName;
		QString Password;
		QString Name;
	};

private slots:
	void on_pushButton_Login_clicked();

	void on_actionExit_triggered();

	void on_actionReload_triggered();

	void on_checkBox_2_stateChanged();

	void on_actionBack_triggered();

protected:
	void resizeEvent(QResizeEvent* evt) override;
private:
	Ui::admin_login *ui;
	void Enter_AdminPanel();
};

#endif // ADMIN_LOGIN_H
