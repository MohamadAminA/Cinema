#include "add_movie.h"
#include "ui_add_movie.h"
#include "fstream"
#include "iomanip"
#include "iostream"
#include "QFile"
#include "QTextStream"
using namespace std;
add_movie::add_movie(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::add_movie)
{
	ui->setupUi(this);

	QWidget::showMaximized();
	this->setWindowFlags(Qt::SubWindow);
	QSize* size = new QSize(100,100);
	ui->toolBar->setIconSize(*size);
	QPixmap pix(":/Resourse/Resourse/Icon/icons8-add-file-100.png");
	ui->label_AddPic->setPixmap(pix.scaled(110,110,Qt::KeepAspectRatio));
}

add_movie::~add_movie()
{
	delete ui;
}
//MovieName*Tickets*Booked Tickets*Time*Genre*Release Date*Director*Movie Cast*IMDB| فیلم بعدی
void add_movie::on_pushButton_clicked()
{
	if(ui->lineEdit_Director->text().isEmpty()||ui->lineEdit_Genre->text().isEmpty()||ui->lineEdit_Movie_Cast->text().isEmpty()||ui->lineEdit_movie_name->text().isEmpty())
	{
		QMessageBox::warning(this , "Warning","Please Fill All Boxes !");
		return;
	}

	Movie Film;
	Film.Name = ui->lineEdit_movie_name->text();
	Film.Tickets = ui->spinBox_Tickets->text() ;
	Film.Genre = ui->lineEdit_Genre->text();
	Film.Release_date = ui->spinBox_ReleaseDate->text();
	Film.Director = ui->lineEdit_Director->text();
	Film.Movie_Cast = ui->lineEdit_Movie_Cast->text();
	Film.IMDB = ui->doubleSpinBox_IMDB->text();
	Film.Time = ui->timeEdit->text();
	Film.BookedTickets = "0";
	QFile file("./Movie.txt");
	if (file.open(QFile::Append|QFile::Text))
	{
		QTextStream stream(&file);
		stream << Film.Name << "*"
			   <<Film.Tickets  << "*"
			   <<Film.BookedTickets  << "*"
			   <<Film.Time<< "*"
			   << Film.Genre <<"*"
			   << Film.Release_date <<"*"
			   << Film.Director <<"*"
			   << Film.Movie_Cast  <<"*"
			   << Film.IMDB  << "|"; // this writes All informations About film in "Movie.txt" File
		file.close();

		ui->doubleSpinBox_IMDB->setValue(0.0);
		ui->spinBox_ReleaseDate->setValue(2022);
		ui->spinBox_Tickets->setValue(0);
		QTime* Time_tmp = new QTime(00,00,00);
		ui->timeEdit->setTime(*Time_tmp);
		ui->lineEdit_Director->setText("");
		ui->lineEdit_Genre->setText("");
		ui->lineEdit_Movie_Cast->setText("");
		ui->lineEdit_movie_name->setText("");

		QMessageBox::information(this , "Add Movie","Movie successfully Added !");
	}
	else{
		QMessageBox::warning(this , "Warning","File Movie didn't Open !");
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
	Admin* Admin_Form = new Admin();
	Admin_Form->show();
	this->close();
}

void add_movie::on_actionExit_triggered()
{
	QApplication::quit();
}

void add_movie::on_actionAddMovie_triggered()
{
	add_movie::on_pushButton_clicked();
}
