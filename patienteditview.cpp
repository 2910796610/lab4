#include "patienteditview.h"
#include "ui_patienteditview.h"
#include "idatabase.h"
#include <QSqlTableModel>

PatientEditView::PatientEditView(QWidget *parent,int index)
    : QWidget(parent)
    , ui(new Ui::PatientEditView)
{
    ui->setupUi(this);

    dataMapper= new QDataWidgetMapper(this);
    QSqlTableModel *tabModel = IDatabase::getInstance().patienttabModel;
    dataMapper->setModel(IDatabase::getInstance().patienttabModel);		//设置数据模型
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit); //数据更新方式


    //界面组件与数据模型的具体字段之间的联系
    dataMapper->addMapping(ui->adEditID,tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->adEditName,tabModel->fieldIndex("Name"));
    dataMapper->addMapping(ui->adEditIDCard,tabModel->fieldIndex("ID_CARD"));
    dataMapper->addMapping(ui->dbSpinHeight,tabModel->fieldIndex("HEIGHT"));
    dataMapper->addMapping(ui->dbSpinWeight,tabModel->fieldIndex("WEIGHT"));
    dataMapper->addMapping(ui->bdEditMobile,tabModel->fieldIndex("MOBILEPHONE"));
    dataMapper->addMapping(ui->dbDateEditDOB,tabModel->fieldIndex("DOB"));
    dataMapper->addMapping(ui->adComboSex,tabModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->bdCreateTimeStamp,tabModel->fieldIndex("CREATEDTIMESTAMP"));

    dataMapper->setCurrentIndex(index);
}

PatientEditView::~PatientEditView()
{
    delete ui;
}

void PatientEditView::on_pushButton_clicked()
{
    IDatabase::getInstance().submitPatientEdit();

    emit goPreviousView();
}


void PatientEditView::on_pushButton_2_clicked()
{
    IDatabase::getInstance().revertPatientEdit();

    emit goPreviousView();

}

