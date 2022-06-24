#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QMessageBox>
#include "dbutil.h"
#include "Models.h"

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr, dbutil *db = nullptr);
    ~Register();

private slots:
    void on_signupBtn_clicked();

    void on_Register_rejected();

private:
    Ui::Register *ui;
    dbutil *db;
};

#endif // REGISTER_H
