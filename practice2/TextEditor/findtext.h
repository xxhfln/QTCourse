#ifndef FINDTEXT_H
#define FINDTEXT_H

#include <QMainWindow>
#include "common.h"

namespace Ui {
class FindText;
}

class FindText : public QMainWindow
{
    Q_OBJECT

public:
    explicit FindText(QWidget *parent = nullptr);
    ~FindText();

signals:
    void findNextRequested(const QString &str);
    void findPreviousRequested(const QString &str);

private slots:
    void on_findNext_clicked();

private:
    void init();

    Ui::FindText *ui;
};

#endif // FINDTEXT_H
