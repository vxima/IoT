#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <random>

using namespace std;

// number of nodes must not be greater than number of 
// max number of conflicting nodes must not be greater than number of slots
int N = 4; // number of node
int F = 22; // numbers of frames
int S = 5;  // number of slots in one frame

double y = 1.0;
double e = 0.01;
int threshold = 3;

// seed random number generator
random_device rd; 
mt19937 gen(rd());
uniform_real_distribution<double> dis(0.0, 1.0);
vector<int> transmition_Node(N, 0); // 0: idle  , 1: transmition

int colisao, sucesso, vazio;
int fullcolide, fullsucesso;

//auxiliares
double randP(){ //numero randomico entre 0.0 e 1.0
    return dis(gen);
}

class Slot{
    public:
        int id;
        int k;
        int q_value;
        int escolhido;
        int idle;

        Slot(int new_id){
            id = new_id;
            k = 0;
            q_value = 0;
            escolhido = 0;
            idle = 1;
        }

};

class Node{
    // cada no vai ter sua Q-Table e id
    public:
        int node_id;
        int davez;
        int ultimo;
        int resultado; // 1 = funcionou ; 0 = falhou

        Node(int id){
            node_id = id;
            davez = -1;
            ultimo = -1;
            resultado = -1;
        }
};

vector<Node> network;

vector<vector<Slot>> variosframe;


float randomFloat(){
    return (float)(rand()) / (float)(RAND_MAX);
}

int select_biggest(int iteracao){
    // procura o maior q_value
    int aux = 0;
    for(int i=1; i<S ;i++){
        if(variosframe[iteracao][i].q_value > variosframe[iteracao][aux].q_value){
            // TODO ver se faço um vetor e escolho um aleatorio entre os maiores
            aux = i;
        }
    }
    // cout << "passou da parte 1\n";
    // salva todas as posições empatadas em primeiro com o maior q_value
    vector<int> auxvector;
    int tam = 0;
    for(int i=0; i<S ;i++){
        if(variosframe[iteracao][i].q_value == variosframe[iteracao][aux].q_value){
            // TODO ver se faço um vetor e escolho um aleatorio entre os maiores
            auxvector.push_back(i);
            tam++;
        }
    }
    // cout << "passou da parte 2\n";

    // seleciona e retorna um indicie aleatorio do vetor dos campeões
    cout << tam;
    int randao = rand() % auxvector.size();
    // cout << "passou da parte 3\n";
    return auxvector[randao];
}

int select_idle(int iteracao){
    vector<int> validos;
    for(int i=0;i<S;i++){
        if(variosframe[iteracao][i].idle == 1){
            validos.push_back(i);
        }
    }

    int aux = rand() % validos.size();
    return validos[aux];
}

int select_random(int iteracao){
    if(randP() > e){
        return select_idle(iteracao);
    }
    return select_biggest(iteracao);
}



void select(int iteracao){
    for(int i=0 ; i<N ; i++){
        int aux;
        if(network[i].ultimo == -1){
            cout<< "Chegou aqui 1\n";
            aux = rand() % S;
        }
        else if(network[i].resultado == 1){
            cout<< "Chegou aqui 2\n";
            aux = select_biggest(iteracao);
        }
        else{
            cout<< "Chegou aqui 3\n";
            aux = select_random(iteracao);
        }
        network[i].davez = aux;
        variosframe[iteracao][aux].escolhido++;
        // cout << "selecionei o no: " << aux << "para o carinha de id " << i << "\n";
    }
}

void check_conflicts(int iteracao){
    for(int i=0 ; i<N ; i++){
        int aux = network[i].davez;
        network[i].ultimo = aux;
        network[i].davez = -1;

        int funfou;
        if(variosframe[iteracao][aux].escolhido > 1){
            funfou = 0;
        }
        else{
            funfou = 1;
        }
        network[i].resultado = funfou;
    }
}

