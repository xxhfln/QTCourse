#ifndef PATIENTEDITVIEW_H
#define PATIENTEDITVIEW_H

#include <QWidget>

namespace Ui {
class PatientEditView;
}

class PatientEditView : public QWidget
{
    Q_OBJECT

public:
    explicit PatientEditView(QWidget *parent = nullptr);
    ~PatientEditView();

signals:
    void cancel();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::PatientEditView *ui;
};

#endif // PATIENTEDITVIEW_H
