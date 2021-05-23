#include "Controllers/controller.hpp"
#include <QApplication>
#include "library.hpp"

#include <cstdlib>
#include <ctime>

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

  QCoreApplication::setApplicationName("QtWarriors");
  Controller c;

  return a.exec();
}
