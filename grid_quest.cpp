#include <iostream>
#include <chrono>
#include <thread>

int random(int from, int to){
    int delta = abs(to - from);
    return (rand() % (delta + 1)) + from;
}


void sleep(int seconds) {
    std::time_t start = std::time(nullptr);
    std::time_t end = start + seconds;

    while (std::time(nullptr) < end) {}
}

class board_and_player {

protected:
char **b = nullptr;
unsigned int size = 0;
unsigned int round_n = 0;

unsigned int x = 0;
unsigned int y = 0;



public:
void generate(unsigned int size) {

    this->size = size;

    b = new char*[size];

    //array init
    for(int y = 0; y < size; y++){
        b[y] = new char[size];
    }

    for(int y = 0; y < size; y++){
        for(int x = 0; x < size; x++){
            b[y][x] = ' ';
        }
    }

    //obstacles
    for(int i = 0; i < random(3, size + 3); i++) {
        b[random(0, size-1)][random(0, size-1)] = 'G';
    }

    //win condition
    b[random(0, size-1)][random(0, size-1)] = 'W';


}

void generate() {
    generate(random(5,7));
}

void display() {
    std::cout << "*";
    for(int i = 0; i < size * 2 + 1; i++){
        std::cout << "-";
    }
    std::cout << "*\n";
    for(int y = 0; y < size;y++){
        std::cout << "|";
        for(int x = 0; x < size;x++){
            if(x == this->x && y == this->y) {
                std::cout << " p";
            } else {
                std::cout << " " << b[y][x];
            }
        }
        std::cout << " |\n";
    }

    std::cout << "*";
    for(int i = 0; i < size * 2 + 1; i++){
        std::cout << "-";
    }
    std::cout << "*\n";


}

bool obstacle(unsigned int x, unsigned int y) {
    if(b[y][x] == 'G') {
        return true;
    }
    return false;
}

bool win(unsigned int x, unsigned int y) {
    if(b[y][x] == 'W') {
        return true;
    }
    return false;
}

void spawn() {
    bool flag = false;
    while(!flag) {
        x = random(0, size - 1);
        y = random(0, size - 1);

        if(!obstacle(x,y)) {
            flag = true;
        }
    }
}

void move() {

    std::string in;

    while (true) {
        std::cout << "Type in to move (W/A/S/D) or any combination:\n";
        std::cin >> in;

        if(in.empty()) {
            std::cout<< "Invalid input, please try again!\n";
        } else {
            char letter1 = in.at(0);
            char letter2 = ' ';
            if(in.length() >= 2) {
                letter2 = in.at(1);
            }

            unsigned int oldx = x;
            unsigned int oldy = y;

            bool fail1 = false;
            bool fail2 = false;

            switch(toupper(letter1)) {
                case 'W':
                    y--;
                break;
                case 'A':
                    x--;
                break;
                case 'S':
                    y++;
                break;
                case 'D':
                    x++;
                break;

                default:
                    fail1 = true;
                break;
            }

            switch(toupper(letter2)) {
                case 'W':
                    y--;
                break;
                case 'A':
                    x--;
                break;
                case 'S':
                    y++;
                break;
                case 'D':
                    x++;
                break;

                default:
                    fail2 = true;
                break;
            }

            if(fail1 && fail2) {
                std::cout << "Invalid input, please try again!\n";
                continue;
            }

            if(x < 0 || y < 0 || x >= size || y >= size) {
                std::cout << "You can't exit the board! Try again!\n";
                x = oldx;
                y = oldy;
            } else if(obstacle(x,y)) {
                std::cout << "There's an obstacle there! Try again!\n";
                x = oldx;
                y = oldy;
            } else if(win(x,y)) {
                std::cout << "You got to the end, next maze!!\n";
                sleep(1);
                generate();
                spawn();
                round_n++;
                break;
            } else {
                break;
            }
        }
    }
}

void cycle() {
    display();
    std::cout << "\n\n";
    move();
    std::cout << "\n\n";
}

unsigned int round() {
    return round_n;
}


};

int main() {
    srand(time(nullptr));

    std::cout << "Let's play! Complete all 4 random mazes!\n";

    board_and_player bp = board_and_player();

    bp.generate();
    bp.spawn();

    while(bp.round() < 4) {
        bp.cycle();
    }

    std::cout << "Congrats on completing the mazes!\n";

    return 0;
}