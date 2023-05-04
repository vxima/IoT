#include <iostream>
#include <vector>
#include <random>

using namespace std;

const int N = 10; // number of stations
const double p = 0.1; // probability of transmitting
const int T = 1000; // number of time slots
const int S = 5; // number of time slots per frame

int main() {
    vector<int> x(N, 0); // station states (0: idle, 1: transmitting)
    int success_count = 0, collision_count = 0;
    random_device rd; // seed random number generator
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 1.0);

    // simulate T time slots
    for (int t = 1; t <= T; t++) {
        cout << "Time slot " << t << ":\n";

        // determine which stations are attempting to transmit
        int transmitting_count = 0;
        for (int i = 0; i < N; i++) {
            if (x[i] == 0 && dis(gen) < p) {
                x[i] = 1; // set station to transmitting state
                transmitting_count++;
            }
        }

        // count the number of successes and collisions at the end of each frame
        if (t % S == 0) {
            if (transmitting_count == 1) {
                success_count++;
            } else if (transmitting_count > 1) {
                collision_count++;
            }
            // reset the station states at the end of each frame
            fill(x.begin(), x.end(), 0);
        }

        // print station states for this time slot
        for (int i = 0; i < N; i++) {
            cout << "Station " << i + 1 << ": ";
            if (x[i] == 0) {
                cout << "idle\n";
            } else if (x[i] == 1) {
                cout << "transmitting\n";
            }
        }
        cout << endl;
    }

    // print the overall results
    cout << "Success rate: " << (double) success_count / (T/S) << endl;
    cout << "Collision rate: " << (double) collision_count / (T/S) << endl;
    cout << "Idle rate: " << (double) (1 - ((success_count / (T/S)) + (collision_count / (T/S)))) << endl;
    return 0;
}
