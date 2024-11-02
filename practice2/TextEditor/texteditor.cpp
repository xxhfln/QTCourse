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

    find = new FindText();
    find->close();
}

void TextEditor::on_new_action_triggered()
{
    // 桌面路径
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString textfileName = QFileDialog::getOpenFileName(this,"new txt",desktopPath,"text(*.txt)");
    qDebug()<<textfileName;
}

