#include "ui_admin_login.h"
#include "admin_login.h"
#include "Qt"
//admin_login::Admin_User Accounts[20];

admin_login::admin_login(QWidget *parent, dbutil *db) :
	QMainWindow(parent),
	ui(new Ui::admin_login)
{

	ui->setupUi(this);
	this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	DB = db;
	QWidget::showMaximized();
	QSize* size = new QSize(100,100);
	ui->toolBar->setIconSize(*size);


	//Defult Admin Username : admin | Password : 123456

}

admin_login::~admin_login()
{
	delete ui;
}

void admin_login::on_pushButton_Login_clicked()
{
	if(ui->lineEdit_username->text().isEmpty() || ui->lineEdit_password->text().isEmpty()) {
		QMessageBox::warning(this , "Warning","Username and password should be filled both");
		return ;
	}


	Entered_Admin.username = ui->lineEdit_username->text();
	Entered_Admin.password = ui->lineEdit_password->text();
	if(!DB->ValidateAdmin(Entered_Admin)){
		QMessageBox::warning(this , "Warning","Incorrect username or password");
		return;
	}
	else{
		Enter_AdminPanel();
	}
}

void admin_login::Enter_AdminPanel()
{
	Admin* Admin_Form = new Admin(this);
	Admin_Form->show();
	this->hide();
}

//تنظیم بکگراند به صورت تغییر پذیر
void admin_login::resizeEvent(QResizeEvent* evt)
{
	QPixmap bkgnd(":/Resourse/Resourse/Img/Background_salon.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	QPalette palette;

	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);

}




void admin_login::on_actionExit_triggered()
{

	this->close();
	QApplication::quit();
}

void admin_login::on_actionReload_triggered()
{
	ui->lineEdit_password->setText("");
	ui->lineEdit_username->setText("");
	ui->checkBox_2->setChecked(false);
}

void admin_login::on_checkBox_2_stateChanged()
{
	if(ui->checkBox_2->isChecked())
		ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
	else
		ui->lineEdit_password->setEchoMode(QLineEdit::Password);
}

void admin_login::on_actionBack_triggered()
{

	this->destroy();
	((QWidget*)parent())->show();

}
