#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <random>

using namespace std;

int N = 40;// number of node
int S = 40;  // number of slots in one frame

 //inicializar hiperparametros
const double y = 1.0;
const double e = 0.01;
const double threshold = 3.0;

// seed random number generator
random_device rd; 
mt19937 gen(rd());
uniform_real_distribution<double> dis(0.0, 1.0);

int successCount = 0;
int colisionCount = 0; //começa vazio
int voidCount = 0;
int totalSlots = 0;
vector<int> slotTransmiting(S, 0);

int checkTransmition(int slot_id){
    if(slotTransmiting[slot_id] == 1){
        return 1; //sucesso
    } else if(slotTransmiting[slot_id] > 1){
        return 2; //colisao
    } else {
        return 0; // vazio
    }
}
void metricFrame(){
    for(int i=0;i<S;i++){
        if(slotTransmiting[i] == 1){
            successCount++;
        } else if(slotTransmiting[i] > 1){
            colisionCount++;
        } else{
            voidCount++;
        }
        totalSlots++;
    }

}
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

int max_value_index(vector<pair<double, int>>& values) {
    int max_idx = 0;
    double max_val = values[0].first;
    vector<int> max_indices = {0};
    for (int i = 1; i < values.size(); i++) {
        if (values[i].first > max_val) {
            max_indices = {i};
            max_idx = i;
            max_val = values[i].first;
        } else if (values[i].first == max_val) {
            max_indices.push_back(i);
        }
    }
    if (max_indices.size() > 1) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, max_indices.size() - 1);
        max_idx = max_indices[dis(gen)];
    }
    return max_idx;
}
class QTable{
    //cada table vai ter o Q-Value e o K de cada slot
    public:    
        int node_idx;
        vector<pair<double, int>> state;
        QTable() : node_idx(0), state(S, make_pair(0.0, 0)) {}
        QTable(int id) : node_idx(id){
            pair<double, int> pa(0.0 , 0); // Q-value e K
            state = vector<pair<double, int>>(S , pa); //array de 5 slots com Q-value e K
            node_idx = id;
        }

        void updateQValue(int slot_idx){
            int check = checkTransmition(slot_idx);
            int K = state[slot_idx].second;
            int  R = 1<<K; // R=1<<K
            if(check == 1){ //sucesso
                state[slot_idx].first = state[slot_idx].first + R*y; // Q=Q+γR;
                state[slot_idx].second = computeK(K);
            }
            else if(check == 2){ //colisao
                state[slot_idx].first = state[slot_idx].first - R*y; // Q=Q-γR;
                state[slot_idx].second = computeK(K);
            }
        }

        int selectSlot(int slot_id){
            int slot = slot_id;
            int check = checkTransmition(slot_id);
            if(check == 2){ //colisao
                if( randP() < e){ // p<e
                    //selectionar random idle slot
                    slot =  rand() % S; 
                }
                else{
                    //select a random slot with highest Q-value
                    slot =  max_value_index(state);
                }
            } 
            else{
                //select a random slot with highest Q-value
                slot =  max_value_index(state);
            }
            return slot;
        }
};
class Node{
    // cada no vai ter sua Q-Table e id
    public:
        int node_id;
        QTable table;
        int selectedSlot;
        Node(int id){
            node_id = id;
            table = QTable(id);
            selectedSlot = rand() % S; 
        }
};








//auxiliares
void printSlotArray(){
    for (auto elem : slotTransmiting) cout << elem << " ";
    cout << endl;
}


void updateSlotTransmiting(vector<Node> network){
    fill(slotTransmiting.begin(), slotTransmiting.end(), 0);
    for(int no = 0 ; no < N ; no++){
        slotTransmiting[network[no].selectedSlot]++;
    }

}

bool converged(){
    for(int i=0; i<S;i++){
        if(slotTransmiting[i] != 1){
            return false;
        }
    }
    return true;
}
int main() {
    
    // Create network
    int cont =0;
    srand(1234);
    vector<Node> network;
    for(int i=0; i<N;i++){
        Node node = Node(i);
        network.push_back(node);
    }   
    updateSlotTransmiting(network); 
    // loop de iteraçoes
    //cout << "Slots inicias: " << endl;
    //printSlotArray();
    //cout << "Slots atualizados: " << endl;
    while(!converged()){ //nao convergiu
         // print which slots are used
        cont++;
        for(int node_id = 0; node_id<N;node_id++){
            network[node_id].table.updateQValue(network[node_id].selectedSlot);
            network[node_id].selectedSlot = network[node_id].table.selectSlot(network[node_id].selectedSlot); //atualiza slot escolhido pelo nó
    
        }
        updateSlotTransmiting(network); 
        //printSlotArray();
        metricFrame();
    }
    cout << "Case for " <<  N << " Nodes" << endl;
    cout /*<< "Success Rate: "*/ <<(double) successCount/(totalSlots) << endl;
    cout /*<< "Colision Rate: "*/ <<(double) colisionCount/(totalSlots) << endl;
    cout /*<< "Void Rate: "*/ <<(double) voidCount/(totalSlots) << endl;
    cout /*<< "Convergence Time(iterations): "*/ << cont <<  endl;
    return 0;
}
