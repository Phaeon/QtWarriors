#include "game.hpp"

Game::Game() : _ListPionsGame()
{

}

Game::~Game()
{

}

void Game::setListPionGame(const QString &name)
{
  this->_ListPionsGame.push_back(name);
}

void Game::setListPionGameDel(const QString &name)
{
  for(auto i = _ListPionsGame.begin() ; i != _ListPionsGame.end() ; ++i){
       if((*i) == name){
          _ListPionsGame.erase(i);
          return;
       }
  }
}

void Game::ViewRejected()
{
  this->_ListPionsGame.clear();
}

QVector<QString> Game::getListPionsGame() const
{
  return  this->_ListPionsGame;
}

QString Game::getPion(int index) const
{
  return this->_ListPionsGame.at(index);
}
