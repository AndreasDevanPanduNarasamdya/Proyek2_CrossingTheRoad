#include "LibraryAzzam.h"
#include "LibraryFaiz.h" 

void NextLevel() {
    PermainanBerakhir = (level == 2);

    if (!PermainanBerakhir) {
        level++;
        numCars += 5; 
        carSpeed = (carSpeed < 5) ? carSpeed + 1 : 5; 
        
        player.x = GRID_WIDTH / 2;
        player.y = GRID_HEIGHT - 2;
        checkpoint.x = player.x;
        checkpoint.y = player.y;

        InitGame(); 
    }
}
