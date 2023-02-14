#include "phonebook.h"

PhoneBook::PhoneBook(QWidget *parent)
    : QWidget(parent)
{
    CreateMenu();

    auto * pvbxlMain = new QVBoxLayout();
    pvbxlMain->setContentsMargins(10, 10, 10, 10);
    pvbxlMain->setSpacing(10);

    auto  *pgbTop = new QGroupBox();
    auto  *pgbMedium = new QGroupBox();
    pgbLower = new QGroupBox();

    pvbxlMain->addWidget(pgbTop);
    pvbxlMain->addWidget(pgbMedium);
    pvbxlMain->addWidget(pgbLower);

    setLayout(pvbxlMain);

    //====================================================//
    //Компановка pgbTop

    plState = new QLabel(tr("Справочник готов к работе"));
    plDirIndividual = new QLabel(tr("Справочник физических лиц"));
    plDirEntitie = new QLabel(tr("Справочник юридических лиц"));

    auto * phbxlTop = new QHBoxLayout();
    phbxlTop->addStretch();
    phbxlTop->addWidget(plState);
    phbxlTop->addWidget(plDirIndividual);
    phbxlTop->addWidget(plDirEntitie);
    phbxlTop->addStretch();

    plDirIndividual->hide();
    plDirEntitie->hide();

    pgbTop->setLayout(phbxlTop);
    //====================================================//


    //====================================================//
    //Компановка pgbMedium
    auto   *phbxMedium = new QHBoxLayout();

    ptvSQL = new QTableView();
    ptwXML= new QTableWidget();

    ppbIndividuals = new QPushButton (tr("Физические лица"));
    ppbLegalEntities = new QPushButton (tr("Юридические лица"));

    phbxMedium->addWidget(ptvSQL);
    phbxMedium->addWidget(ptwXML);
    phbxMedium->addWidget(ppbIndividuals);
    phbxMedium->addWidget(ppbLegalEntities);

    pgbMedium->setLayout(phbxMedium);

    ptvSQL->hide();
    ptwXML->hide();
    //====================================================//


    //====================================================//
    //Компановка pgbLower
    auto *phbxlLower = new QHBoxLayout();

    auto *pgbSearch = new QGroupBox();

    auto *ppbAddrecord = new QPushButton (tr("Добавить запись"));
    auto *ppbEditrecord = new QPushButton (tr("Редактировать запись"));
    auto *ppbDeleterecord = new QPushButton (tr("Удалить запись"));

    auto *pvbxlEditing = new QVBoxLayout();

    pvbxlEditing->addWidget(ppbAddrecord);
    pvbxlEditing->addWidget(ppbEditrecord);
    pvbxlEditing->addWidget(ppbDeleterecord);

    phbxlLower->addLayout(pvbxlEditing);

    auto *phbxSearch = new QHBoxLayout();

    auto *pvbxlSearchRadioButton = new QVBoxLayout();
    auto *pvbxlSearchInput = new QVBoxLayout();

    prbname = new QRadioButton (tr("По имени"));
    prbsurname = new QRadioButton (tr("По фамилии"));
    prbnumber = new QRadioButton (tr("По номеру телефона"));
    prbtitle = new QRadioButton (tr("По названию"));
    prbFIO = new QRadioButton (tr("По ФИО директора"));
    prbOGRN = new QRadioButton (tr("По ОГРН"));
    prbbranch = new QRadioButton (tr("По отрасли"));

    pvbxlSearchRadioButton->addWidget(prbname);
    pvbxlSearchRadioButton->addWidget(prbsurname);
    pvbxlSearchRadioButton->addWidget(prbnumber);
    pvbxlSearchRadioButton->addWidget(prbtitle);
    pvbxlSearchRadioButton->addWidget(prbFIO);
    pvbxlSearchRadioButton->addWidget(prbOGRN);
    pvbxlSearchRadioButton->addWidget(prbbranch);

    auto  *plinput= new QLabel(tr("Введите критерий поиска"));
    pleSearch = new QLineEdit();
    auto  *ppbsearch = new QPushButton (tr("Искать"));
    auto  *ppbbshow = new QPushButton (tr("Показать все записи"));
    auto  *ppbmap = new QPushButton (tr("Показать записи картой"));

    auto   *phbxSearchInput = new QHBoxLayout();

    phbxSearchInput->addWidget(ppbsearch);
    phbxSearchInput->addWidget(ppbbshow);
    phbxSearchInput->addWidget(ppbmap);

    pvbxlSearchInput->addWidget(plinput);
    pvbxlSearchInput->addWidget(pleSearch);
    pvbxlSearchInput->addLayout(phbxSearchInput);

    phbxSearch->addLayout(pvbxlSearchRadioButton);
    phbxSearch->addLayout(pvbxlSearchInput);

    pgbSearch->setLayout(phbxSearch);
    phbxlLower->addWidget(pgbSearch);

    auto *ppbbexit = new QPushButton (tr("Выход"));
    auto *ppbbgomain = new QPushButton (tr("На главную"));

    auto *pvbxlbuttons = new QVBoxLayout();

    pvbxlbuttons->addWidget(ppbbgomain);
    pvbxlbuttons->addWidget(ppbbexit);
    phbxlLower->addLayout(pvbxlbuttons);

    pgbLower->setLayout(phbxlLower);

    pgbLower->hide();
    //====================================================//


    //====================================================//

    connect(ppbAddrecord,SIGNAL(clicked()),SLOT(AddRecord()));
    connect(ppbEditrecord,SIGNAL(clicked()),SLOT(EditRecord()));
    connect(ppbDeleterecord,SIGNAL(clicked()),SLOT(DeleteRecord()));
    connect(prbname,SIGNAL(clicked()),SLOT(SortName()));
    connect(prbsurname,SIGNAL(clicked()),SLOT(SortSurname()));
    connect(prbnumber,SIGNAL(clicked()),SLOT(SortNumber()));
    connect(ppbsearch,SIGNAL(clicked()),SLOT(Search()));
    connect(ppbbshow,SIGNAL(clicked()),SLOT(Show()));
    connect(ppbmap,SIGNAL(clicked()),SLOT(Map()));
    connect(ppbbexit,SIGNAL(clicked()),SLOT(Exit()));
    connect(ppbbgomain,SIGNAL(clicked()),SLOT(GoMain()));
    connect(ppbIndividuals,SIGNAL(clicked()),SLOT(OpenIndividuals()));
    connect(ppbLegalEntities,SIGNAL(clicked()),SLOT(OpenLegalEntities()));
    //====================================================//


    //====================================================//
    // Настройка таблицы ptvSQL
    ptvSQL->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ptvSQL->setItemDelegate(new QSqlRelationalDelegate(this));
    ptvSQL->setSelectionBehavior(QAbstractItemView::SelectRows);
    ptvSQL->resizeColumnsToContents();
    //====================================================//


    //====================================================//
    // Настройка таблицы ptwXML
    ptwXML->setColumnCount(9);
    QStringList columns = { "Название", "ФИО директора", "Телефон директора", "Контактное лицо","Телефон контанктного лица","ОГРН","Адрес","Отрасль","Описание" };
    ptwXML->setHorizontalHeaderLabels(columns);
    ptwXML->setEditTriggers(QAbstractItemView::NoEditTriggers); // Запрет редактирование ячеек
    for(int i=0;i<ptwXML->columnCount();i++)
        ptwXML->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch); //Выравнивание по всей ширине виджета
    //====================================================//


    //====================================================//
    // Подключение базы данных
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/d.andronychev/study/Qt/PhoneBookV2/db/PhoneRecordIndividuals.db");
    if(!db.open())
    {
        Close_msg("Ошибка при открытии базы данных");
        qDebug() << db.lastError().text();
    }
    modeldb= new QSqlTableModel(this,db);
    modeldb->setTable("Records");
    ptvSQL->setModel(modeldb);
    modeldb->select();
    //====================================================//


    //====================================================//
    // Подключение файла XML и запись его в QMap
    QDomDocument domDoc;
    QFile file("C:/Users/d.andronychev/study/Qt/Guide/Entities.xml") ;
    if(file.open(QIODevice::ReadOnly)) {
        if(domDoc.setContent(&file)) {
            QDomElement domElement= domDoc.documentElement();
            TraverseNode(domElement);
        }
        file. close ();
    }
}

