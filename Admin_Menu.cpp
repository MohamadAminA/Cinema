#include "Admin_Menu.h"
#include "ui_admin.h"

Admin::Admin(QWidget *parent, dbutil *db) :
	QMainWindow(parent),
	ui(new Ui::Admin)
{
	ui->setupUi(this);

	ui->pushButton_Users->hide();
	this->db = db;
	this->QWidget::showMaximized();
	this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	QSize* size = new QSize(100,100);
	ui->toolBar->setIconSize(*size);
	QPixmap pix(":/Resourse/Resourse/Icon/icons8-add-file-100.png");
	ui->label_AddmoviePic->setPixmap(pix.scaled(200,200,Qt::KeepAspectRatio));
	QPixmap pix2(":/Resourse/Resourse/Icon/icons8-create-100.png");
	ui->label_MoviListPic->setPixmap(pix2.scaled(200,200,Qt::KeepAspectRatio));

}

Admin::~Admin()
{
	delete ui;
}

void Admin::on_actionBack_triggered()
{

	this->destroy();
	((QWidget*)parent())->show();
}

//تنظیم بکگراند به صورت تغییر پذیر
void Admin::resizeEvent(QResizeEvent* evt)
{
	QPixmap bkgnd(":/Resourse/Resourse/Img/Background_film.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	QPalette palette;

    palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);

}

void Admin::on_actionExit_triggered()
{
	QApplication::quit();
}

void Admin::on_pushButton_Addmovie_clicked()
{
	add_movie* add_Movie = new add_movie(this,db);
	add_Movie->show();
	this->hide();
}

void Admin::on_pushButton_MovieList_clicked()
{
	movie_list* Movie_List = new movie_list(this,db);
	Movie_List->show();
	this->hide();
}

void Admin::on_actionMovieList_triggered()
{
	Admin::on_pushButton_MovieList_clicked();
}

void Admin::on_actionAddMovie_triggered()
{
	Admin::on_pushButton_Addmovie_clicked();
}
