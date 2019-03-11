#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "boids.h"

int main(){
    
    // seed for rand_normalize
    srand(time(NULL));
   
    // define screen size
    float screenWidth = 1600;
    float screenHeight = 900;

    // create boid system
    struct boid_system *myboid_sys = boid_init(200, screenWidth, screenHeight, 2, 150);
    
    InitWindow(screenWidth, screenHeight, "boids");
    
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        boid_update_neighbors(myboid_sys);
        boid_update(myboid_sys);
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            draw_boid_system(myboid_sys);

        EndDrawing();
   
    }

    CloseWindow();        // Close window and OpenGL context
    boid_release(myboid_sys);

    return 0;
}