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
    }else {
        this->setWindowTitle(filePath + " - TextEditor");
    }
}

