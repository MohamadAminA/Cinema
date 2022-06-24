#include "ui_admin_login.h"
#include "admin_login.h"

admin_login::Admin_User Accounts[20];

admin_login::admin_login(QWidget *parent) :
    QDialog(parent),
	ui(new Ui::admin_login)
{

	ui->setupUi(this);
//	this->setWindowFlags(Qt::SubWindow);

//	QWidget::showMaximized();
//	QSize* size = new QSize(100,100);
//	ui->toolBar->setIconSize(*size);

//	QFile file("./Admin Users.txt");
//	if (file.open(QFile::ReadOnly|QFile::Text))
//	{
//		QTextStream stream(&file);
//		QString Admin_txt = stream.readAll();
//		QStringList Admin_sec_txt = Admin_txt.split('|');
//		QStringList Admin_3th_txt;
//		QString Admin_single_user;
//		for (int i = 0; i < Admin_sec_txt.count()-1; i++) {
//			Admin_single_user = Admin_sec_txt[i];
//			Admin_3th_txt = Admin_single_user.split(':');
//			Accounts[i].UserName = Admin_3th_txt[0];
//			Accounts[i].Password = Admin_3th_txt[1];
//			Accounts[i].Name = Admin_3th_txt[2];
//		}


//		file.close();
//	}
//	else{
//		QFile file("./Admin Users.txt");
//		if (file.open(QFile::WriteOnly|QFile::Text))
//		{
//			QTextStream stream(&file);
//			stream << "Admin" << ":" << "123456" << ":" << "Defult"<< "|"; // this writes first line with two columns
//			file.close();
//		}
//	}
	//Defult Admin Username : Admin | Password : 123456

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
	admin_login::Admin_User * Admin;
	bool isFind = false;
	for (int i = 0; !(Accounts[i].UserName.isEmpty()); ++i) {
		Admin = &(Accounts[i]);
		if(Admin->Password == ui->lineEdit_password->text() &&Admin->UserName == ui->lineEdit_username->text()){
			Enter_AdminPanel();
			isFind = true;
		}
	}
	if(!isFind){
		QMessageBox::warning(this , "Warning","Incorrect username or password");
		return;
	}

}

void admin_login::Enter_AdminPanel()
{
	Admin* Admin_Form = new Admin();
	Admin_Form->show();
	this->close();
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
	MainWindow* mainwindow_Form = new MainWindow();
	mainwindow_Form->show();
	this->close();
}
