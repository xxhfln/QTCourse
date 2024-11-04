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

    ui->textEdit->setEnabled(false);    // 新建文件后才显示文字编辑栏

    find = new FindText();
    find->close();
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
    this->setWindowTitle(textfilePath + "-" + this->windowTitle());
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
    ui->textEdit->setText(arr);

    ui->textEdit->setEnabled(true);
    this->setWindowTitle(textfilePath + "-" + this->windowTitle());
    file->close();
}

