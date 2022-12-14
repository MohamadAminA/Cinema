#include "add_movie.h"
#include "ui_add_movie.h"
#include "fstream"
#include "iomanip"
#include "iostream"
#include "QFile"
#include "QTextStream"
#include "Models.h"
using namespace std;
add_movie::add_movie(QWidget *parent, dbutil *db) :
	QMainWindow(parent),
	ui(new Ui::add_movie)
{
	ui->setupUi(this);
	this->db = db;
	QWidget::showMaximized();
	this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	QSize* size = new QSize(100,100);
	ui->toolBar->setIconSize(*size);
	QPixmap pix(":/Resourse/Resourse/Icon/icons8-add-file-100.png");
	ui->label_AddPic->setPixmap(pix.scaled(110,110,Qt::KeepAspectRatio));
}

add_movie::~add_movie()
{
	delete ui;
}

void add_movie::on_pushButton_clicked()
{
	if(ui->lineEdit_Director->text().isEmpty()||ui->lineEdit_Genre->text().isEmpty()||ui->lineEdit_Movie_Cast->text().isEmpty()||ui->lineEdit_movie_name->text().isEmpty())
	{
		QMessageBox::warning(this , "Warning","Please Fill All Boxes !");
		return;
	}
	Movie* Film = new Movie(ui->lineEdit_movie_name->text(),ui->spinBox_Tickets->text().toInt(),0,ui->timeEdit->text(),ui->lineEdit_Genre->text(),ui->spinBox_ReleaseDate->text(),ui->lineEdit_Director->text(),ui->lineEdit_Movie_Cast->text(),ui->doubleSpinBox_IMDB->text().toDouble());

	if(db->AddMovie(*Film)){
		add_movie::on_actionReset_triggered();
		QMessageBox::information(this , "Add Movie","Movie successfully Added !");
	}
	else{
		QMessageBox::warning(this , "Warning","couldn't add movie !");
		return ;
	}
}

void add_movie::resizeEvent(QResizeEvent* evt)
{
	QPixmap bkgnd(":/Resourse/Resourse/Img/Background Light Movie.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	QPalette palette;

    palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);
}

void add_movie::on_actionReset_triggered()
{
	ui->doubleSpinBox_IMDB->setValue(0.0);
	ui->spinBox_ReleaseDate->setValue(2022);
	ui->spinBox_Tickets->setValue(0);
	QTime* Time_tmp = new QTime(00,00,00);
	ui->timeEdit->setTime(*Time_tmp);
	ui->lineEdit_Director->setText("");
	ui->lineEdit_Genre->setText("");
	ui->lineEdit_Movie_Cast->setText("");
	ui->lineEdit_movie_name->setText("");
}

void add_movie::on_actionBack_triggered()
{

	this->destroy();
	((QWidget*)parent())->show();

}

void add_movie::on_actionExit_triggered()
{
	QApplication::quit();
}

void add_movie::on_actionAddMovie_triggered()
{
	add_movie::on_pushButton_clicked();
}
