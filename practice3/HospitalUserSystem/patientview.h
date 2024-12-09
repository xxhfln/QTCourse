#ifndef PATIENTVIEW_H
#define PATIENTVIEW_H

#include <QWidget>
#include "database.h"

namespace Ui {
class PatientView;
}

class PatientView : public QWidget
{
    Q_OBJECT

public:
    explicit PatientView(QWidget *parent = nullptr);
    ~PatientView();

signals:
    void goPatientEdit(int index);

private slots:
    void on_pushButton_2_clicked();

    void on_btn_find_clicked();

    void on_btn_delete_clicked();

    void on_btn_edit_clicked();

private:
    Ui::PatientView *ui;
};

#endif // PATIENTVIEW_H
