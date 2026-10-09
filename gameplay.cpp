#include <iostream>
#include "world.hpp"
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
// #include <bits/stdc++.h>
#include <vector>
#include <cmath>

bool playinggame = true;

Player player;
Enemy enemy;

Weapon longsword("Longsword", 2, 'l');
Weapon club("Club", 3, 'c');
Weapon axe("Axe", 6, 'a');
Weapon staff("Staff", 4, 's');
Weapon dagger("Dagger", 4, 's');
Weapon warhammer("Warhammer", 8, 'w');
Weapon ultrasword("UltraSword", 15, 'u');

//   combat
void combat(){
  bool wea = false;
  bool mag = false;
  enemy.chooseenemy(player.level);;
  std::cout << "a " << enemy.name << " appears!\n";
  bool choseweap = false;
  while(enemy.health >= 1 && player.health >= 1){
    std::cout << "  Health: " << player.health << "\n  Stamina: " << player.stam << "\n  Mana: " << player.mana << "\n  Exp: " << player.xp << " / " << ceil((pow(((float)player.level * 2.5), 2))/2) << "\n  Level: " << player.level <<  "\n  ------------------ \n  " << enemy.name << " Health: " << enemy.health << "\n";
    std::cout << "'q' = inventory, 'c' = spells, 'e' = attack\n";
    char action;
    int damagedealt;
    std::cin >> action;
    switch(action){
      case 'q':{
        switch(player.inv()){
          case 'l':{
            std::cout << "selected longsword\n";
            damagedealt = longsword.damage();
            choseweap = true;
            wea = true;
            break;
          }
          case 'c':{
            damagedealt = club.damage();
            std::cout << "selected club\n";
            choseweap = true;
            wea = true;
            break;
          }
          case 'a':{
            damagedealt = axe.damage();
            std::cout << "selected axe\n";
            choseweap = true;
            wea = true;
            break;
          }
          case 's':{
            damagedealt = staff.damage();
            std::cout << "selected staff\n";
            choseweap = true;
            wea = true;
            break;
          }
          case 'd':{
            damagedealt = dagger.damage();
            std::cout << "selected dagger\n";
            choseweap = true;
            wea = true;
            break;
          }
          case 'w':{
            damagedealt = warhammer.damage();
            std::cout << "selected warhammer\n";
            choseweap = true;
            wea = true;
            break;
          }
          case 'u':{
            damagedealt = ultrasword.damage();
            std::cout << "selected ultrasword\n";
            choseweap = true;
            wea = true;
            break;
          }
          case 'h':{
            player.health += 20;
            if (player.health > 100){
              player.health = 100;
            }
            std::cout << "consumed health potion, gained 20 hp.";
            player.healthpotions -= 1;
            std::cout << " removed 1 health potion from inventory.";
            if (player.healthpotions == 0){
              int potionfind = 0;
              for (int i = 0; i < player.inventory.size(); i++){
                if (player.inventory[i] == "healthpotion"){
                  potionfind = i;
                }
              }
              player.inventory.erase(player.inventory.begin() + potionfind);
              std::cout << " you are out of health potions.";
            }
            std::cout << "\n";
            break;
          }
          case 'm':{
            player.mana += 30;
            std::cout << "consumed mana potion, gained 30 mana.";
            player.manapotions -= 1;
            std::cout << " removed 1 mana potion from inventory.";
            if (player.manapotions == 0){
              int potionfind = 0;
              for (int i = 0; i < player.inventory.size(); i++){
                if (player.inventory[i] == "manapotion"){
                  potionfind = i;
                }
              }
              player.inventory.erase(player.inventory.begin() + potionfind);
              std::cout << " you are out of mana potions.";
            }
            break;
          }
          case 'v':{
            player.stam += 30;
            std::cout << "consumed vigor potion, gained 30 stamina.";
            player.vigorpotions -= 1;
            std::cout << " removed 1 vigor potion from inventory.";
            if (player.vigorpotions == 0){
              int potionfind = 0;
              for (int i = 0; i < player.inventory.size(); i++){
                if (player.inventory[i] == "vigorpotion"){
                  potionfind = i;
                }
              }
              player.inventory.erase(player.inventory.begin() + potionfind);
              std::cout << " you are out of vigor potions.";
            }
          }
          default:{
            std::cout << "invalid\n";
          }
        }
        continue;
      }
      case 'c':{
        if (player.spells()){
          mag = true;
        }
        break;
      }
      case 'e':{
        if ((rand() % player.stam) < 10){
          std::cout << "miss\n";
        }
        else{
          if (choseweap){
            enemy.health -= damagedealt;
            std::cout << "dealt " << damagedealt << " damage to " << enemy.name << "!\n";
          }
          else{
            std::cout << "weapon not selected... attacked with fists! dealt 1 damage to " << enemy.name << "!\n";
            enemy.health -= 1;
            player.stam -= 10;
          }
        }
        break;
      }
      default:{
        break;
      }
    }
    if(enemy.health >=1){
      int enemydamage = enemy.damage();
      if (enemydamage == 0){
        std::cout << "The " << enemy.name << " missed!";
      }
      else{
        player.health -= enemydamage;
        std::cout << "the " << enemy.name << " hit you with their " << enemy.weapname << " for " << enemydamage << " damage.";
        if (enemy.type == 'd'){
          enemy.health += (enemydamage / 4);
          std::cout << " and stole some health";
        }
      }
      std::cout << "\n";
      
    }
    if(player.health <= 0){
      std::cout << "\nYou Died.\n";
      playinggame = false;
      break;
    }
  }
  if (enemy.health <=0){
    player.xpup(wea, mag);
  }
};

