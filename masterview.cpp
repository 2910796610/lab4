#include "masterview.h"
#include "ui_masterview.h"
#include <QDebug>
#include "idatabase.h"

MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);

    gologinView();

    IDatabase::getInstance();
}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::gologinView()
{
    qDebug()<<"goLoginView";
    loginView = new LoginView(this);
    pushWidgetToStackView(loginView);

    connect (loginView,SIGNAL(loginSuccess()),this,SLOT(goWelcomeView()));

}

void MasterView::goWelcomeView()
{
    qDebug()<<"goWelcomeView";
    welcomeView = new Wellcome(this);
    pushWidgetToStackView(welcomeView);

    connect (welcomeView,SIGNAL(goDoctorView()),this,SLOT(goDoctorView()));
    connect (welcomeView,SIGNAL(goPatientView()),this,SLOT(goPaitentView()));
    connect (welcomeView,SIGNAL(goDepartmentView()),this,SLOT(goDepartmentView()));




}

void MasterView::goDoctorView()
{
    qDebug()<<"goDoctorView";
    doctorView = new Doctor(this);
    pushWidgetToStackView(doctorView);

}

void MasterView::goDepartmentView()
{
    qDebug()<<"goDepartmentView";
    departmentView = new DepartmentView(this);
    pushWidgetToStackView(departmentView);

}

void MasterView::goPatientEditView(int rowNo)
{
    qDebug()<<"goPatientEditView";
    patientEditView = new PatientEditView(this,rowNo);
    pushWidgetToStackView(patientEditView);

    connect (patientEditView,SIGNAL(goPreviousView()),this,SLOT(goPreviousView()));


}

void MasterView::goPaitentView()
{

    qDebug()<<"goPaitentView";
    patientView = new PatientView(this);
    pushWidgetToStackView(patientView);

    connect (patientView,SIGNAL(goPaitentEditView(int)),this,SLOT(goPatientEditView(int)));

}

void MasterView::goPreviousView()
{
    int count = ui->stackedWidget->count();

    if(count > 1){
        ui->stackedWidget->setCurrentIndex(count-2);
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());

        QWidget *widget = ui->stackedWidget->widget(count - 1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }
}

void MasterView::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);

    int count =ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count-1);
    ui->labelTitle->setText(widget->windowTitle());

}

void MasterView::on_btBack_clicked()
{
    goPreviousView();
}


void MasterView::on_stackedWidget_currentChanged(int arg1)
{
    int count = ui->stackedWidget->count();
    if(count > 1)
        ui->btBack->setEnabled(true);
    else
        ui->btBack->setEnabled(false);

    QString title = ui->stackedWidget->currentWidget()->windowTitle();
    if(title == "欢迎"){
        ui->btLogout->setEnabled(true);
        ui->btBack->setEnabled(false);
    } else
        ui->btLogout->setEnabled(false);
}


void MasterView::on_btLogout_clicked()
{
    goPreviousView();
}
