#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "register.h"
#include "admin_login.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
    db = new dbutil();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_loginBtn_clicked()
{
    QString user = ui->username->text();
    QString pass = ui->password->text();
    if (user.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "login", "fields can not be empty.");
        return;`
    }
    User userobj{user, pass};
    bool res = db->ValidateUser(userobj);
    if (res) {
        QMessageBox::information(this, "login", "successfull loginned");
    } else {
        QMessageBox::information(this, "login", "login failed");
    }
}


void MainWindow::on_registerBtn_clicked()
{
    Register *reg = new Register(this, db);
    this->hide();
    reg->show();
}


void MainWindow::on_adminBtn_clicked()
{
    admin_login *admin = new admin_login(this);
    this->hide();
    admin->show();
}