PhoneBook::~PhoneBook()
{

}

void PhoneBook::CreateMenu(/*QWidget *parent*/)
{
    auto *menuBar= new QMenuBar(this);
    auto * pmDirIndividual = menuBar->addMenu(tr("Справочник физических лиц"));
    auto * paSearchRecord = new QMenu(tr("Поиск"));
    auto * paDisplayRecord = new QMenu(tr("Отобразить все записи"));
    auto * pmDirEntitie= menuBar->addMenu(tr("Справочник юридических лиц"));
    auto * paSearchRecordEntitie = new QMenu(tr("Поиск"));
    auto * paDisplayRecordEntitie = new QMenu(tr("Отобразить все записи"));
    auto * paExit = menuBar->addAction(tr("Выход"));

    menuBar->show();
    connect(paExit,SIGNAL(triggered()),SLOT(Exit()));

    //====================================================//
    // Подменю справочника физических лиц

    auto *paAddRecord = new QAction(tr("Добавить запись"), this);
    auto *paEditRecord = new QAction(tr("Редактировать запись"), this);
    auto *paDeleteRecord = new QAction(tr("Удалить запись"), this);
    auto *paSearchRecordName = new QAction(tr("По имени"), this);
    auto *paSearchRecordSurname = new QAction(tr("По фамилии"), this);
    auto *paSearchRecordNumber = new QAction(tr("По номеру"), this);
    auto *paDisplayRecordList = new QAction(tr("Списком"), this);
    auto *paSearcheRecordMap = new QAction(tr("Картой"), this);

    paSearchRecord->addAction(paSearchRecordName);
    paSearchRecord->addAction(paSearchRecordSurname);
    paSearchRecord->addAction(paSearchRecordNumber);

    paDisplayRecord->addAction(paDisplayRecordList);
    paDisplayRecord->addAction(paSearcheRecordMap);

    pmDirIndividual->addAction(paAddRecord);
    pmDirIndividual->addAction(paEditRecord);
    pmDirIndividual->addAction(paDeleteRecord);
    pmDirIndividual->addMenu(paSearchRecord);
    pmDirIndividual->addMenu(paDisplayRecord);

    connect(paAddRecord,SIGNAL(triggered()),SLOT(AddRecordIndividuals()));
    connect(paEditRecord,SIGNAL(triggered()),SLOT(EditRecordIndividuals()));
    connect(paDeleteRecord,SIGNAL(triggered()),SLOT(DeleteRecordIndividuals()));
    connect(paSearchRecordName,SIGNAL(triggered()),SLOT(SearchRecordNameIndividuals()));
    connect(paSearchRecordSurname,SIGNAL(triggered()),SLOT(SearchRecordSurnameIndividuals()));
    connect(paSearchRecordNumber,SIGNAL(triggered()),SLOT(SearchRecordNumberIndividuals()));
    connect(paDisplayRecordList,SIGNAL(triggered()),SLOT(DisplayRecordListIndividuals()));
    connect(paSearcheRecordMap,SIGNAL(triggered()),SLOT(SearcheRecordMapIndividuals()));

    //====================================================//


    //====================================================//
    // Подменю справочника юридических лиц

    auto *paAddRecordEntitie = new QAction(tr("Добавить запись"), this);
    auto *paEditRecordEntitie = new QAction(tr("Редактировать запись"), this);
    auto *paDeleteRecordEntitie = new QAction(tr("Удалить запись"), this);
    auto *paSearchRecordTitle = new QAction(tr("По названию"), this);
    auto *paSearchRecordDirector = new QAction(tr("По ФИО директора"), this);
    auto *paSearchRecordOGRN = new QAction(tr("По ОГРН"), this);
    auto *paSearchRecordBranch = new QAction(tr("По названию отрасли"), this);
    auto *paDisplayRecordListEntitie = new QAction(tr("Списком"), this);
    auto *paSearcheRecordMapEntitie = new QAction(tr("Картой"), this);

    paSearchRecordEntitie->addAction(paSearchRecordTitle);
    paSearchRecordEntitie->addAction(paSearchRecordDirector);
    paSearchRecordEntitie->addAction(paSearchRecordOGRN);
    paSearchRecordEntitie->addAction(paSearchRecordBranch);

    paDisplayRecordEntitie->addAction(paDisplayRecordListEntitie);
    paDisplayRecordEntitie->addAction(paSearcheRecordMapEntitie);

    pmDirEntitie->addAction(paAddRecordEntitie);
    pmDirEntitie->addAction(paEditRecordEntitie);
    pmDirEntitie->addAction(paDeleteRecordEntitie);
    pmDirEntitie->addMenu(paSearchRecordEntitie);
    pmDirEntitie->addMenu(paDisplayRecordEntitie);

    connect(paAddRecordEntitie,SIGNAL(triggered()),SLOT(AddRecordEntitie()));
    connect(paEditRecordEntitie,SIGNAL(triggered()),SLOT(EditRecordEntitie()));
    connect(paDeleteRecordEntitie,SIGNAL(triggered()),SLOT(DeleteRecordEntitie()));
    connect(paSearchRecordTitle,SIGNAL(triggered()),SLOT(SearchRecordTitle()));
    connect(paSearchRecordDirector,SIGNAL(triggered()),SLOT(SearchRecordDirector()));
    connect(paSearchRecordOGRN,SIGNAL(triggered()),SLOT(SearchRecordOGRN()));
    connect(paSearchRecordBranch,SIGNAL(triggered()),SLOT(SearchRecordBranch()));
    connect(paDisplayRecordListEntitie,SIGNAL(triggered()),SLOT(DisplayRecordListEntitie()));
    connect(paSearcheRecordMapEntitie,SIGNAL(triggered()),SLOT(SearcheRecordMapEntitie()));
}

