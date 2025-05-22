//Elemental Clash: a stratagy game

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

// Struct for attack moves: damage-dealing or status effects (heal/poison)
struct Attack {
    string name;
    int damage;
    string type; // "status" if it's a heal or poison move
};

// Struct for character details
struct Character {
    string name;
    string type;// elemental type: fire, water, etc.
    int hp;
    bool poisoned = false;// status effect
};


// Help Menu Display
void displayHelpMenu() {
    cout << "\n=== GAME INSTRUCTIONS ===\n";
    cout << "1. Choose your character (Fire, Earth, Lightning, Water).\n";
    cout << "2. Each turn you'll be given 3 random move choices.\n";
    cout << "   - Normally, you'll get 3 elemental attacks of your type.\n";
    cout << "   - Occasionally, 1 move will be a status move: Heal or Poison.\n";
    cout << "3. Type Weaknesses:\n";
    cout << "   - Fire is weak to Water (x2) and Lightning (x1)\n";
    cout << "   - Earth is weak to Fire (x2) and Water (x1)\n";
    cout << "   - Lightning is weak to Earth (x2) and Fire (x1)\n";
    cout << "   - Water is weak to Lightning (x2) and Earth (x1)\n";
    cout << "4. Heal: Recovers 20 HP or removes poison if poisoned.\n";
    cout << "5. Poison: Makes the opponent lose 5 HP at the start of each turn.\n";
    cout << "6. Battle continues until one player's HP drops to 0.\n";
    cout << "==========================\n";
}


// Calculate attack damage based on weaknesses
int calculateDamage(const Attack& atk, const Character& defender, const map<string, vector<pair<string, int>>>& weaknesses) {
    if (atk.type == "heal" || atk.type == "poison") return 0;

    int dmg = atk.damage;
    if (weaknesses.count(defender.type)) {
        for (auto& w : weaknesses.at(defender.type)) {
            if (w.first == atk.type) {
                dmg *= w.second;
                if (w.second > 1) cout << "It's super effective!\n";
            }
        }
    }
    return dmg;
}

// Apply poison status to a character
void applyStatus(Character& target, const string& status) {
    if (status == "poison") {
        if (!target.poisoned) {
            target.poisoned = true;
            cout << target.name << " is now poisoned!\n";
        } else {
            cout << target.name << " is already poisoned.\n";
        }
    }
}

// Heal logic - recover HP or cure poison
void applyHeal(Character& target) {
    if (target.poisoned) {
        target.poisoned = false;
        cout << target.name << " cured the poison!\n";
    } else {
        target.hp += 20;
        if (target.hp > 100) target.hp = 100;
        cout << target.name << " healed 20 HP!\n";
    }
}

// Perform attack logic
void performAttack(Character& attacker, Character& defender, const Attack& atk,
                   const map<string, vector<pair<string, int>>>& weaknesses) {
    if (atk.type == "heal") {
        applyHeal(attacker);
    } else if (atk.type == "poison") {
        applyStatus(defender, "poison");
    } else {
        int damage = calculateDamage(atk, defender, weaknesses);
        defender.hp -= damage;
        cout << attacker.name << " used " << atk.name << " and dealt " << damage << " damage.\n";
    }
    cout << endl;
}

// Print current status of both players
void printStatus(const Character& p1, const Character& p2) {
    cout << p1.name << " HP: " << p1.hp << (p1.poisoned ? " [Poisoned]" : "") << " | ";
    cout << p2.name << " HP: " << p2.hp << (p2.poisoned ? " [Poisoned]" : "") << "\n\n";
}

// Character selection menu
Character chooseCharacter(const vector<Character>& characters) {
    cout << "Choose your character:\n";
    for (int i = 0; i < characters.size(); ++i) {
        cout << i + 1 << ". " << characters[i].name << " (" << characters[i].type << ")\n";
    }
    int choice;
    cin >> choice;
    return characters[choice - 1];
}

