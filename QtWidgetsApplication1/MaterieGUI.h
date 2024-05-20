#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qmessagebox.h>
#include <qdebug.h>
#include <vector>
#include <string>
#include <Service.h>
using std::vector;
using std::string;

class MaterieGUI: public QWidget {
public:
    MaterieGUI(MaterieService& service) : service{ service } {
        initGUI();
        add_toate_materiile();
        initConnect();
        
	}

private:
    MaterieService& service;
    QListWidget* lst = new QListWidget;
    QPushButton* btnAdd = new QPushButton{ "&Add" };
    QPushButton* btnExit = new QPushButton{ "&Exit" };
    QLineEdit* txtNume = new QLineEdit;
    QLineEdit* txtProfesor = new QLineEdit;
    QLineEdit* txtOre = new QLineEdit;

    ///add default



    void initConnect() {

        ///default



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
            try {
                service.addMaterieService(numeString, profesorString, std::stoi(oreString));

                lst->addItem(QString::fromStdString(materieString));
            }
            catch (ValidationException& e) {
                QMessageBox::information(nullptr, "Eroare!", "Valori invalide!");
            }
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

    void add_toate_materiile () {
        vector<Materie> materii = service.primeste_toate_materiile();
        for (auto& it : materii) {
            string nume = it.getNume();
            string profesor = it.getProfesor();
            int ore = it.getOre();
            string oreSt = std::to_string(ore);
            string materie_string = "(" + nume + " " + profesor + " " + oreSt + ")";
            lst->addItem(QString::fromStdString(materie_string));
        }
    }

};