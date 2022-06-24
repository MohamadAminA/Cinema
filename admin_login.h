#ifndef ADMIN_LOGIN_H
#define ADMIN_LOGIN_H
#include "QString"
#include <QMainWindow>
#include <QMessageBox>
#include "Admin_Menu.h"
#include "mainwindow.h"
#include "Models.h"
#include "dbutil.h"
namespace Ui {
class admin_login;
}

class admin_login : public QMainWindow
{
	Q_OBJECT

public:
	explicit admin_login(QWidget *parent = 0, dbutil *db = nullptr);
	~admin_login();
	admin Entered_Admin;

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
	dbutil* DB;
};

#endif // ADMIN_LOGIN_H
