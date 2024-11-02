#ifndef FINDTEXT_H
#define FINDTEXT_H

#include <QMainWindow>

namespace Ui {
class FindText;
}

class FindText : public QMainWindow
{
    Q_OBJECT

public:
    explicit FindText(QWidget *parent = nullptr);
    ~FindText();

private:
    Ui::FindText *ui;
};

#endif // FINDTEXT_H