void PhoneBook::Close_msg(QString str)
{
    QMessageBox msg;
    msg.setText(str);
    msg.exec();
}


void PhoneBook::TraverseNode(const QDomNode& node)
{
    QString *OGRN= new QString();
    Company *company= new Company();
    QDomNode domNode = node.firstChild();
    while ( ! domNode. isNull () ) {
        if(domNode.isElement()) {
            QDomElement domElement = domNode.toElement();
            if (!domElement.isNull()) {
                QString str=domElement. tagName ( );
                if( domElement. tagName ( ) == "company" ) {
                       OGRN = new QString();
                       company = new Company();
                }
                else if(domElement.tagName() == "title")
                    company->title=domElement.text();
                else if(domElement.tagName() == "director")
                    company->director=domElement.text();
                else if(domElement.tagName() == "phone_director")
                    company->phone_director=domElement.text();
                else if(domElement.tagName() == "contact_person")
                    company->contact_person=domElement.text();
                else if(domElement.tagName() == "phone_contact_person")
                    company->phone_contact_person=domElement.text();
                else if(domElement.tagName() == "OGRN")
                    *OGRN=domElement.text();
                else if(domElement.tagName() == "adress")
                    company->adress=domElement.text();
                else if(domElement.tagName() == "branch")
                    company->branch=domElement.text();
                else if(domElement.tagName() == "description"){
                    company->description=domElement.text();
                    mapCompany.insert(*OGRN,*company);
                }
            }
        }
        TraverseNode(domNode);
        domNode=domNode.nextSibling();
    }
}

