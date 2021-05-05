#include "Controllers/controller.hpp"
#include <QApplication>
#include "library.hpp"

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  QApplication a(argc, argv);
  Controller c;

  return a.exec();
}
