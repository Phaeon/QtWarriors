#ifndef VIEW_HPP
#define VIEW_HPP

#include <QWidget>
#include <QDesktopWidget>
#include <QApplication>
#include <QScreen>
#include <memory>

//#include "Controllers/controller.hpp"

class Controller;
/**
 * @brief The View class
 * Classe mère des différentes vues
 * Chaque vue a accès au contrôleur
 */
class View
{
public:
  View(Controller *controller);
  ~View();

protected:
  Controller * _controller;

};

#endif // VIEW_HPP
