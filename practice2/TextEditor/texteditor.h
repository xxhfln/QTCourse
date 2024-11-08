#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>

#include "common.h"
#include "findtext.h"
#include "replace.h"
#include "aboutme.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TextEditor; }
QT_END_NAMESPACE

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);
    ~TextEditor();
    QString readTxtFile(QString filepath);
    bool writeTxtFile(QString filepath, QString content);

    FindText *find;
    Replace *replace;
    AboutMe *about;
    QFile *file;
    QString filePath;
    QString fileContent;
    bool isSaved = true;

    QTextCursor cur_search_cursor;
    QString last_search_str;
    bool founded = false;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_new_action_triggered();

    void on_open_action_triggered();

    void on_textEdit_textChanged();

    void on_save_action_triggered();

    void on_save_as_action_triggered();

    void on_backout_action_triggered();

    void on_regain_action_triggered();

    void on_cut_action_triggered();

    void on_copy_action_triggered();

    void on_paste_action_triggered();

    void on_select_all_action_triggered();

    void on_textEdit_selectionChanged();

    void on_about_action_triggered();

    void on_find_action_triggered();

    void on_replace_action_triggered();

    void findText(const QString &str, bool forward);

    void on_font_action_triggered();

    void on_font_color_action_triggered();

    void on_font_background_color_action_triggered();

    void on_word_wrap_action_triggered(bool checked);

    void on_tool_bar_action_triggered(bool checked);

    void on_status_bar_action_triggered(bool checked);

private:
    void init();    // 初始化

    Ui::TextEditor *ui;
};
#endif // TEXTEDITOR_H
