#include "doctorview.h"
#include "ui_doctorview.h"

Doctor::Doctor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Doctor) // 初始化 Ui::DoctorView 指针
{
    ui->setupUi(this); // 必须调用 setupUi 方法
}

Doctor::~Doctor() {
    delete ui;
}
