#include <qdebug.h>
#include <QFileDialog>
#include <QtXml>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_closeButton_clicked()
{
    close();
}

void MainWindow::on_addButton_clicked()
{
    if(!ui->lineEdit->text().isEmpty()) {
        int startTime = ui->recordStartTimeEdit->time().hour()*3600 + ui->recordStartTimeEdit->time().minute()*60 +
                ui->recordStartTimeEdit->time().second();

        int markTime = ui->timeEdit->time().hour()*3600 + ui->timeEdit->time().minute()*60 +
                ui->timeEdit->time().second();

        item mark;
        mark.time = ui->timeEdit->time().toString();
        mark.desc = ui->lineEdit->text();
        mark.minute = (markTime - startTime)/60;
        mark.seconds = (markTime - startTime)%60;

        items.append(mark);
        ui->listWidget->addItem(mark.time + " " + mark.desc);
    }
}

void MainWindow::on_xmlButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "Выбор папки", "");

    QTime expTime = ui->experementStartTimeEdit->time();
    if(!(expTime.hour()==0 && expTime.minute()==0 && expTime.second()==0)) {
        int startRecordTime = ui->recordStartTimeEdit->time().hour()*3600 + ui->recordStartTimeEdit->time().minute()*60 +
                ui->recordStartTimeEdit->time().second();
        int startExperementTime = ui->experementStartTimeEdit->time().hour()*3600 + ui->experementStartTimeEdit->time().minute()*60 +
                ui->experementStartTimeEdit->time().second();

        minute = (startRecordTime - startExperementTime)/60;
        seconds = (startRecordTime - startExperementTime)%60;
    }

    QDomDocument doc("rat");
        QDomElement  domElement = doc.createElement("rat");
        domElement.setAttribute("number", ui->spinBox->value());
        domElement.setAttribute("start_global_time", QString::number(minute)+'.'+QString::number(seconds));
        doc.appendChild(domElement);

        QDomElement itemElement;
        for(int i=0;i<items.count();++i) {
            itemElement = doc.createElement("time_mark");
            itemElement.setAttribute("time", QString::number(items[i].minute)+'.'+QString::number(items[i].seconds));
            itemElement.setAttribute("desc", items[i].desc);
            domElement.appendChild(itemElement);
        }

        QFile file(path + "/rat"+QString::number(ui->spinBox->value())+".xml");
        if(!file.exists()) {
            if(file.open(QIODevice::WriteOnly)) {
                QTextStream ts(&file);
                ts.setCodec(QTextCodec::codecForName("UTF-8"));
                ts << doc.toString();
                file.close();
            }
        } else {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Ошибка!");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("Файл с таким именем уже существует!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            return;
        }

        close();
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    delete item;
}
