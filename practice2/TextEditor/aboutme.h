#ifndef ABOUTME_H
#define ABOUTME_H

#include <QMainWindow>

namespace Ui {
class AboutMe;
}

class AboutMe : public QMainWindow
{
    Q_OBJECT

public:
    explicit AboutMe(QWidget *parent = nullptr);
    ~AboutMe();

private:
    Ui::AboutMe *ui;
};

#endif // ABOUTME_H
