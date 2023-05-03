#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10 // number of stations
#define p 0.5 // probability of transmitting
#define T 1000 // number of time slots

int main() {
    int i, j, t, success_count = 0, collision_count = 0;
    int x[N]; // 0: idle, 1: transmitting
    srand(time(NULL)); // seed random number generator

    // initialize station states
    for (i = 0; i < N; i++) {
        x[i] = 0;
    }

    // simulate T time slots
    for (t = 1; t <= T; t++) {
        printf("Time slot %d:\n", t);

        // determine which stations are attempting to transmit
        for (i = 0; i < N; i++) {
            if (x[i] == 0 && ((double) rand() / RAND_MAX) < p) {
                x[i] = 1; // set station to transmitting state
            }
        }

        // count the number of successes and collisions
        int transmitting_count = 0;
        for (i = 0; i < N; i++) {
            if (x[i] == 1) {
                transmitting_count++;
                if (transmitting_count > 1) {
                    collision_count++;
                    break;
                }
            }
        }
        if (transmitting_count == 1) {
            success_count++;
        }

        // reset the station states
        for (i = 0; i < N; i++) {
            x[i] = 0;
        }

        // print station states for this time slot
        for (i = 0; i < N; i++) {
            printf("Station %d: ", i + 1);
            if (x[i] == 0) {
                printf("idle\n");
            } else if (x[i] == 1) {
                printf("transmitting\n");
            }
        }
        printf("\n");
    }

    // print the overall results
    printf("Success rate: %f\n", (float) success_count / T);
    printf("Collision rate: %f\n", (float) collision_count / T);

    return 0;
}