void PhoneBook::Print_Table()
{
    ptwXML->clearContents();
    ptwXML->setRowCount(0);
    QMapIterator<QString, Company> i (mapCompany);
    while (i.hasNext())
    {
        i.next();
        ptwXML->setRowCount(ptwXML->rowCount() + 1);

        //QTableWidgetItem *newItem;

        ptwXML->setItem(ptwXML->rowCount() - 1, 0, new QTableWidgetItem(i.value().title));

        ptwXML->setItem(ptwXML->rowCount() - 1, 1, new QTableWidgetItem(i.value().director));

        ptwXML->setItem(ptwXML->rowCount() - 1, 2, new QTableWidgetItem(i.value().phone_director));

        ptwXML->setItem(ptwXML->rowCount() - 1, 3, new QTableWidgetItem(i.value().contact_person));

        ptwXML->setItem(ptwXML->rowCount() - 1, 4, new QTableWidgetItem(i.value().phone_contact_person));

        ptwXML->setItem(ptwXML->rowCount() - 1, 5, new QTableWidgetItem(i.key()));

        ptwXML->setItem(ptwXML->rowCount() - 1, 6, new QTableWidgetItem(i.value().adress));

        ptwXML->setItem(ptwXML->rowCount() - 1, 7, new QTableWidgetItem(i.value().branch));

        ptwXML->setItem(ptwXML->rowCount() - 1, 8, new QTableWidgetItem(i.value().description));
    }
    for(int i=0;i<ptwXML->columnCount()+1;i++)
        ptwXML->verticalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}

