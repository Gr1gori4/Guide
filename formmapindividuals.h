#ifndef FORMMAPINDIVIDUALS_H
#define FORMMAPINDIVIDUALS_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlQuery>
#include <QTableView>


class FormMapIndividuals : public QWidget
{
    Q_OBJECT

public:
    explicit FormMapIndividuals(QSqlDatabase,QWidget *parent = nullptr);
    ~FormMapIndividuals();

private:
    QTableView *ptvSQL;
    QSqlTableModel *modeldatabase;

private slots:
    void Forward(QSqlQuery *);
    void Back(QSqlQuery *);
};

#endif // FORMMAPINDIVIDUALS_H
