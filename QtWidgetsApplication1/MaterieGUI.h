#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qmessagebox.h>
#include <qdebug.h>
#include <vector>
#include <string>
#include <Service.h>
using std::vector;
using std::string;

class SmallGUI : public QWidget {

public:
    SmallGUI() {
        initGUI();
    }
    
private:
    void initGUI() {
        QLineEdit* nume = new QLineEdit;
        QLineEdit* profesor = new QLineEdit;
        QLineEdit* ore = new QLineEdit;
        
        auto formLy = new QFormLayout;
        setLayout(formLy);
        formLy->addRow("Nume", nume);
        formLy->addRow("Profesor", profesor);
        formLy->addRow("Ore", ore);
        
       
    }
};

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
    QPushButton* btnDelete = new QPushButton{ "&Delete" };
    QPushButton* btnExit = new QPushButton{ "&Exit" };
    QPushButton* btnModify = new QPushButton{ "&Modify" };
    QPushButton* btnSort = new QPushButton{ "&Sort" };
    QPushButton* btnReset = new QPushButton{ "&Reset" };
    QLineEdit* txtNume = new QLineEdit;
    QLineEdit* txtProfesor = new QLineEdit;
    QLineEdit* txtOre = new QLineEdit;
    QLineEdit* txtNume2 = new QLineEdit;
    QLineEdit* txtProfesor2 = new QLineEdit;
    QLineEdit* txtOre2 = new QLineEdit;

    ///add default



    void initConnect() {

        ///default



        QObject::connect(btnExit, &QPushButton::clicked, [&]() {
            qDebug() << "Exit button apasat!";
            QMessageBox::information(nullptr, "Exit", "exit button");

            close();
            });

        QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
            auto nume = txtNume->text();
            auto profesor = txtProfesor->text();
            auto ore = txtOre->text();
            qDebug() << "Nume: " << nume << " Profesor: " << profesor << " Ore: " << ore;
            std::string oreString = ore.toStdString();
            std::string profesorString = profesor.toStdString();
            std::string numeString = nume.toStdString();
            std::string materieString = "("+ numeString + " " + profesorString + " " + oreString + ")";
            int oreInt = std::stoi(oreString);
            try {
                service.addMaterieService(numeString, profesorString, oreInt);

                lst->addItem(QString::fromStdString(materieString));
            }
            catch (ValidationException& e) {
                QMessageBox::warning(this, "Warning", QString::fromStdString(e.getErrorMessages()));
            }
            });

        QObject::connect(btnDelete, &QPushButton::clicked, [&]() {
            auto nume = txtNume->text();
            auto profesor = txtProfesor->text();
            std::string profesorString = profesor.toStdString();
            std::string numeString = nume.toStdString();

            try {
                int poz = service.get_materie_position(numeString, profesorString);
                service.delete_materie(numeString, profesorString);
                QListWidgetItem* item = lst->takeItem(poz);
                delete item;
                
            }
            catch (std::invalid_argument& e) {
                QMessageBox::information(nullptr, "Eroare!", "Materia nu exista!");
            };


            });

        QObject::connect(btnSort, &QPushButton::clicked, [&]() {
            lst->clear();
            vector<Materie> lista_sortata = service.sort_func(1);
            for (auto& it : lista_sortata) {
                string nume = it.getNume();
                string profesor = it.getProfesor();
                int ore = it.getOre();
                string oreSt = std::to_string(ore);
                string stringAfisare = "(" + nume + " " + profesor + " " + oreSt + ")";
                lst->addItem(QString::fromStdString(stringAfisare));
            }
 
            });

        QObject::connect(btnReset, &QPushButton::clicked, [&]() {
            lst->clear();
            add_toate_materiile();
            });

        QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
            qDebug() << "Selectie schimbata!";
            auto sel = lst->selectedItems();
            if (sel.isEmpty()) {
                txtNume->setText("");
                txtProfesor->setText("");
                txtOre->setText("");
            }
            else {
                auto selItem = sel.at(0);
                auto nume = selItem->text();
                auto profesor = selItem->data(Qt::UserRole).toString();
                int materie_position = service.get_materie_position(nume.toStdString(), profesor.toStdString());
                vector<Materie> materii = service.primeste_toate_materiile();
                int ore = materii[materie_position].getOre();
                string oreSt = std::to_string(ore);
                txtNume->setText(nume);
                txtProfesor->setText(profesor);
                txtOre->setText(QString::fromStdString(oreSt));
                
                


            }
            }
        );
        QObject::connect(btnModify, &QPushButton::clicked, [&]() {
            auto gui = new SmallGUI{};
            gui->show();

            });
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
        lyBtn->addWidget(btnDelete);
        lyBtn->addWidget(btnModify);
        lyBtn->addWidget(btnExit);
        lyBtn->addWidget(btnSort);
        lyBtn->addWidget(btnReset);
        stgLy->addLayout(lyBtn);

        lyMain->addLayout(stgLy);
	}

    void add_toate_materiile () {
        vector<Materie> materii = service.primeste_toate_materiile();
        for (auto& it : materii) {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(it.getNume()));
            item->setData(Qt::UserRole, QString::fromStdString(it.getProfesor()));
            lst->addItem(item);
        }
    }

};