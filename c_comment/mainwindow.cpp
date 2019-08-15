#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>
#include <sstream>
#include <string>

#include <QString>
#include <QTextOption>
#include <QFont>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    setMinimumSize(QSize(700, 300));
    setWindowTitle("C Comment Generator");
    inputBoxLabel = new QLabel("Original comment:");
    inputBox = new QTextEdit;
    inputBox->setPlaceholderText("Type unformatted comment here...");
    inputBox->setTabChangesFocus(true);
    outputBoxLabel = new QLabel("Formatted comment:");
    outputBox = new QTextEdit;
    outputBox->setTabChangesFocus(true);
    outputBox->setCurrentFont(QFont("Courier", 10));
    genButton = new QPushButton("&Generate comment");
    clearButton = new QPushButton("&Clear");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(inputBoxLabel);
    layout->addWidget(inputBox);
    layout->addWidget(outputBoxLabel);
    layout->addWidget(outputBox);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(genButton);
    buttonLayout->addWidget(clearButton);
    layout->addLayout(buttonLayout);
    setLayout(layout);
    connect(genButton, SIGNAL(clicked()), this,
            SLOT(updateBoxes()));
    connect(clearButton, SIGNAL(clicked()), inputBox,
            SLOT(clear()));
    connect(clearButton, SIGNAL(clicked()), outputBox,
            SLOT(clear()));
}

void MainWindow::updateBoxes()
{
    std::istringstream inputStream {inputBox->toPlainText().toStdString()};
    std::string currentLine;
    std::string currentWord;
    std::vector<std::string> outLines;
    while (inputStream >> currentWord) {
        if (currentLine.length() == 0)
            currentLine = currentWord;
        else {
            if (currentLine.length() + currentWord.length() + 1 < 73)
                currentLine += " " + currentWord;
            else {
                outLines.push_back(currentLine);
                currentLine = currentWord;
            }
        }
    }
    if (currentLine.length() != 0)
        outLines.push_back(currentLine);
    std::string outputText;
    std::string lineBeginning {"/* "};
    std::string lineEnding {" */\n"};
    std::string border;
    border += "/";
    for (int i = 0; i < 77; ++i)
        border += "*";
    border += "/";
    outputText += border;
    outputText += "\n";
    for (auto line: outLines) {
        std::string initialSegment = lineBeginning + line;
        while (initialSegment.length() < 76)
            initialSegment += " ";
        outputText += initialSegment;
        outputText += lineEnding;
    }
    outputText += border;
    outputBox->setWordWrapMode(QTextOption::NoWrap);
    outputBox->setPlainText(outputText.c_str());
}
