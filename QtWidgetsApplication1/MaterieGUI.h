#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qmessagebox.h>
#include <qdebug.h>
#include <vector>
#include <string>
using std::vector;
using std::string;

class MaterieGUI: public QWidget {
public:
	MaterieGUI() {
        initGUI();
        loadData();
        initConnect();
        
	}

private:
    QListWidget* lst = new QListWidget;
    QPushButton* btnAdd = new QPushButton{ "&Add" };
    QPushButton* btnExit = new QPushButton{ "&Exit" };
    QLineEdit* txtNume = new QLineEdit;
    QLineEdit* txtProfesor = new QLineEdit;
    QLineEdit* txtOre = new QLineEdit;
    void initConnect() {
        QObject::connect(btnExit, &QPushButton::clicked, [&]() {
            qDebug() << "Exit button apasat!";
            QMessageBox::information(nullptr, "Exit", "exit button");
            close();
            });

        QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
            qDebug() << "Add button apasat!";
            auto nume = txtNume->text();
            auto profesor = txtProfesor->text();
            auto ore = txtOre->text();
            qDebug() << "Nume: " << nume << " Profesor: " << profesor << " Ore: " << ore;
            std::string oreString = ore.toStdString();
            std::string profesorString = profesor.toStdString();
            std::string numeString = nume.toStdString();
            std::string materieString = "("+ numeString + " " + profesorString + " " + oreString + ")";
            lst->addItem(QString::fromStdString(materieString));
            });
    }
    void loadData() {
        vector<string> allMaterii = { "materie1", "materie2", "materie3", "materie4" };

        for (const auto& numeMaterie : allMaterii) {
            lst->addItem(QString::fromStdString(numeMaterie));
        }
    }
	void initGUI() {
        QHBoxLayout* lyMain = new QHBoxLayout{};
        setLayout(lyMain);
        
        lyMain->addWidget(lst);

        auto stgLy = new QVBoxLayout;


        auto formLy = new QFormLayout;
        formLy->addRow("Nume", txtNume);
        formLy->addRow("Profesor", txtProfesor);
        formLy->addRow("Ore", txtOre);
        stgLy->addLayout(formLy);


        auto lyBtn = new QHBoxLayout{};

        lyBtn->addWidget(btnAdd);
        lyBtn->addWidget(new QPushButton{ "&Sterge" });
        lyBtn->addWidget(new QPushButton{ "&Modifica" });
        lyBtn->addWidget(btnExit);
        stgLy->addLayout(lyBtn);

        lyMain->addLayout(stgLy);
	}

};