void PhoneBook::AddRecordIndividuals()
{
    QModelIndexList modelIndex= ptvSQL->selectionModel()->selectedRows();
    formAddIndividuals = new FormIndividuals(-1,db,modeldb,modelIndex);
    formAddIndividuals->show();
}

void PhoneBook::EditRecordIndividuals()
{
    QModelIndexList modelIndex= ptvSQL->selectionModel()->selectedRows();
    formAddIndividuals = new FormIndividuals(0,db,modeldb,modelIndex);
    formAddIndividuals->show();
}

void PhoneBook::DeleteRecordIndividuals()
{
    QModelIndexList modelIndex= ptvSQL->selectionModel()->selectedRows();
    formAddIndividuals = new FormIndividuals(1,db,modeldb,modelIndex);
    formAddIndividuals->show();
}

void PhoneBook::SearchRecordNameIndividuals()
{
    OpenIndividuals();
    QModelIndexList modelIndex= ptvSQL->selectionModel()->selectedRows();
    formAddIndividuals = new FormIndividuals(2,db,modeldb,modelIndex);
    formAddIndividuals->show();
}

void PhoneBook::SearchRecordSurnameIndividuals()
{
    OpenIndividuals();
    QModelIndexList modelIndex= ptvSQL->selectionModel()->selectedRows();
    formAddIndividuals = new FormIndividuals(3,db,modeldb,modelIndex);
    formAddIndividuals->show();
}

void PhoneBook::SearchRecordNumberIndividuals()
{
    OpenIndividuals();
    QModelIndexList modelIndex= ptvSQL->selectionModel()->selectedRows();
    formAddIndividuals = new FormIndividuals(4,db,modeldb,modelIndex);
    formAddIndividuals->show();
}

void PhoneBook::DisplayRecordListIndividuals()
{
    OpenIndividuals();
    modeldb->setTable("Records");
    modeldb->select();
}

void PhoneBook::SearcheRecordMapIndividuals()
{
    formMapIndividuals = new FormMapIndividuals(db);
    formMapIndividuals->show();
}

void PhoneBook::AddRecordEntitie()
{
    OpenLegalEntities();
    formEntities = new FormEntities ();
    formEntities->show();
}

