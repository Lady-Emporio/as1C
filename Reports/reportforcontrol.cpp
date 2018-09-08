#include "reportforcontrol.h"

void ReportForControl::makeGui()
{
    m_document=new QTextDocument(this);
    m_cursor=new QTextCursor(m_document);
    docView=new QTextEdit(this);
    docView->setDocument(m_document);
    QDateTime startMonth;
    QString nowYear=QString("").setNum(QDate::currentDate().year());
    QString nowMonth=QString("").setNum(QDate::currentDate().month());
    startMonth=QDateTime::fromString(nowYear+"."+nowMonth+".1 00:00:00","yyyy.M.d HH:mm:ss");
    beginPar=new QDateTimeEdit(startMonth,this);
    beginPar->setCalendarPopup(true);
    beginPar->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    endPar=new QDateTimeEdit(startMonth.addMonths(1).addSecs(-1),this);
    endPar->setCalendarPopup(true);
    endPar->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);
    QHBoxLayout * parLayout=new QHBoxLayout(this);
    parLayout->addWidget(beginPar);
    parLayout->addWidget(endPar);
    mainLayout->addLayout(parLayout);
    mainLayout->addWidget(docView);
    QMenuBar*mainMenu=new QMenuBar(this);
    mainLayout->setMenuBar(mainMenu);
    mainMenu->addAction("Create",this,SLOT(action_CreateReport()));
}

void ReportForControl::setTitle()
{
    m_cursor->movePosition(QTextCursor::End);
    m_cursor->insertBlock();
    m_cursor->insertBlock();
    QString title="Отчет по найденным авто с: "+beginPar->text()+" по "+endPar->text();
    QTextCharFormat formatTitle;
    formatTitle.setFontWeight(QFont::Bold);
    formatTitle.setFontFamily("Times New Roman");
    formatTitle.setFontPointSize(20);
    m_cursor->insertText(title,formatTitle);
}

void ReportForControl::setTable()
{
    QTextTableFormat tableFormat;
    tableFormat.setAlignment(Qt::AlignHCenter); //выравнивание
    tableFormat.setCellPadding(2);
    tableFormat.setCellSpacing(2);
    table = m_cursor->insertTable(1, 13);
    table->setFormat(tableFormat);

//    destinyTrade._boughtCliend as _boughtCliend,
//    destinyTrade._soldManager as _soldManager,
//    destinyTrade._dateSold as _dateSold,
//    managers._nameForArmour as _nameForArmour,
//    orders._client as findForClient,
//    orders._workList as findForWorkList,
//    trade._getDate as _getDate,
//    trade._getCar as _getCar,
//    trade._getVin as _getVin,
//    trade._giveAwayCar as _giveAwayCar,
//    trade._giveAwayVin as _giveAwayVin,
//    trade._giveAwayDate as _giveAwayDate,
//    trade._color_option_trade as _color_option_trade

    table->cellAt(0, 0).firstCursorPosition().insertText("Купил клиент:");
    table->cellAt(0, 1).firstCursorPosition().insertText("Продал менеджер:");
    table->cellAt(0, 2).firstCursorPosition().insertText("Дата продажи:");
    table->cellAt(0, 3).firstCursorPosition().insertText("Менеджер:");
    table->cellAt(0, 4).firstCursorPosition().insertText("Клиент:");
    table->cellAt(0, 5).firstCursorPosition().insertText("РЛ:");
    table->cellAt(0, 6).firstCursorPosition().insertText("Дата полученного:");
    table->cellAt(0, 7).firstCursorPosition().insertText("Вин полученный:");
    table->cellAt(0, 8).firstCursorPosition().insertText("Модель полученная:");
    table->cellAt(0, 9).firstCursorPosition().insertText("Дата отданного:");
    table->cellAt(0, 10).firstCursorPosition().insertText("Вин отданного:");
    table->cellAt(0, 11).firstCursorPosition().insertText("Модель отданного:");
    table->cellAt(0, 12).firstCursorPosition().insertText("Цвета опции обмена:");

}

void ReportForControl::getSqlTable()
{
    QSqlQuery query(Settings::S()->_db);
    QString sql="SELECT "
            " destinyTrade._boughtCliend as _boughtCliend, "
            " destinyTrade._soldManager as _soldManager, "
            " destinyTrade._dateSold as _dateSold, "
            " managers._nameForArmour as _nameForArmour, "
            " orders._client as findForClient, "
            " orders._workList as findForWorkList, "
            " trade._getDate as _getDate, "
            " (SELECT cars._name FROM cars WHERE cars._id=trade._getCar) as _getCar, "
            " trade._getVin as _getVin, "
            " (SELECT cars._name FROM cars WHERE cars._id=trade._giveAwayCar) as _giveAwayCar, "
            " trade._giveAwayVin as _giveAwayVin, "
            " trade._giveAwayDate as _giveAwayDate, "
            " trade._color_option_trade as _color_option_trade "
        " FROM trade "
        " LEFT JOIN orders ON "
        "   orders._id=trade._orders "
        " LEFT JOIN managers ON "
        "     managers._code=orders._manager "
        " LEFT JOIN destinyTrade ON "
        "     destinyTrade._parentTrade=trade._id "  
        " WHERE "
        "     trade._date >= :dateBegin and trade._date <= :dateEnd "
        "     and trade._status='Учитывать в отчете по поиску';";
    query.prepare(sql);
    query.bindValue(":dateBegin",beginPar->text());
    query.bindValue(":dateEnd",endPar->text());
    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText("Не получается выбрать данные для отчета\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return;
    }
    while(query.next()){
        table->appendRows(1);
        int row=table->rows()-1;
        table->cellAt(row, 0).firstCursorPosition().insertText(query.value("_boughtCliend").toString());
        table->cellAt(row, 1).firstCursorPosition().insertText(query.value("_soldManager").toString());
        table->cellAt(row, 2).firstCursorPosition().insertText(query.value("_dateSold").toString());
        table->cellAt(row, 3).firstCursorPosition().insertText(query.value("_nameForArmour").toString());
        table->cellAt(row, 4).firstCursorPosition().insertText(query.value("findForClient").toString());
        table->cellAt(row, 5).firstCursorPosition().insertText(query.value("findForWorkList").toString());
        table->cellAt(row, 6).firstCursorPosition().insertText(query.value("_getDate").toString());
        table->cellAt(row, 7).firstCursorPosition().insertText(query.value("_getVin").toString());
        table->cellAt(row, 8).firstCursorPosition().insertText(query.value("_getCar").toString());
        table->cellAt(row, 9).firstCursorPosition().insertText(query.value("_giveAwayDate").toString());
        table->cellAt(row, 10).firstCursorPosition().insertText(query.value("_giveAwayVin").toString());
        table->cellAt(row, 11).firstCursorPosition().insertText(query.value("_giveAwayCar").toString());
        table->cellAt(row, 12).firstCursorPosition().insertText(query.value("_color_option_trade").toString());
    };
}

ReportForControl::ReportForControl(QWidget *parent) : QWidget(parent)
{

    makeGui();
}

void ReportForControl::action_CreateReport()
{
    m_document->clear();
    setTitle();
    setTable();
    getSqlTable();
}
