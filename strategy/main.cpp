//
// Created by Gustavo on 2/22/22.
//

#include <iostream>
#include <memory>
#include <vector>

// Weapon 'behaviour' base class
class Weapon {
public:
    virtual void use_weapon() const = 0;

    virtual ~Weapon() = default;
};

// Default weapon: represents no weapon being assigned to a char
class DefaultWeapon : public Weapon {
public:
    void use_weapon() const override {
        std::cout << "No weapon to fight with :(\n";
    };

    ~DefaultWeapon() override = default;
};

// Weapon classes: Sword, Axe, Knife and PaperClip (why not?)
class Sword : public Weapon {
public:
    void use_weapon() const override {
        std::cout << "Swings with sword!\n";
    };

    ~Sword() override = default;
};

class Axe : public Weapon {
public:
    void use_weapon() const override {
        std::cout << "Chops with axe!\n";
    };

    ~Axe() override = default;
};

class Knife : public Weapon {
public:
    void use_weapon() const override {
        std::cout << "Stabs with knife!\n";
    };

    ~Knife() override = default;
};

class PaperClip : public Weapon {
public:
    void use_weapon() const override {
        std::cout << "Sorry, I'm just a paper clip!\n";
    };

    ~PaperClip() override = default;
};

// Character base class
class Character {
private:
    std::unique_ptr<Weapon> weapon{new DefaultWeapon()};
public:
    virtual void display() const = 0;

    void set_weapon(std::unique_ptr<Weapon> &new_weapon) {
        weapon = std::move(new_weapon);
    }

    void fight() const {
        weapon->use_weapon();
    }

    virtual ~Character() = default;
};

// Different types of characters: Queen, King, Knight and Troll
class Queen : public Character {
public:
    void display() const override {
        std::cout << "I'm a Queen!\n";
    }

    ~Queen() override = default;
};

class King : public Character {
public:
    void display() const override {
        std::cout << "I'm a King!\n";
    }

    ~King() override = default;
};

class Knight : public Character {
public:
    void display() const override {
        std::cout << "I'm a Knight!\n";
    }

    ~Knight() override = default;
};

class Troll : public Character {
public:
    void display() const override {
        std::cout << "LMAO, I'm a Troll!\n";
    }

    ~Troll() override = default;
};

int main() {

    // Create weapon instances
    std::unique_ptr<Weapon> sword = std::make_unique<Sword>();
    std::unique_ptr<Weapon> axe = std::make_unique<Axe>();
    std::unique_ptr<Weapon> knife = std::make_unique<Knife>();
    std::unique_ptr<Weapon> paperclip = std::make_unique<PaperClip>();

    // Create character instances
    std::vector<std::unique_ptr<Character>> char_vec{};

    std::unique_ptr<Character> queen(new Queen());
    queen->set_weapon(sword);
    char_vec.push_back(std::move(queen));

    std::unique_ptr<Character> king(new King());
    king->set_weapon(axe);
    char_vec.push_back(std::move(king));

    std::unique_ptr<Character> knight(new Knight());
    //knight->set_weapon(knife);
    char_vec.push_back(std::move(knight));

    std::unique_ptr<Character> troll(new Troll());
    troll->set_weapon(paperclip);
    char_vec.push_back(std::move(troll));

    // Call character actions
    for (const auto &character: char_vec) {
        character->display();
        character->fight();
    }

    return 0;
}
