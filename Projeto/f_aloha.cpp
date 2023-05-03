#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

#define N 8 // number of stations
#define T 10 // number of time slots

// Q-values e K para respectivo slot 
vector<int> Q(N, 0);   
vector<int> K(N, 0);
float randomFloat(){
    return (float)(rand()) / (float)(RAND_MAX);
}
//TO-DO
void update_Qvalue( float y , float threshold, int slot_idx){
    
    int R;
    if(true){ //sucesso 
        R = 1<<K[slot_idx];
        Q[slot_idx] = Q[slot_idx] + y*R;
        //falta computar k 
    } 
    else {
        R = 1<<K[slot_idx];
        Q[slot_idx] = Q[slot_idx] - y*R;
        //falta computar k
    }
}
int select_slot(float e, int slot_idx){
    //TO-DO
    float p;
    if(true){ //colisao
        p = randomFloat();
        if(p<e){
            //select random idle slot 
        }
        else{
        // select a random slot with highest Q-value
        }
    }
    else{
        //select a random slot with highest Q-value
    }
    return slot_idx;
}
int main() {
    //inicializar hiperparametros
    float y = 1.0;
    float e = 0.01;
    float threshold = 3.0;

    srand(time(NULL)); // seed random number generator

    // initialize station states
    
     
    return 0;
}
