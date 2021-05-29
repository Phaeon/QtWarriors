#include "Controllers/controller.hpp"
#include <QApplication>
#include "library.hpp"
#include <cstdlib>
#include <ctime>
#include <QTranslator>

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    srand(time_t(nullptr));

    glutInit(&argc, argv);

    QApplication a(argc, argv);

    QTranslator translator;
    if(translator.load(QLocale::system(), "Annotations", "_", a.applicationDirPath(), ".qm")){
        a.installTranslator(&translator);
    }

    QCoreApplication::setApplicationName("QtWarriors");
    Controller c;

    return a.exec();
}
