#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QDebug>
#include <QLineEdit>

struct widgets {
    int id = 0;
    int type = 0;
    QObject *widget;
};

QVector<widgets> store;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    widgets temp;

    temp.id = store.size();
    temp.type = 0;
    store.push_back(temp);
    store.last().widget = new QPushButton(this);
    qobject_cast<QPushButton*>(store.last().widget)->setText("Добавить кнопку");
    ui->horizontalLayout->addWidget(qobject_cast<QPushButton*>(store.last().widget));
    connect(store.last().widget, SIGNAL(clicked()), this, SLOT(slotDynamic()));

    temp.id = store.size();
    temp.type = 0;
    store.push_back(temp);
    store.last().widget = new QPushButton(this);
    qobject_cast<QPushButton*>(store.last().widget)->setText("Удалить кнопку");
    qobject_cast<QPushButton*>(store.last().widget)->setEnabled(false);
    ui->horizontalLayout->addWidget(qobject_cast<QPushButton*>(store.last().widget));
    connect(store.last().widget, SIGNAL(clicked()), this, SLOT(slotDynamic()));

    temp.id = store.size();
    temp.type = 1;
    store.push_back(temp);
    store.last().widget = new QPushButton(this);
    qobject_cast<QPushButton*>(store.last().widget)->setText("Добавить поле EDIT");
    ui->horizontalLayout_2->addWidget(qobject_cast<QPushButton*>(store.last().widget));
    connect(store.last().widget, SIGNAL(clicked()), this, SLOT(slotDynamic()));

    temp.id = store.size();
    temp.type = 1;
    store.push_back(temp);
    store.last().widget = new QPushButton(this);
    qobject_cast<QPushButton*>(store.last().widget)->setText("Удалить поле EDIT");
    qobject_cast<QPushButton*>(store.last().widget)->setEnabled(false);
    ui->horizontalLayout_2->addWidget(qobject_cast<QPushButton*>(store.last().widget));
    connect(store.last().widget, SIGNAL(clicked()), this, SLOT(slotDynamic()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotDynamic()
{
    widgets temp;
    for (int cnt = 0; cnt < store.size(); cnt++) {
        if (store[cnt].widget == (QPushButton*) sender()) {
            //qDebug() << sender();
            if (store[cnt].type == 0) {
                if (store[cnt].id == 0) {
                    ui->label->setText("Нажата кнопка добавления");
                    temp.id = store.size();
                    temp.type = 0;
                    store.push_back(temp);
                    store.last().widget = new QPushButton(this);
                    qobject_cast<QPushButton*>(store.last().widget)->setText(QString::number(temp.id - 3) + " кнопка");
                    ui->horizontalLayout->addWidget(qobject_cast<QPushButton*>(store.last().widget));
                    connect(store.last().widget, SIGNAL(clicked()), this, SLOT(slotDynamic()));
                }
                if (store[cnt].id == 1) {
                    ui->label->setText("Нажата кнопка удаления");
                    for (int i = store.size() - 1; i > 3; i-- ) {
                        if (store[i].type == 0) {
                            ui->horizontalLayout->removeWidget(qobject_cast<QPushButton*>(store[i].widget));
                            delete store[i].widget;
                            store.remove(i);
                            break;
                        }
                    }
//                    ui->horizontalLayout->removeWidget(qobject_cast<QPushButton*>(store.last().widget));
//                    delete store.last().widget;
//                    store.removeLast();
                }
                if (store[cnt].id > 3) {
                    ui->label->setText("Нажата кнопка " + QString::number(store[cnt].id - 3));
                }
            }
            if (store[cnt].type == 1) {
                if (store[cnt].id == 2) {
                    ui->label->setText("Нажата кнопка добавления EDIT");
                    temp.id = store.size();
                    temp.type = 1;
                    store.push_back(temp);
                    store.last().widget = new QLineEdit(this);
                    qobject_cast<QLineEdit*>(store.last().widget)->setText(QString::number(temp.id - 3) + " Edit");
                    ui->horizontalLayout_2->addWidget(qobject_cast<QLineEdit*>(store.last().widget));
                }

                if (store[cnt].id == 3) {
                    ui->label->setText("Удаление EDIT");
                    for (int i = store.size() - 1; i > 3; i--) {
                        if (store[i].type == 1) {
                            ui->horizontalLayout_2->removeWidget(qobject_cast<QLineEdit*>(store[i].widget));
                            delete store[i].widget;
                            store.remove(i);
                            break;
                        }
                    }
//                    ui->horizontalLayout_2->removeWidget(qobject_cast<QLineEdit*>(store.last().widget));
//                    delete store.last().widget;
//                    store.removeLast();
                }
            }

        }
    }

    int sumBtn = 0;
    int sumLineEdit = 0;
    for (int count = 0; count < store.size(); count++) {
        if (store[count].type == 0) sumBtn += 1;
        if (store[count].type == 1) sumLineEdit += 1;
    }

    if (sumBtn > 2) qobject_cast<QPushButton*>(store[1].widget)->setEnabled(true);
    else qobject_cast<QPushButton*>(store[1].widget)->setEnabled(false);

    if (sumLineEdit > 2) qobject_cast<QPushButton*>(store[3].widget)->setEnabled(true);
    else qobject_cast<QPushButton*>(store[3].widget)->setEnabled(false);
}
