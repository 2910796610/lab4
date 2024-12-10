#include "wellcome.h"
#include "ui_wellcome.h"  // 包含自动生成的 UI 文件

Wellcome::Wellcome(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Wellcome)  // 正确初始化 UI 指针
{
    ui->setupUi(this);  // 调用 setupUi 初始化界面
}

Wellcome::~Wellcome() {
    delete ui;  // 释放资源
}

void Wellcome::on_btDepartment_clicked()
{
    emit goDepartmentView();
}


void Wellcome::on_btDoctor_clicked()
{
    emit goDoctorView();

}


void Wellcome::on_pushButton_3_clicked()
{
    emit goPatientView();
}