// Generate 3 random moves (sometimes includes a status move)
vector<Attack> getMoveChoices(const string& element, const vector<Attack>& allMoves) {
    vector<Attack> elementMoves, finalChoices;
    for (const auto& atk : allMoves) {
        if (atk.type == element) {
            elementMoves.push_back(atk);
        }
    }

    // Shuffle elemental moves
    random_device rd;
    mt19937 g(rd());
    shuffle(elementMoves.begin(), elementMoves.end(), g);

    // Pick 3 base attacks
    for (int i = 0; i < 3 && i < elementMoves.size(); ++i) {
        finalChoices.push_back(elementMoves[i]);
    }

    // With a 1-in-3 chance, replace one move with a status move
    if (rand() % 3 == 0) {
        Attack statusMove = (rand() % 2 == 0) ?
            Attack{"Poison Cloud", 0, "poison"} : Attack{"Healing Light", 0, "heal"};

        int replaceIndex = rand() % 3;
        finalChoices[replaceIndex] = statusMove;
    }

    return finalChoices;
}

// Main game loop
int main() {
    srand(time(0));
    displayHelpMenu();// Show instructions at the beginning

    // Elemental weaknesses map
    map<string, vector<pair<string, int>>> weaknesses = {
        {"fire", {{"water", 2}, {"lightning", 1}}},
        {"earth", {{"fire", 2}, {"water", 1}}},
        {"lightning", {{"earth", 2}, {"fire", 1}}},
        {"water", {{"lightning", 2}, {"earth", 1}}}
    };

    // Character options
    vector<Character> characterList = {
        {"Pyra the Flame", "fire", 100},
        {"Terros the Earthshaker", "earth", 100},
        {"Voltra the Spark", "lightning", 100},
        {"Aquon the Wave", "water", 100}
    };

    // All attack moves
    vector<Attack> movePool = {
        {"Flame Burst", 20, "fire"},
        {"Inferno Kick", 25, "fire"},
        {"Blazing Spin", 30, "fire"},
        {"Rock Slam", 20, "earth"},
        {"Quake Smash", 25, "earth"},
        {"Mud Trap", 30, "earth"},
        {"Spark Jab", 20, "lightning"},
        {"Thunder Fang", 25, "lightning"},
        {"Volt Crash", 30, "lightning"},
        {"Water Jet", 20, "water"},
        {"Aqua Blade", 25, "water"},
        {"Tidal Crush", 30, "water"}
    };


    // Player character selection
    cout << "Player 1, ";
    Character player1 = chooseCharacter(characterList);
    cout << "\nPlayer 2, ";
    Character player2 = chooseCharacter(characterList);
    cout << "\n";


    // Decide turn randomly
    cout << "Coin Toss to Decide Who Starts..."<<endl;
    bool player1Turn = rand() % 2 == 0;
    cout << (player1Turn ? "Player 1 starts first!\n\n" : "Player 2 starts first!\n\n");

    // Game loop starts
    while (player1.hp > 0 && player2.hp > 0) {
        printStatus(player1, player2);

        Character& attacker = player1Turn ? player1 : player2;
        Character& defender = player1Turn ? player2 : player1;

        cout << (player1Turn ? "Player 1's" : "Player 2's") << " Turn (" << attacker.name << "):\n";

        vector<Attack> choices = getMoveChoices(attacker.type, movePool);// Filter moves to only match character's type

        for (int i = 0; i < choices.size(); ++i) {
            string info = (choices[i].type == "heal" || choices[i].type == "poison") ?
                choices[i].name + " (Status Move)" :
                choices[i].name + " (" + choices[i].type + ", " + to_string(choices[i].damage) + " dmg)";
            cout << i + 1 << ". " << info << "\n";
        }

        int moveChoice;
        cin >> moveChoice;

        performAttack(attacker, defender, choices[moveChoice - 1], weaknesses);

        // Poison damage after move
        if (player1Turn && player2.poisoned) {
            player2.hp -= 5;
            cout << player2.name << " suffers 5 poison damage!\n";
        } else if (!player1Turn && player1.poisoned) {
            player1.hp -= 5;
            cout << player1.name << " suffers 5 poison damage!\n";
        }

        // Switch turns
        player1Turn = !player1Turn;
        cout << "\n------------------------\n";
    }

    // End of game result
    if (player1.hp > 0)
        cout << "\nPlayer 1 (" << player1.name << ") wins!\n";
    else
        cout << "\nPlayer 2 (" << player2.name << ") wins!\n";

    return 0;
}