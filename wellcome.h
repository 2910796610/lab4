#ifndef WELLCOME_H
#define WELLCOME_H

#include <QWidget>

namespace Ui {
class Wellcome;  // 声明 UI 类
}

class Wellcome : public QWidget {
    Q_OBJECT

public:
    explicit Wellcome(QWidget *parent = nullptr);
    ~Wellcome();

private slots:
    void on_btDepartment_clicked();

    void on_btDoctor_clicked();

    void on_pushButton_3_clicked();

signals:
    void goDepartmentView();

    void goDoctorView();

    void goPatientView();

private:
    Ui::Wellcome *ui;  // 定义指向 UI 类的成员变量
};

#endif // WELLCOME_H
