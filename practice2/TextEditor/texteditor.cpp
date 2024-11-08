#include "texteditor.h"
#include "ui_texteditor.h"

TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TextEditor)
{
    ui->setupUi(this);

    init();
}

TextEditor::~TextEditor()
{
    delete ui;
}

void TextEditor::init(){    // 初始化
    this->setWindowIcon(QIcon(":/images/images/main_icon.png"));    // 设置图标

    // 设置默认编码 UTF-8
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QLabel *encodingLabel = new QLabel("编码:UTF-8",this);
    ui->statusbar->addWidget(encodingLabel);

    ui->textEdit->setEnabled(false);    // 新建文件后才显示文字编辑栏
    ui->save_action->setEnabled(false);
    ui->save_as_action->setEnabled(false);
    ui->cut_action->setEnabled(false);
    ui->copy_action->setEnabled(false);
    ui->paste_action->setEnabled(false);
    ui->find_action->setEnabled(false);
    ui->replace_action->setEnabled(false);

    find = new FindText();
    find->close();
    replace = new Replace();
    replace->close();
    about = new AboutMe();
    about->close();

    cur_search_cursor = QTextCursor();
    last_search_str = QString();

    connect(find,&FindText::findPreviousRequested,this,[this](const QString &str){findText(str, true);});
    connect(find,&FindText::findNextRequested,this,[this](const QString &str){findText(str, false);});
}

QString TextEditor::readTxtFile(QString filepath){
    if (filepath.isNull()){
        return QString();
    }
    QFile file(filepath);
    QString file_content;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        file_content = in.readAll();
        file.close();
    }
    return file_content;
}


bool TextEditor::writeTxtFile(QString filepath, QString content){
    if (filepath.isNull()){
        return false;
    }
    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return false;
    }
    QTextStream out(&file);
    out << content;

    file.close();
    return true;
}


void TextEditor::on_new_action_triggered()
{
    // 桌面路径
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString textfilePath = QFileDialog::getSaveFileName(this,"新建文件",desktopPath,"text(*.txt)");
    if (textfilePath.isNull()){
        QMessageBox::information(this,"提示","未保存选中文件");
    }
    qDebug()<<textfilePath;

    file = new QFile(textfilePath);
    filePath = textfilePath;
    if (!file->open(QFile::ReadWrite)){
        return;
    }
    file->close();

    ui->textEdit->setEnabled(true);
    this->setWindowTitle(textfilePath + " - TextEditor");
}


void TextEditor::on_open_action_triggered()
{
    // 桌面路径
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString textfilePath = QFileDialog::getOpenFileName(this,"打开文件",desktopPath,"text(*.txt)");
    if (textfilePath.isNull()){
        QMessageBox::critical(this,"ERROR","无法打开文件");
        return;
    }

    file = new QFile(textfilePath);
    filePath = textfilePath;
    if (!file->open(QFile::ReadOnly)){
        return;
    }

    QByteArray arr = file->readAll(); // 读取文件所有内容，以字节数组形式保存
    this->fileContent = readTxtFile(textfilePath);
    ui->textEdit->setText(arr);

    ui->textEdit->setEnabled(true);
    this->setWindowTitle(textfilePath + " - TextEditor");
    file->close();
}


void TextEditor::on_textEdit_textChanged()
{
    if (ui->textEdit->toPlainText() != fileContent){
        this->setWindowTitle(filePath + " - TextEditor*");
        ui->save_action->setEnabled(true);
        isSaved = false;
    }else {
        this->setWindowTitle(filePath + " - TextEditor");
        ui->save_action->setEnabled(false);
        isSaved = true;
    }
    ui->save_as_action->setEnabled(true);
    ui->find_action->setEnabled(true);
    ui->replace_action->setEnabled(true);
}


void TextEditor::on_save_action_triggered()
{
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this, "ERROR", "无法打开文件");
        return;
    }
    QTextStream out(this->file);
    out << ui->textEdit->toPlainText();

    file->close();
    this->fileContent = readTxtFile(filePath);
    this->setWindowTitle(filePath + " - TextEditor");
    ui->save_action->setEnabled(false);
    isSaved = true;
}


void TextEditor::on_save_as_action_triggered()
{
    // 桌面路径
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString textfilePath = QFileDialog::getSaveFileName(this,"另存为文件",desktopPath,"text(*.txt)");
    if (textfilePath.isNull()){
        QMessageBox::information(this,"提示","未另存为文件");
    }
//    qDebug()<<textfilePath;

    file = new QFile(textfilePath);
    filePath = textfilePath;
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }
    QTextStream out(this->file);
    out << ui->textEdit->toPlainText();
    file->close();

    this->setWindowTitle(textfilePath + " - TextEditor");
    ui->save_action->setEnabled(false);
    isSaved = true;
}