void update_values(int iteracao){
    for(int i=0 ; i< S ; i++){

        // supõe que o nó não estava idle
        variosframe[iteracao][i].idle = 0;  

        //pega o valor antigo de k
        int k_antigo = variosframe[iteracao][i].k;

        // se deu pau
        if( variosframe[iteracao][i].escolhido > 1 ){
            colisao = variosframe[iteracao][i].escolhido;
            //se ja tinha dado pau antes
            if( variosframe[iteracao][i].k < 0){
                variosframe[iteracao][i].k--;
            }
            // se tava dando bom ou tava idle
            else{
                variosframe[iteracao][i].k = -1;
            }
        }
        // se deu bom
        else if( variosframe[iteracao][i].escolhido == 1 ){
            sucesso++;
            //se ja tinha dado bom antes
            if( variosframe[iteracao][i].k > 0){
                variosframe[iteracao][i].k++;
            }
            // se tava dando ruim ou tava idle
            else{
                variosframe[iteracao][i].k = 1;
            }
        }
        else{
            // se ficou idle não muda o valor
            variosframe[iteracao][i].idle = 1;
            variosframe[iteracao][i].k = 0;
        }


        // atualiza o q_value
        int sinal;
        (k_antigo < 0) ? sinal = -1 : sinal = 1;
        int k = abs(k_antigo); 
        int R = 1 << k;
        variosframe[iteracao][i].q_value = variosframe[iteracao][i].q_value + (sinal * y * R);
        
        // força para que k não passe do valor máximo
        variosframe[iteracao][i].k = min(variosframe[iteracao][i].k, threshold);
        
        // zerar os escolhidos
        variosframe[iteracao][i].escolhido = 0;
    }
}

int convergiu = 0;

int mainha() {
    //inicializar hiperparametros

    srand(time(NULL)); // seed qrandom number generator

    // Create network
    for(int ii=0; ii < N;ii++){
        Node node = Node(ii);
        network.push_back(node);
    }

    // Create frame vector
    for(int i=0; i<F; i++){
        vector<Slot> frame;
        for(int iii=0; iii < S; iii++){
            Slot node = Slot(iii);
            frame.push_back(node);
        }
        variosframe.push_back(frame);
    }

    int convergiu = 0;
    colisao = 0;
    vazio = 0;
    sucesso = 0;
    // loop de iteraçoes
    for(int frames = 0; frames < F ;frames++){
        //metricas
        cout << "iteracao: " << frames+1 << "\n";
        
        
        // fazer as escolhas
        if(!convergiu){
            select(frames);

            cout<< "Chegou aqui\n";
            for(int i=0; i<S;i++){
                cout << variosframe[frames][i].escolhido << " "; 
            }
            cout << "\n";

            // checar os conflitos
            check_conflicts(frames);

            // atualizar os valores
            update_values(frames);
        }

        // aumentar o valor da probabilidade?
        
        // printar metricas
        cout << "Métricas: sucesso = " << sucesso << " colisao = "<< colisao << "\n";
        cout << "vazão: " << (double) sucesso / (colisao+sucesso) << "\n\n";
        fullcolide+=colisao;
        fullsucesso+=sucesso;
        if(colisao == 0){
            convergiu = 1;
            return frames+1;
        }
        else {
            colisao = 0;
            vazio = 0;
            sucesso = 0;
        }
    }
    return 0;
    
}

int main(){

    // seta os hiperparametros
    N = 5; // number of nodes
    F = 25; // numbers of frames
    S = 6;  // number of slots in one frame
    y = 1.0;
    e = 0.01;
    threshold = 3;
    int TOTAL = 10; // quantas vezes roda o código

    // reseta os resultados gerais
    fullcolide = 0;
    fullsucesso = 0;
    int convergencias = 0;
    int convege_tempo = 0;
    int aux; 
    

    for(int i=0; i<TOTAL; i++){
        cout << "Tentativa " << i << "\n";
        aux = mainha();
        if(aux>0){
            convergencias++;
        }
        convege_tempo+=aux;
        cout << "\n\n\n";
    }
    cout << "resultado para esses parâmetros:\n";
    cout << "convergiu " << (double) convergencias / TOTAL * 100  << " % das vezes\n";
    cout << "convergiu em media em " << (double) convege_tempo/TOTAL << " iterações\n\n";


    return 0;
}
// tentar fazer pra a rede toda conflitando
// tentar fazer pra alguns nos conflitando apenas
// fazer uma chance de transmissao para cada no
// talvez um slot extra decontrole pra uma base station ou varios nos mandarem a atualizacao da rede