void PhoneBook::EditRecordEntitie()
{
    OpenLegalEntities();
    formEntities = new FormEntities ();
    formEntities->show();
}

void PhoneBook::DeleteRecordEntitie()
{
    OpenLegalEntities();
    formEntities = new FormEntities ();
    formEntities->show();
}

void PhoneBook::SearchRecordTitle()
{

    pleSearch->text();
    ptwXML->clearContents();
    ptwXML->setRowCount(0);
    QMapIterator<QString, Company> i (mapCompany);
    while (i.hasNext())
    {
        i.next();
        if(i.value().title==pleSearch->text())
        {
        ptwXML->setRowCount(ptwXML->rowCount() + 1);

        ptwXML->setItem(ptwXML->rowCount() - 1, 0, new QTableWidgetItem(i.value().title));

        ptwXML->setItem(ptwXML->rowCount() - 1, 1, new QTableWidgetItem(i.value().director));

        ptwXML->setItem(ptwXML->rowCount() - 1, 2, new QTableWidgetItem(i.value().phone_director));

        ptwXML->setItem(ptwXML->rowCount() - 1, 3, new QTableWidgetItem(i.value().contact_person));

        ptwXML->setItem(ptwXML->rowCount() - 1, 4, new QTableWidgetItem(i.value().phone_contact_person));

        ptwXML->setItem(ptwXML->rowCount() - 1, 5, new QTableWidgetItem(i.key()));

        ptwXML->setItem(ptwXML->rowCount() - 1, 6, new QTableWidgetItem(i.value().adress));

        ptwXML->setItem(ptwXML->rowCount() - 1, 7, new QTableWidgetItem(i.value().branch));

        ptwXML->setItem(ptwXML->rowCount() - 1, 8, new QTableWidgetItem(i.value().description));
        }
    }
    for(int i=0;i<ptwXML->columnCount()+1;i++)
        ptwXML->verticalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}

void PhoneBook::SearchRecordDirector()
{

}

void PhoneBook::SearchRecordOGRN()
{

}

void PhoneBook::SearchRecordBranch()
{

}

void PhoneBook::DisplayRecordListEntitie()
{

}

void PhoneBook::SearcheRecordMapEntitie()
{

}

void PhoneBook::Exit()
{
    close();
}

void PhoneBook::GoMain()
{
    pgbLower->hide();
    plDirIndividual->hide();
    ptvSQL->hide();
    ptwXML->hide();
    plDirEntitie->hide();

    plState->show();
    ppbIndividuals->show();
    ppbLegalEntities->show();

}

void PhoneBook::AddRecord()
{
    if(plDirIndividual->isVisible())
        AddRecordIndividuals();
    else
        AddRecordEntitie();
}

void PhoneBook::EditRecord()
{
    if(plDirIndividual->isVisible())
        EditRecordIndividuals();
    else
        EditRecordEntitie();
    //QModelIndex idIndex = ptvSQL->model()->selectedIndexes()->first();
    //qDebug() << " value "<< ptvSQL->model()->data(ptvSQL->model()->index(index.row(),0)).toInt();

}

void PhoneBook::DeleteRecord()
{
    if(plDirIndividual->isVisible())
        DeleteRecordIndividuals();
    else
        DeleteRecordEntitie();
}

void PhoneBook::SortName()
{
    modeldb->setSort(1, Qt::AscendingOrder);
    modeldb->select();
}

void PhoneBook::SortSurname()
{
    modeldb->setSort(0, Qt::AscendingOrder);
    modeldb->select();
}

void PhoneBook::SortNumber()
{
    modeldb->setSort(3, Qt::AscendingOrder);
    modeldb->select();
}



