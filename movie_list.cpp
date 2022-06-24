#include "movie_list.h"
#include "ui_movie_list.h"
#include "QDir"
movie_list::Movie movies[50];

movie_list::movie_list(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::movie_list)
{

	ui->setupUi(this);

	QWidget::showMaximized();

	this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	QSize* size = new QSize(100,100);
	ui->toolBar->setIconSize(*size);

	ui->tableWidget_film->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->tableWidget_film->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	//MovieName*Tickets*Booked Tickets*Time*Genre*Release Date*Director*Movie Cast*IMDB| فیلم بعدی

	movie_list::Refresh_TableWidget_Film();

}

movie_list::~movie_list()
{
	delete ui;
}

void movie_list::resizeEvent(QResizeEvent* evt)
{
	QPixmap bkgnd(":/Resourse/Resourse/Img/backdrop-wooden-table.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	QPalette palette;

    palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);
}

void movie_list::Refresh_TableWidget_Film()
{
	QFile file ("./Movie.txt");
	if (file.open(QFile::ReadOnly|QFile::Text))
	{
		QTextStream stream(&file);
		QString Admin_txt = stream.readAll();
		QStringList Admin_sec_txt = Admin_txt.split('|');
		QStringList Admin_3th_txt;
		QString Admin_single_user;
		ui->tableWidget_film->setRowCount(Admin_sec_txt.count()-1);
		for (int i = 0; i < Admin_sec_txt.count()-1; i++) {
			Admin_single_user = Admin_sec_txt[i];
			Admin_3th_txt = Admin_single_user.split('*');

			movies[i].Name = Admin_3th_txt[0];
			movies[i].Tickets = Admin_3th_txt[1];
			movies[i].BookedTickets = Admin_3th_txt[2];
			movies[i].Time = Admin_3th_txt[3];
			movies[i].Genre = Admin_3th_txt[4];
			movies[i].Release_date = Admin_3th_txt[5];
			movies[i].Director = Admin_3th_txt[6];
			movies[i].Movie_Cast = Admin_3th_txt[7];
			movies[i].IMDB = Admin_3th_txt[8];

			QTableWidgetItem* tmp = new QTableWidgetItem(movies[i].Name);
			ui->tableWidget_film->setItem(i,0,tmp);
			QTableWidgetItem* tmp1 = new QTableWidgetItem(movies[i].Tickets);
			ui->tableWidget_film->setItem(i,1,tmp1);
			QTableWidgetItem* tmp2 = new QTableWidgetItem(movies[i].BookedTickets);
			ui->tableWidget_film->setItem(i,2,tmp2);
			QTableWidgetItem* tmp3 = new QTableWidgetItem(movies[i].Time);
			ui->tableWidget_film->setItem(i,3,tmp3);
			QTableWidgetItem* tmp4 = new QTableWidgetItem(movies[i].Genre);
			ui->tableWidget_film->setItem(i,4,tmp4);
			QTableWidgetItem* tmp5 = new QTableWidgetItem(movies[i].Release_date);
			ui->tableWidget_film->setItem(i,5,tmp5);
			QTableWidgetItem* tmp6 = new QTableWidgetItem(movies[i].Director);
			ui->tableWidget_film->setItem(i,6,tmp6);
			QTableWidgetItem* tmp7 = new QTableWidgetItem(movies[i].Movie_Cast);
			ui->tableWidget_film->setItem(i,7,tmp7);
			QTableWidgetItem* tmp8 = new QTableWidgetItem(movies[i].IMDB);
			ui->tableWidget_film->setItem(i,8,tmp8);
			cell_check = true;
		}
		file.close();
	}
	else{
		if(QMessageBox::warning(this , "Warning","No Movie Found !","Ok","Back","",2,1) == 2){
			movie_list::on_actionBack_triggered();
		}
	}
}

void movie_list::on_actionExit_triggered()
{
	QApplication::quit();
}

void movie_list::on_actionBack_triggered()
{

	this->destroy();
	((QWidget*)parent())->show();

}

void movie_list::on_tableWidget_film_cellChanged(int row, int column)
{

	if(!cell_check)
		return;
	switch (column) {//MovieName*Tickets*Booked Tickets*Time*Genre*Release Date*Director*Movie Cast*IMDB| فیلم بعدی
	case 0:
		movies[row].Name = ui->tableWidget_film->item(row,column)->text();
		break;
	case 1:
		movies[row].Tickets = ui->tableWidget_film->item(row,column)->text() ;
		break;

	case 4:
		movies[row].Genre = ui->tableWidget_film->item(row,column)->text();
		break;

	case 5:
		movies[row].Release_date = ui->tableWidget_film->item(row,column)->text();
		break;

	case 6:
		movies[row].Director = ui->tableWidget_film->item(row,column)->text();
		break;

	case 7:
		movies[row].Movie_Cast = ui->tableWidget_film->item(row,column)->text();
		break;

	case 3:
		movies[row].Time = ui->tableWidget_film->item(row,column)->text();
		break;

	case 2:
		movies[row].BookedTickets = ui->tableWidget_film->item(row,column)->text();
		break;
	case 8:
		movies[row].IMDB = ui->tableWidget_film->item(row,column)->text();
		break;

	default:
		break;
	}
	movie_list::on_actionSave_triggered();
}

void movie_list::on_actionSave_triggered()
{
	QFile file("./Movie.txt");
	if (file.open(QFile::WriteOnly|QFile::Text))
	{
		QTextStream stream(&file);
		for (int i = 0; movies[i].Name != ""; ++i) {
			stream << movies[i].Name << "*"
				   <<movies[i].Tickets  << "*"
				  <<movies[i].BookedTickets  << "*"
				 <<movies[i].Time<< "*"
				<< movies[i].Genre <<"*"
				<< movies[i].Release_date <<"*"
				<< movies[i].Director <<"*"
				<< movies[i].Movie_Cast  <<"*"
				<< movies[i].IMDB  << "|"; // this writes All informations About film in "Movie.txt" File
		}
		file.flush();
		file.close();
	}
	else{
		QMessageBox::warning(this , "Warning","File Movie didn't Open !");
		return ;
	}
}

void movie_list::on_actionRemove_triggered()
{
	if(ui->tableWidget_film->rowCount()==0)
		return;
	int row = ui->tableWidget_film->currentRow();
	if(QMessageBox::warning(this,"Warning","Are you sure you want to delete : "+ movies[row].Name +" ?","Cancle","Delete","",0,0)==1){
		for (int i = row; i < 49 - row; ++i) {
			movies[i] = movies[i+1];
		}
		movie_list::on_actionSave_triggered();

		movie_list::Refresh_TableWidget_Film();
	}
}

void movie_list::on_actionRefresh_triggered()
{
	movie_list::Refresh_TableWidget_Film();
	QMessageBox::information(this , "Information","Table Refreshed");
}
