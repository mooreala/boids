#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"
#include "boids.h"

float rand_normalize(){
    float rand_num = (float)rand() / (float)RAND_MAX; 
    return rand_num;
}

// Passes in: max num boids, screenwidth, screenheight, max velocity, max radius
// Returns pointer to a boid system
struct boid_system *boid_init(unsigned num, float screenWidth, float screenHeight, float velocity, float radius){
    // init boid system
    struct boid_system *myboid_sys = malloc(sizeof(struct boid_system));
    myboid_sys->n = num;
    myboid_sys->width = screenWidth;
    myboid_sys->height = screenWidth;

    // init boid array
    struct boid *myboids = malloc(sizeof(struct boid)*num); // returns a pointer to an array of struct boids
    for(int i = 0; i < num; i++){
        // set fields
        myboids[i].position.x = rand_normalize() * screenWidth;
        myboids[i].position.y = rand_normalize() * screenHeight;
        myboids[i].max_velocity = velocity;
        myboids[i].velocity.x = rand_normalize() * velocity;
        myboids[i].velocity.y = rand_normalize() * velocity;

        // malloc neighbors
        // create n-1 size array for boids neighbors
        struct boid **myneighbors = malloc(sizeof(struct boid*) * (num - 1));
        myboids[i].neighbors.buds = myneighbors;
        myboids[i].neighbors.n = 0;
        myboids[i].neighbors.radius = radius;
    }
    
    myboid_sys->boids = myboids;
    return(myboid_sys);
}

void boid_release(struct boid_system *myboid_sys){
    // free each boid's neighborhood
    unsigned num = myboid_sys->n;
    for(int i = 0; i < num; i++){
        free(myboid_sys->boids[i].neighbors.buds);
    }
    // free boids
    free(myboid_sys->boids);
    // free system
    free(myboid_sys);
}

Vector2 boid_separation(struct boid *myboid){
    // start with zero accel vector
    Vector2 acceleration = Vector2Zero();
    // for each neighbor, add displacement from boid
    for(int i = 0; i < myboid->neighbors.n; i++){
        // calculate each displacement between the boid and its neighbors
        Vector2 displacement = Vector2Subtract(myboid->position, myboid->neighbors.buds[i]->position);
        // sum displacement vectors and accel vector
        acceleration = Vector2Add(acceleration, displacement);
    }
    return (acceleration);
}

Vector2 boid_cohesion(struct boid *myboid){
    // start with zero sum vector
    Vector2 sum = Vector2Zero();
    // sum the position of every neighbor boid
    for(int i = 0; i < myboid->neighbors.n; i++){
        sum = Vector2Add(sum, myboid->neighbors.buds[i]->position);
    }
    // divide by number of neighbors to get average pos
    Vector2 avg_pos = Vector2Divide(sum, myboid->neighbors.n);
    // find displacement between boid pos and average pos
    Vector2 displacement = Vector2Subtract(avg_pos, myboid->position);
    // return displacement vector for accel
    return (displacement);
}

Vector2 boid_alignment(struct boid *myboid){
// start with zero velocity vector
Vector2 velocity = Vector2Zero();
// sum the velocity of every neighbor boid
for(int i = 0; i < myboid->neighbors.n; i++){
    // calculate displacement 
    Vector2 displacement = Vector2Subtract(myboid->neighbors.buds[i]->position, myboid->position);
    // calculate magnitude of displacement
    float displacement_length = Vector2Length(displacement);
    // normalize neighbor velocity (get direction)
    Vector2 bud_vel = Vector2Normalize(myboid->neighbors.buds[i]->velocity);
    // to calculate scaling factor, divide neighbors velocity by the mag of displacement
    bud_vel = Vector2Divide(bud_vel, displacement_length);
    // calculate velocity
    velocity = Vector2Add(velocity, bud_vel);
}
// return average velocity
return (velocity);
}

