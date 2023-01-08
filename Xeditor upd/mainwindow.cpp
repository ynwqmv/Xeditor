#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QMainWindow>

#include <QTextEdit>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

#include <QToolBar>
#include <QStringList>
#include <QClipboard>
#include <QTimer>
#include <QStatusBar>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QStatusBar>
#include <QStack>
#include <QStyleFactory>

#include <QString>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);

    setCentralWidget(ui->textEdit);
    setWindowTitle("Xeditor");

    QMenu* fileMenu = menuBar()->addMenu("File");
    QMenu* fileAbout = menuBar()->addMenu("Tools");






  /**/  /*                   FILEMENU                             */
  /**/  QAction *openAction = fileMenu->addAction("Open...");   /**/
  /**/  QAction *saveAction = fileMenu->addAction("Save As...");/**/
  /**/  fileMenu->addSeparator();
        QAction *exAction = fileMenu->addAction("Exit");        /**/
  /**/  QAction* separator = new QAction(fileMenu);             /**/
  /**/  separator->setSeparator(true);                          /**/
  /**/  fileMenu->addAction(separator);                         /**/
  //////////////////////////////////////////////////////////////////




    QToolBar *toolbarr = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, toolbarr);
    QAction *oA = new QAction(QIcon("C:/Users/qumar/OneDrive/Desktop/Resources/open.png"), "Open", this);
    QAction *sA = new QAction(QIcon("C:/Users/qumar/OneDrive/Desktop/Resources/save.png"), "Save", this);
    QAction *cA = new QAction(QIcon("C:/Users/qumar/OneDrive/Desktop/Resources/copy.png"), "Copy", this);
    QAction *pA = new QAction(QIcon("C:/Users/qumar/OneDrive/Desktop/Resources/paste.png"), "Paste", this);
    QAction *clA = new QAction(QIcon("C:/Users/qumar/OneDrive/Desktop/Resources/clear.png"), "Clear", this);
    QAction *prA = new QAction(QIcon("C:/Users/qumar/OneDrive/Desktop/Resources/Undo-icon.png"), "Undo", this);
    QAction *aboutA = new QAction(QIcon("C:/Users/qumar/OneDrive/Desktop/Resources/about.png"), "About", this);

    QIcon icon("C:/Users/qumar/OneDrive/Desktop/Resources/text_editor.png");

    setWindowIcon(icon);




    toolbarr->addAction(oA);
    toolbarr->addSeparator();
    toolbarr->addAction(sA);
    toolbarr->addAction(cA);
    toolbarr->addAction(pA);
    toolbarr->addSeparator();
    toolbarr->addAction(prA);
    toolbarr->addAction(clA);
    toolbarr->addSeparator();
    toolbarr->addAction(aboutA);




   QAction *copyAction   = fileAbout->addAction("Copy");
   QAction *pasteAction  = fileAbout->addAction("Paste");
   QAction *clearAction  = fileAbout->addAction("Clear");
   QAction *uclearAction = fileAbout->addAction("Undo clear");
   fileAbout->addSeparator();
   QAction *aboutAction  = fileAbout->addAction("About");



    connect(openAction,  &QAction::triggered, this, &MainWindow::open);
    connect(saveAction,  &QAction::triggered, this, &MainWindow::save);
    connect(exAction,    &QAction::triggered, this, &MainWindow::exit);

    connect(copyAction,  &QAction::triggered, this, &MainWindow::copy);
    connect(pasteAction, &QAction::triggered, this, &MainWindow::paste);
    connect(clearAction, &QAction::triggered, this, &MainWindow::clear);
    connect(uclearAction,&QAction::triggered, this, &MainWindow::undo);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

    connect(oA,          &QAction::triggered, this, &MainWindow::open);
    connect(cA,          &QAction::triggered, this, &MainWindow::copy);
    connect(sA,          &QAction::triggered, this, &MainWindow::save);
    connect(pA,          &QAction::triggered, this, &MainWindow::paste);
    connect(prA,         &QAction::triggered, this, &MainWindow::undo);

    connect(clA,         &QAction::triggered, this, &MainWindow::clear);
    connect(aboutA,      &QAction::triggered, this, &MainWindow::about);


    ui->statusbar->showMessage("Ready");
}

QStack<QString> textStack;

void MainWindow::open()
{

    QString fileName = QFileDialog::getOpenFileName(this,"Open File");
    if (fileName.isEmpty())
    {
        return;
    }

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"Error", "Can not open file: " + file.errorString());
        return;
    }

    QTextStream in(&file);
    ui->textEdit->setPlainText(in.readAll());

    ui->statusbar->showMessage("Opened successfully!");
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save As");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot save file: " + file.errorString());
        return;
    }

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    ui->statusbar->showMessage("Saved successfully!");
}

void MainWindow::about()
{
    QMessageBox::information(this,tr("About"), tr("\t\tXeditor 0.1.2\n\n"
                                                  "Beta Verison of free open-source text Editor.\n"
                                                  "If you have any questions, goto 'Xeditor' GitHub page:\n"
                                                  "\nhttps://github.com/ynwqmv"),
                                                   QMessageBox::Ok);


    ui->statusbar->showMessage("About");
}

void MainWindow::exit()
{
    QMessageBox::information(this,tr("Close"), tr("Thank you for using Xeditor!"), QMessageBox::Ok);
    QApplication::exit();
}

void MainWindow::copy()
{
    // Get the text from the QLineEdit
    QString text = ui->textEdit->textCursor().selectedText();

    // Create a QClipboard object and copy the text to it
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(text);

    QMessageBox::information(this,"Copy", "Text copied to clipboard successfully.", QMessageBox::Ok);
    ui->statusbar->showMessage("Copied");
}

void MainWindow::paste()
{
    // Create a QClipboard object and get the text from it
    QClipboard *clipboard = QApplication::clipboard();
    QString text = clipboard->text();

    // Insert the clipboard text into the QTextEdit
    ui->textEdit->insertPlainText(text);
    QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setWindowTitle("Paste");
        messageBox->setText("Text pasted from clipboard successfully.");
        messageBox->setStandardButtons(QMessageBox::Ok);

        // Disable the message box when it first appears

        // Show the message box
        messageBox->show();

        ui->statusbar->showMessage("Pasted");
}

void MainWindow::clear()
{

    textStack.push(ui->textEdit->toPlainText());

    ui->textEdit->clear();
    ui->statusbar->showMessage("Cleared");
}

void MainWindow::undo()
{
    if(!textStack.isEmpty())
    {
        QString text = textStack.pop();

        ui->textEdit->setPlainText(text);
        ui->statusbar->showMessage("Undo successful");
    }

    QMessageBox::information(this,tr("Undo"), tr("Undo successful"), QMessageBox::Ok);
}


MainWindow::~MainWindow()
{
    delete ui;
}



