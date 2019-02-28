#include <stdlib.>
#include "raylib"
#include "boids.h"
#include <ctime>

int screenWidth = 800;
int screenHeight = 450;

srand(time(NULL));

float rand_normalize(){
    float rand_num = (float)rand() / (float)RAND_MAX; 
    return rand_num;
}

struct boid *boid_init(int num, int screenWidth, int screenHeight, position, Vector2 velocity, Vector2 acceleration){
    struct boid *myboids = malloc(sizeof(struct boid)*num); // returns a pointer to an array of struct boids
    for(int i = 0; i < num; i++){
        // set position
        myboids[i].position.x = rand_normalize() * screenWidth;
        myboids[i].position.y = rand_normalize() * screenHeight;
        myboids[i].velocity = velocity;
        myboids[i].acceleration = acceleration;
    }
    
    // create n-1 size array for boids neighbors
    struct neighbors *myneighbors = malloc(sizeof(struct neighbors)) * (n - 1);
}

void boid_release()