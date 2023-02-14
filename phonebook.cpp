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

void PhoneBook::CreateMenu()
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
    //====================================================//


    //====================================================//
    // Функции подменю справочника физических лиц

void PhoneBook::AddRecordIndividuals()
{
    QModelIndexList modelIndex;
    formAddIndividuals = new FormIndividuals(-1,db,modeldb);
    formAddIndividuals->show();
}

void PhoneBook::EditRecordIndividuals()
{
    OpenIndividuals();
    QModelIndexList modelIndex= ptvSQL->selectionModel()->selectedRows();
    formindividualsEdit = new FormindividualsEdit(0,db,modeldb,modelIndex);
    formindividualsEdit->show();
}

void PhoneBook::DeleteRecordIndividuals()
{
    OpenIndividuals();
    QModelIndexList modelIndex= ptvSQL->selectionModel()->selectedRows();
    formindividualsEdit = new FormindividualsEdit(1,db,modeldb,modelIndex);
    formindividualsEdit->show();
}



void PhoneBook::SearchRecordNameIndividuals()
{
    OpenIndividuals();
    QModelIndexList modelIndex;
    formAddIndividuals = new FormIndividuals(2,db,modeldb);
    formAddIndividuals->show();
}

void PhoneBook::SearchRecordSurnameIndividuals()
{
    OpenIndividuals();
    QModelIndexList modelIndex;
    formAddIndividuals = new FormIndividuals(3,db,modeldb);
    formAddIndividuals->show();
}

void PhoneBook::SearchRecordNumberIndividuals()
{
    OpenIndividuals();
    QModelIndexList modelIndex;
    formAddIndividuals = new FormIndividuals(4,db,modeldb);
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
    //====================================================//


    //====================================================//
    // Функции подменю справочника физических лиц

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
//====================================================//


//====================================================//
// Функции в pgbLower

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
    if(plDirIndividual->isVisible())
    {
        modeldb->setTable("Records");
        modeldb->select();
    }
    else
        Print_Table();
}

void PhoneBook::Map()
{
    if(plDirIndividual->isVisible())
        SearcheRecordMapIndividuals();
    else
        SearcheRecordMapEntitie();
}
//====================================================//


//====================================================//
// Функции смены отображения справочников

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

    Print_Table();
}
//====================================================//


//====================================================//
// Вспомогательные функции

void PhoneBook::Close_msg(QString notification_text)
{
    QMessageBox msg;
    msg.setText(notification_text);
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
                // НАД ИФАМИ ПОДУМАТЬ

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
    QMapIterator<QString, Company> iterator_map (mapCompany);
    while (iterator_map.hasNext())
    {
        iterator_map.next();
        ptwXML->setRowCount(ptwXML->rowCount() + 1);

        //QTableWidgetItem *newItem;

        ptwXML->setItem(ptwXML->rowCount() - 1, 0, new QTableWidgetItem(iterator_map.value().title));

        ptwXML->setItem(ptwXML->rowCount() - 1, 1, new QTableWidgetItem(iterator_map.value().director));

        ptwXML->setItem(ptwXML->rowCount() - 1, 2, new QTableWidgetItem(iterator_map.value().phone_director));

        ptwXML->setItem(ptwXML->rowCount() - 1, 3, new QTableWidgetItem(iterator_map.value().contact_person));

        ptwXML->setItem(ptwXML->rowCount() - 1, 4, new QTableWidgetItem(iterator_map.value().phone_contact_person));

        ptwXML->setItem(ptwXML->rowCount() - 1, 5, new QTableWidgetItem(iterator_map.key()));

        ptwXML->setItem(ptwXML->rowCount() - 1, 6, new QTableWidgetItem(iterator_map.value().adress));

        ptwXML->setItem(ptwXML->rowCount() - 1, 7, new QTableWidgetItem(iterator_map.value().branch));

        ptwXML->setItem(ptwXML->rowCount() - 1, 8, new QTableWidgetItem(iterator_map.value().description));
    }
    for(int i=0;i<ptwXML->columnCount()+1;i++)
        ptwXML->verticalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}
