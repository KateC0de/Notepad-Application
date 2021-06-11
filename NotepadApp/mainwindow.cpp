#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");   //assign a file name to open up a file dialog to allow the user to select which text file they want to work with
    QFile file(filename);   //object for reding/writing files
    currentFile = filename;   //store that current file name inside our current file
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){   //try to open up file as a read only, otherwise open a message box to indicate that something went wrong
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    //otherwise assume everythong is going fine
    setWindowTitle(filename);
    QTextStream in(&file);  //create interface for reading text
    QString text = in.readAll();    //copy the text in the string
    ui->textEdit->setText(text);    //put text in our text edit widget on the screen
    file.close();   //close the file
}


void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");    //open a dialog for saving a file
    QFile file(fileName);   //object for reding/writing files
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;   //allows to interact with any printer on the network
    printer.setPrinterName("Printer Name");
    QPrintDialog pDialog(&printer, this);    //printer dilog that allows the user to select the actual printer that they want to use
    if(pDialog.exec() == QDialog::Rejected){    //verify I was able to connect to the printer and had no errors
        QMessageBox::warning(this, "Warning", "Cannot Access Printer");
        return;
    }
    //send text in out text editor to the printer
    ui->textEdit->print(&printer);
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

