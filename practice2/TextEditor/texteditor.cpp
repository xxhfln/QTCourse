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

    find = new FindText();
    find->close();
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

