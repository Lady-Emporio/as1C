#include "neutral_func.h"

QString neutral_getArmor(QString orderCode)
{
    QSqlQuery query(Settings::S()->_db);
    QString sql="select "
           " managers._nameForArmour as _nameForArmour, "
            " orders._client as _client, "
            " orders._workList as _workList"
            " from orders "
            " left join managers on "
            " orders._manager=managers._code "
            " where orders._id=:code;";
    query.prepare(sql);
    query.bindValue(":code",orderCode);
    if(!query.exec()){
        QMessageBox msgBox;
        msgBox.setText("Не получается сформировать бронь\n\n"+Settings::S()->_db.lastError().text()+" |\n "+query.lastError().text()+" |\n "+query.lastQuery());
        msgBox.exec();
        return "";
    }
    query.next();
    QString armorText="A/м найден "+QDate::currentDate().toString("yyyy-MM-dd")+" "+query.value("_nameForArmour").toString()+" для "+query.value("_client").toString()+" РЛ "+query.value("_workList").toString()+" до п"+QDate::currentDate().addDays(7).toString("dd.MM");
    return armorText;
}