//   movement
void movement(char direction) {
  switch(direction){
    case 'w':{
      player.move(-1, 0, direction);
      break;
    }
    case 's':{
      player.move(1, 0, direction);
      break;
    }
    case 'a':{
      player.move(0, -1, direction);
      break;
    }
    case 'd':{
      player.move(0, 1, direction);
      break;
    }
    case 'n':{
      achievements();
      break;
    }
    case 'm':{
      playinggame = false;
      break;
    }
    case 'p':{
      player.save();
      std::cout << "\nsaved\n\n";
      break;
    }
    case 'o':{
      std::cout << "  Health: " << player.health << "\n  Stamina: " << player.stam << "\n  Mana: " << player.mana << "\n  Exp: " << player.xp << "/" << ceil((pow(((float)player.level * 2.5), 2))/2) << "\n  Level: " << player.level << "\n  Magic Skill: " << player.magicskill << "\n  Magic XP: " << player.magicxp << "/" << ((float)player.magicskill/2) * 10.0 << "\n  Shield HP: " << player.shieldhealth << "\n  Strength: " << player.strength << "\n  Strength XP: " << player.strengthxp << "/" << ((float)player.strength/2) * 10.0 << "\n  Gold: " << player.gold << "\n";
      break;
    }
    case 'i':{
      std::string dropping;
      for (int i = 0; i < player.inventory.size(); i++){
        std::cout << "\n " << i << ": " << player.inventory[i] << ", ";
      }
      std::cout << "\n\nDrop item? y/n\n";
      std::cin >> dropping;
      if (dropping == "y"){
        switch(player.inv()){
          case 'l':{
            int invfind = 0;
            for (int i = 0; i < player.inventory.size(); i++){
              if (player.inventory[i] == "longsword"){
                invfind = i;
                }
              }
            player.inventory.erase(player.inventory.begin() + invfind);
            std::cout << "longsword removed\n";
            break;
          }
          case 'c':{
            int invfind = 0;
            for (int i = 0; i < player.inventory.size(); i++){
              if (player.inventory[i] == "club"){
                invfind = i;
                }
              }
            player.inventory.erase(player.inventory.begin() + invfind);
            std::cout << "club removed\n";
            break;
          }
          case 'a':{
            int invfind = 0;
            for (int i = 0; i < player.inventory.size(); i++){
              if (player.inventory[i] == "axe"){
                invfind = i;
                }
              }
            player.inventory.erase(player.inventory.begin() + invfind);
            std::cout << "axe removed\n";
            break;
          }
          case 's':{
            int invfind = 0;
            for (int i = 0; i < player.inventory.size(); i++){
              if (player.inventory[i] == "staff"){
                invfind = i;
                }
              }
            player.inventory.erase(player.inventory.begin() + invfind);
            std::cout << "staff removed\n";
            break;
          }
          case 'd':{
            int invfind = 0;
            for (int i = 0; i < player.inventory.size(); i++){
              if (player.inventory[i] == "dagger"){
                invfind = i;
                }
              }
            player.inventory.erase(player.inventory.begin() + invfind);
            std::cout << "dagger removed\n";
            break;
          }
          case 'w':{
            int invfind = 0;
            for (int i = 0; i < player.inventory.size(); i++){
              if (player.inventory[i] == "warhammer"){
                invfind = i;
                }
              }
            player.inventory.erase(player.inventory.begin() + invfind);
            std::cout << "warhammer removed\n";
            break;
          }
          case 'h':{
            int invfind = 0;
            for (int i = 0; i < player.inventory.size(); i++){
              if (player.inventory[i] == "healthpotion"){
                invfind = i;
                }
              }
            player.inventory.erase(player.inventory.begin() + invfind);
            std::cout << "health potions removed\n";
            break;
          }
          case 'm':{
            int invfind = 0;
            for (int i = 0; i < player.inventory.size(); i++){
              if (player.inventory[i] == "manapotion"){
                invfind = i;
                }
              }
            player.inventory.erase(player.inventory.begin() + invfind);
            std::cout << "mana potions removed\n";
            break;
          }
          case 'v':{
            int invfind = 0;
            for (int i = 0; i < player.inventory.size(); i++){
              if (player.inventory[i] == "vigorpotion"){
                invfind = i;
                }
              }
            player.inventory.erase(player.inventory.begin() + invfind);
            std::cout << "vigor potions removed\n";
            break;
          }
          default:{
            std::cout << "invalid\n";
            break;
          }

        }
      }
      else{
        return;
      }
      break;
    }
    case 'c':{
      player.passivecast();
      break;
    }
    default:
      {
        std::cout << "bruhinvalid\n";
        break;
      }
  }
  return;
}

void gameplay(bool loadgame) {
  if (loadgame == true){
    player.load();
  }
  else{
    player.newgame();
  }
  //   game loop
  playinggame = true;
    while (playinggame){  
      map();
      char direction = -1;
      std::cout << "WASD = move, 'c' = cast spell, 'i' = inventory, 'o' = stats, 'p' = save, 'n' = achievements, 'm' = menu\n";
      std::cin >> direction;
      movement(direction);
    }
  return;
}