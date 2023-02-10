#ifndef FORMMAPINDIVIDUALS_H
#define FORMMAPINDIVIDUALS_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlQuery>
#include <QTableView>

namespace Ui {
class FormMapIndividuals;
}

class FormMapIndividuals : public QWidget
{
    Q_OBJECT

public:
    explicit FormMapIndividuals(QSqlDatabase,QWidget *parent = nullptr);
    ~FormMapIndividuals();

private:
    QTableView *ptable;
    QSqlTableModel *modeldb;

};

#endif // FORMMAPINDIVIDUALS_H
