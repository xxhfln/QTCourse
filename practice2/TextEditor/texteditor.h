#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>

#include "common.h"
#include "findtext.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TextEditor; }
QT_END_NAMESPACE

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);
    ~TextEditor();

    FindText *find;
    QFile *file;
    QString filePath;

private slots:
    void on_new_action_triggered();

    void on_open_action_triggered();

private:
    void init();    // 初始化

    Ui::TextEditor *ui;
};
#endif // TEXTEDITOR_H
