#include "formmapindividuals.h"
#include "phonebook.h"

FormMapIndividuals::FormMapIndividuals(QSqlDatabase database,QWidget *parent) :
    QWidget(parent)
{
    resize(1250, 300);
    setWindowTitle("Физические лица");
    ptvSQL = new QTableView();
    ptvSQL->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ptvSQL->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ptvSQL->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    modeldatabase= new QSqlTableModel(this,database);
    modeldatabase->setTable("Records");

    ptvSQL->setModel(modeldatabase);

    auto* phbxlTop = new QVBoxLayout();
    phbxlTop->addWidget(ptvSQL);

    auto *ppbforward = new QPushButton (tr("Вперед"));
    auto *ppbback = new QPushButton (tr("Назад"));

    auto* pvhbxlTop = new QHBoxLayout();
    pvhbxlTop->addStretch();
    pvhbxlTop->addWidget(ppbback);
    pvhbxlTop->addWidget(ppbforward);
    pvhbxlTop->addStretch();

    phbxlTop->addLayout(pvhbxlTop);

    setLayout(phbxlTop);

    QSqlQuery *query=new QSqlQuery(database);

    query->prepare("SELECT DISTINCT Статус  FROM Records");
    query->exec();

    query->first();
    query->next();
    modeldatabase->setFilter("Статус = '"+query->value(0).toString()+"'");
    modeldatabase->select();

    connect(ppbforward,&QPushButton::clicked, [=](){ this->Forward(query); });
    connect(ppbback,&QPushButton::clicked, [=](){ this->Back(query); });
}

FormMapIndividuals::~FormMapIndividuals()
{

}

void FormMapIndividuals::Forward(QSqlQuery *query)
{
    if(query->next()) {
        modeldatabase->select();
        modeldatabase->setFilter("Статус = '"+query->value(0).toString()+"'");
    }
}

void FormMapIndividuals::Back(QSqlQuery *query)
{
    if(query->previous()){
        modeldatabase->select();
        modeldatabase->setFilter("Статус = '"+query->value(0).toString()+"'");
    }
}
