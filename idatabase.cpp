#include "idatabase.h"
#include <QUuid>
#include <QDebug>

void IDatabase::ininDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    QString aFile = "E:/Qt/applicantion/lab4a.db";
    database.setDatabaseName(aFile);

    if(!database.open()){
        qDebug() << "failed to open database";
    }else
        qDebug() << "open database is ok ";

}


bool IDatabase::searchPatient(QString filter)
{
    patienttabModel->setFilter(filter);
    return patienttabModel->select();

}

bool IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex = thepatientSelection->currentIndex();
    patienttabModel->removeRow(curIndex.row());
    patienttabModel->submitAll();
    patienttabModel->select();

}

bool IDatabase::submitPatientEdit()
{
    return patienttabModel->submitAll();
}

void  IDatabase::revertPatientEdit()
{
     patienttabModel->revertAll();
}


bool IDatabase::initPatientModel()
{
    patienttabModel = new QSqlTableModel(this,database);
    patienttabModel->setTable("patient");
    patienttabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);	//数据保存方式，OnManualSubmit , OnRowChange
    patienttabModel->setSort(patienttabModel->fieldIndex("name"),Qt::AscendingOrder); //排序
    if (!(patienttabModel->select()))	//查询数据失败
        return false;
    thepatientSelection = new QItemSelectionModel(patienttabModel);
    return true;



}

int IDatabase::addNewPatient()
{

    patienttabModel->insertRow(patienttabModel->rowCount(),QModelIndex());
    QModelIndex curIndex = patienttabModel->index(patienttabModel->rowCount()-1,1);

    int cutRecNO = curIndex.row();
    QSqlRecord curRec = patienttabModel->record(cutRecNO);
    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithoutBraces));
    patienttabModel->setRecord(cutRecNO,curRec);
    return curIndex.row();
}

QString IDatabase::userLogin(QString userName, QString password)
{

    //return "loginOK";
    QSqlQuery query;
    query.prepare("select username,password from user where username = :USER");
    query.bindValue(":USER",userName);
    query.exec();
    qDebug()<<query.lastQuery()<<query.first();

    if(query.first() && query.value("username").isValid()){
        QString passwd = query.value("password").toString();
        if(passwd == password)
        {
            qDebug() << "login ok";
            return "loginOk";
        }
        else{
            qDebug() << "wrongPassword";
            return "wrongPassword";
        }
    }
    else{
        qDebug()<< "no such user";
        return "wrongUsername";
    }

}

IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{
    ininDatabase();
}
