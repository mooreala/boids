// This header file includes structs and function prototypes for boids

#include "raylib.h"

// define struct boid
struct boid{
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    struct boid_neighbor bud;
}

// define boid neighbor 
struct boid_neighbor{
    struct boid **buds;
    unsigned n; // number of boids
    float radius; 
}

// define boid system 
struct boid_system{
    struct boid *boids;
    int n;
    float width;
    float height;
}

// boid functions
void boid_init(int, Vector2, float);