void PhoneBook::Search()
{
    if(prbname->isChecked())
        modeldb->setFilter("Имя = '"+pleSearch->text()+"'");
    else if(prbsurname->isChecked())
        modeldb->setFilter("Фамилия = '"+pleSearch->text()+"'");
    else
        modeldb->setFilter("Телефон = '"+pleSearch->text()+"'"); // не работает
    modeldb->select();
}

void PhoneBook::Show()
{
    modeldb->setTable("Records");
    modeldb->select();
}

void PhoneBook::Map()
{
    if(plDirIndividual->isVisible())
        SearcheRecordMapIndividuals();
    else
        AddRecordEntitie();
}

void PhoneBook::OpenIndividuals()
{
    pgbLower->show();
    plDirIndividual->show();
    plState->hide();
    plDirEntitie->hide();
    ppbIndividuals->hide();
    ppbLegalEntities->hide();
    ptvSQL->show();
    ptwXML->hide();
    prbname->show();
    prbsurname->show();
    prbnumber->show();
    prbtitle->hide();
    prbFIO->hide();
    prbOGRN->hide();
    prbbranch->hide();

}

void PhoneBook::OpenLegalEntities()
{
    pgbLower->show();
    ptwXML->show();
    ptvSQL->hide();
    plDirIndividual->hide();
    plState->hide();
    plDirEntitie->show();
    ppbIndividuals->hide();
    ppbLegalEntities->hide();
    prbname->hide();
    prbsurname->hide();
    prbnumber->hide();
    prbtitle->show();
    prbFIO->show();
    prbOGRN->show();
    prbbranch->show();


//    QString OGRN="1221313";
//    Company company;
//    company.title="Название 1";
//    company.director="Директор 1";
//    company.phone_director="Телефон директора 1";
//    company.contact_person="Контактный человек 1";
//    company.phone_contact_person="Телефон контакного 1";
//    company.adress="Адрес 1";
//    company.branch="Отсрасль 1";
//    company.description="Описание 1";

//    QString OGRN1="1221314";
//    Company company1;
//    company1.title="Название 2";
//    company1.director="Директор 2";
//    company1.phone_director="Телефон директора 2";
//    company1.contact_person="Контактный человек 2";
//    company1.phone_contact_person="Телефон контакного 2";
//    company1.adress="Адрес 2";
//    company1.branch="Отсрасль 2";
//    company1.description="Описание 2";

//    QString OGRN3="1221315";
//    Company company3;
//    company3.title="Название 3";
//    company3.director="Директор 3";
//    company3.phone_director="Телефон директора 3";
//    company3.contact_person="Контактный человек 3";
//    company3.phone_contact_person="Телефон контакного 3";
//    company3.adress="Адрес 3";
//    company3.branch="Отсрасль 3";
//    company3.description="Описание 3";

//    mapCompany.insert(OGRN,company);
//    //qDebug()<<mapCompany.size();
//    mapCompany.insert(OGRN1,company1);//нужно создать модель
//    //qDebug()<<mapCompany.size();
//    mapCompany.insert(OGRN3,company3);//нужно создать модель
//    //qDebug()<<mapCompany.size();

//    QMapIterator<QString, Company> j(mapCompany);
//    while (j.hasNext()) {
//     j.next();
//           qDebug()<<j.key();
//           qDebug()<<j.value().title;
//           qDebug()<<j.value().director;
//           qDebug()<<j.value().phone_director;
//           qDebug()<<j.value().contact_person;
//           qDebug()<<j.value().phone_contact_person;
//           qDebug()<<j.value().adress;
//           qDebug()<<j.value().branch;
//           qDebug()<<j.value().description;
//        }

    //QStandardItemModel* model = new QStandardItemModel();


    Print_Table();
        // устанавливаем модели данных в таблицы
        //ptwXML->setModel(model);
}
//QTableWidgetItem* MyTableWidgetFactory::createTableWidgetItem( const QString& text ) const
//{
//    QTableWidgetItem* item = new QTableWidgetItem( text );
//    item->setTextAlignment( Qt::AlignLeft );
//    return item;
//}
