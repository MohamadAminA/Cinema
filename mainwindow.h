#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dbutil.h"
#include "Models.h"
#include <QMessageBox>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
    void on_loginBtn_clicked();

    void on_registerBtn_clicked();

private:
	Ui::MainWindow *ui;
    dbutil *db;
};

#endif // MAINWINDOW_H