void TextEditor::closeEvent(QCloseEvent *event)
{
    if (!isSaved){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Unsaved Changes","有未保存的文件，是否保存？"
                ,QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes){
            writeTxtFile(filePath, ui->textEdit->toPlainText());
            event->accept();
        }else if (reply == QMessageBox::No){
            event->accept();
        }else if (reply == QMessageBox::Cancel){
            event->ignore();
        }
    }else {
        event->accept();
    }
}


void TextEditor::on_backout_action_triggered()
{
    ui->textEdit->undo();
}


void TextEditor::on_regain_action_triggered()
{
    ui->textEdit->redo();
}


void TextEditor::on_cut_action_triggered()
{
    ui->textEdit->cut();
}


void TextEditor::on_copy_action_triggered()
{
    ui->textEdit->copy();
}


void TextEditor::on_paste_action_triggered()
{
    ui->textEdit->paste();
}


void TextEditor::on_select_all_action_triggered()
{
    ui->textEdit->selectAll();
}


void TextEditor::on_textEdit_selectionChanged()
{
    // 文本未选中时，剪切、复制、粘贴按键不使能
    if (ui->textEdit->textCursor().hasSelection()){
        ui->cut_action->setEnabled(true);
        ui->copy_action->setEnabled(true);
        ui->paste_action->setEnabled(true);
    }else {
        ui->cut_action->setEnabled(false);
        ui->copy_action->setEnabled(false);
        ui->paste_action->setEnabled(false);
    }

};


void TextEditor::on_about_action_triggered()
{
    this->about->show();
}


void TextEditor::on_find_action_triggered()
{
    this->find->show();
}


void TextEditor::on_replace_action_triggered()
{
    this->replace->show();
}


void TextEditor::findText(const QString &str, bool forward){
    QTextDocument *document = ui->textEdit->document();

    QTextCursor cursor(document);
    if (cur_search_cursor.isNull()){
        cur_search_cursor = cursor;
        founded = false;
    }
    if (str != last_search_str){
        cur_search_cursor = cursor;
        founded = false;
    }

    if ((!cur_search_cursor.isNull() && !cur_search_cursor.atEnd())
        || (cur_search_cursor.atEnd() && forward)){
        cursor = forward?document->find(str,cur_search_cursor,QTextDocument::FindBackward):
                     document->find(str,cur_search_cursor);
        if (!cursor.isNull()){
            cursor.movePosition(QTextCursor::NoMove,QTextCursor::KeepAnchor);
            ui->textEdit->setTextCursor(cursor);
            cur_search_cursor = cursor;
            founded = true;
        }else if(cursor.isNull() && !founded){
            QMessageBox::information(this,"提示","无法找到您所查找的内容");
        }else{  // 已是最后一处
            QMessageBox::information(this,"提示","已完成对文档的搜索");
            cur_search_cursor = QTextCursor();
        }


    }else if (cur_search_cursor.atEnd() && founded){
        QMessageBox::information(this,"提示","已完成对文档的搜索");
        cur_search_cursor = QTextCursor();
    }else{
        QMessageBox::information(this,"提示","无法找到您所查找的内容");
    }

    last_search_str = str; // 记录上次搜索的文本
}


void TextEditor::on_font_action_triggered()
{
    bool ok;
    QTextCursor cursor = ui->textEdit->textCursor();
    QFont selection_font("微软雅黑",15,15,false);
    if (cursor.hasSelection()){
        selection_font = cursor.charFormat().font();
    }else{
        QMessageBox::information(this,"提示","请先选择一段文本");
        return;
    }
    QFont font = QFontDialog::getFont(&ok,selection_font,this,"选择字体");
    if (ok){
//        ui->textEdit->setFont(font); // 设置全部字体变化
        ui->textEdit->setCurrentFont(font); // 设置选中字体变化
    }
}


void TextEditor::on_font_color_action_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QColor selection_color("black");
    if (cursor.hasSelection()){
        selection_color = cursor.charFormat().foreground().color();
    }else{
        QMessageBox::information(this,"提示","请先选择一段文本");
        return;
    }
    QColor color = QColorDialog::getColor(selection_color,this,"选择颜色");
    if (color.isValid()){
        ui->textEdit->setTextColor(color);
    }
}


void TextEditor::on_font_background_color_action_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QColor selection_color("black");
    if (cursor.hasSelection()){
        selection_color = cursor.charFormat().foreground().color();
    }else{
        QMessageBox::information(this,"提示","请先选择一段文本");
        return;
    }
    QColor color = QColorDialog::getColor(selection_color,this,"选择颜色");
    if (color.isValid()){
        ui->textEdit->setTextBackgroundColor(color);
    }
}


void TextEditor::on_word_wrap_action_triggered(bool checked)
{
    if (checked){
        ui->textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    }else{
        ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
    }
}


void TextEditor::on_tool_bar_action_triggered(bool checked)
{
    ui->toolBar->setVisible(checked);
}


void TextEditor::on_status_bar_action_triggered(bool checked)
{
    ui->statusbar->setVisible(checked);
}

