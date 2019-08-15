#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    QLabel *inputBoxLabel;
    QTextEdit *inputBox;
    QLabel *outputBoxLabel;
    QTextEdit *outputBox;
    QPushButton *genButton;
    QPushButton *clearButton;

public slots:
    void updateBoxes();
};

#endif // MAINWINDOW_H
