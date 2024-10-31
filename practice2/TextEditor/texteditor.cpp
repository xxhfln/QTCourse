#include "texteditor.h"
#include "ui_texteditor.h"

TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TextEditor)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/images/images/main_icon.png"));
}

TextEditor::~TextEditor()
{
    delete ui;
}

