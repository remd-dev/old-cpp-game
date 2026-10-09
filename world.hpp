#pragma once
#include <string>
#include <vector>

void achievements();

void bossfight();

void worldget();

void map();

void test(); 

void combat();

void spellbookload(std::string spells);

void gameworldinitialize();

int selectenemy(int A, int B, int PA, int PB);

class Player {
  public:
    int world_x;
    int world_y;
    int x;
    int y;
    int health;
    int level;
    float xp;
    int stam;
    int mana;
    int magicskill;
    float magicxp;
    int strength;
    float strengthxp;
    bool shield;
    int shieldhealth;
    int healthpotions;
    int manapotions;
    int vigorpotions;
    int gold;
    std::vector<std::string> inventory;
    void move(int xa, int ya, char direction);
    void load();
    void xpup(bool wea, bool mag);
    void shop();
    char inv();
    bool spells();
    void save();
    void newgame();
    void passivecast();
};

extern Player player;

class Mob {
  public:
    std::string name;
    int health;
    int strength;
    char weap;
    int chance;
    Mob(std::string newname, int newhealth, int newstrength, char newweap, int newchance);
};

class Weapon {
  public:
    std::string name;
    int dmg;
    char type;
    Weapon(std::string newname, int newdmg, char newtype);
    int damage();
};

class Enemy {
  public:
    char type;
    std::string name;
    int health;
    int totalhealth;
    int strength;
    char weap;
    std::string weapname;
    void chooseenemy(int level);
    int damage();
};

class Spells {
  public:
    std::string name;
    int cost;
    char effect;
    int dmg;
    int id;
    Spells(std::string newname, int newcost, char neweffect, int newdmg, int newid);
    void cast();
};

extern Enemy enemy;