#include <iostream>
#include <fstream>
#include "world.hpp"

void play() {
  void gameplay(bool loadgame);
  bool loadgame;
  char newgame = -1;
  std::cout << "'n' for New Game, 'l' for Load Save\n";
  std::cin >> newgame;
  switch (newgame){
    case 'n':
    {
      loadgame = false;
      gameworldinitialize();
      gameplay(loadgame);
      break;
    }
    case 'l':
    {
      loadgame = true;
      gameworldinitialize();
      gameplay(loadgame);
      break;
    }
  }
}

void menu() {
    char menuoption = -1;
    while (menuoption != 'e'){
    std::cout << "\n\n------------------------\n\nEnter 'p' to play.\nEnter 'h' for information and help.\nEnter 'e' to exit.\n";
    std::cin >> menuoption;
      switch(menuoption){
        case 'h':
          void help();
          help();
          break;
        case 'p':
          play();
          break;
        case 'e':
          std::cout << "exiting\n";
          break;
        default:
          std::cout << "invalid\n";
          break;
        };
    }
};

int main()
{
    menu();
    return 0;
}