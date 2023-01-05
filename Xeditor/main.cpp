#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStatusBar>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;




    /*QLabel *label = new QLabel("Hello, World!");
       QPushButton *button = new QPushButton("Click me");
       QPushButton *button2 = new QPushButton("Count");

       // Create the layout and add the widgets to it
       QVBoxLayout *layout = new QVBoxLayout;

       layout->addWidget(label);
       layout->addWidget(button);
       layout->addWidget(button2);

       // Set the layout as the central widget of the window
       w.setCentralWidget(new QWidget);
       w.centralWidget()->setLayout(layout);


       int clickCount = 0;
       QObject::connect(button, &QPushButton::clicked, [label]()
       { label->setText("Button was clicked!");});



       QObject::connect(button2, &QPushButton::clicked, [&]() {
              if (++clickCount >= 10) {
                  button2->setEnabled(false);

              w.statusBar()->showMessage(QString("Button was clicked %1 times").arg(clickCount));
       }});*/
    w.show();
    return a.exec();
}
