#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h >
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <vector>
#include <string>
#include "MaterieGUI.h"

using std::vector;
using std::string;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileRepository repo;
    Contract contract;
    MaterieValidator val;
    MaterieService service{ repo, val, contract };
    service.add_default();

    MaterieGUI gui(service);
    gui.show();
    /*

   
    
    
    auto lyBtn = new QHBoxLayout{};


    lyMain->addLayout(stgLy);

    w.show();*/

    return a.exec();
}
