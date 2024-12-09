#ifndef PATIENTVIEW_H
#define PATIENTVIEW_H

#include <QWidget>

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
    void goPatientEdit();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::PatientView *ui;
};

#endif // PATIENTVIEW_H
