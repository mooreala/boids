// This header file includes structs and function prototypes for boids

#include "raylib.h"

// define boid neighbor 
struct neighborhood{
    struct boid **buds; // array of struct boid POINTERS(second pointer)
    unsigned n; // number of buds
    float radius; // radius of field
};

// define struct boid
struct boid{
    Vector2 position; // where is it
    Vector2 velocity; // how fast is it going
    float max_velocity; // max speed
    //Vector2 acceleration; // how fast is it accelerating
    struct neighborhood neighbors; // neighbors
};

// define boid system 
struct boid_system{
    struct boid *boids;
    unsigned n;
    float width;
    float height;
};

// boid function prototypes
float rand_normalize();
struct boid_system *boid_init(unsigned, float, float, float, float);
void boid_release(struct boid_system *);
Vector2 boid_separation(struct boid *);
Vector2 boid_cohesion(struct boid *);
Vector2 boid_alignment(struct boid *);
void boid_pos_update(struct boid *);