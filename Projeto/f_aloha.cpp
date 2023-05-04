#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <random>

using namespace std;

#define N 4 // number of node
#define F 10 // numbers of frames
#define S 5  // number of slots in one frame

#define y 1.0;
#define e 0.01;
#define threshold  3.0;

// seed random number generator
random_device rd; 
mt19937 gen(rd());
uniform_real_distribution<double> dis(0.0, 1.0);
vector<int> transmition_Node(N, 0); // 0: idle  , 1: transmition

//auxiliares
double randP(){ //numero randomico entre 0.0 e 1.0
    return dis(gen);
}
int computeK(int k){ //computar K
    if(k>= 0)
        return k++;
    else
        return 0;
}
int max_index(const vector<pair<double, int>>& vec) { //return the index of the maximum first element in a vector of pair 
    auto max_it = max_element(vec.begin(), vec.end(),
        [](const auto& p1, const auto& p2) { return p1.first < p2.first; });
    return distance(vec.begin(), max_it);
}
class QTable{
    //cada table vai ter o Q-Value e o K de cada slot
    public:    
        int node_idx;
        vector<pair<double, int>> state;
        QTable() : node_idx(0), state(S, make_pair(0.0, 0)) {}
        QTable(int id) : node_idx(id){
            pair<double, int> pa(0.0 , 0); // Q-value e K
            state = vector<pair<double, int>>(F , pa); //array de 5 slots com Q-value e K
            node_idx = id;
        }

        void updateQValue(int slot_idx){
            int K = state[slot_idx].second;
            int  R = 1<<K; // R=1<<K
            if(true){
                state[slot_idx].first = state[slot_idx].first + R*y; // Q=Q+γR;
                state[slot_idx].second = computeK(K);
            }
            else if(false){ //colisao
                state[slot_idx].first = state[slot_idx].first - R*y; // Q=Q-γR;
                state[slot_idx].second = computeK(K);
            }
        }

        int selectSlot(){
            int slot;
            if(true){ //colisao
                if( randP() < 0.01){ // p<e
                    //selectionar random idle slot
                    slot =  rand() % S; 
                }
                else{
                    //select a random slot with highest Q-value
                    slot =  max_index(state);
                }
            } 
            else{
                //select a random slot with highest Q-value
                slot =  max_index(state);
            }
            return slot;
        }
};
class Node{
    // cada no vai ter sua Q-Table e id
    public:
        int node_id;
        QTable table;
        Node(int id){
            node_id = id;
            table = QTable(id);
        }
};


float randomFloat(){
    return (float)(rand()) / (float)(RAND_MAX);
}
int main() {
    //inicializar hiperparametros
    

    srand(time(NULL)); // seed random number generator

    // Create network
    vector<Node> network;
    for(int i=1; i<=N;i++){
        Node node = Node(i);
        network.push_back(node);
    }
    // loop de iteraçoes
    for(int frame = 0; frame<F;frame++){

    }
    return 0;
}
