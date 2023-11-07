#include "manager.h"
#include "board.h"

// testing board initiation and drawing
int main() {
    Manager* manager = new Manager();

    while (true) {
        manager->run();
       
    }

    delete manager;
    return 0;

}