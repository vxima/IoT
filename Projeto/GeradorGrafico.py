import matplotlib.pyplot as plt 
def ConvergenciaCompleta():
 plt.clf()
 frames = [0, 1 , 2 , 3 ,4 , 5, 6, 7 ,8, 9 , 10];
 iterations = [0 , 15 , 25 , 33, 48 , 50  , 61 , 68 , 89 , 87 , 109]
 plt.xlabel('Numero de Nós')
 plt.ylabel('Iterations')
 plt.title('Average Time Convergence')
 plt.plot(frames, iterations)
 plt.savefig('Graficos/FullConvergence.png')

def ThroughputPerNodes():
 plt.clf()
 frames = [0, 1 , 2 , 3 ,4 , 5, 6, 7 ,8, 9 , 10];
 success  = [0 , 0.6424697 , 0.6686664 , 0.7799696 , 0.801849 , 0.7943983 , 0.8367715 , 0.8559182 , 0.8763327 , 0.8705739 , 0.8965252]
 plt.xlabel('Numero de frames (10 slots per frame)')
 plt.ylabel('Success Rate')
 plt.title('Average Throughput')
 plt.plot(frames, success)
 plt.savefig('Graficos/Throughput.png')
#ThroughputPerNodes()

def ThroughputPer_E():
 plt.clf()
 e = [0, 0.01 , 0.05 , 0.10 , 0.15 , 0.2];
 success  = [0 , 0.63 , 0.65 , 0.58,  0.59 , 0.5]
 plt.xlabel('Value of E (for 10 nodes and 10 iterations)')
 plt.ylabel('Success Rate')
 plt.title('Average Throughput variating e')
 plt.plot(e, success)
 plt.savefig('Graficos/ThroughputChange_E.png')

def ThroughputPer_Y():
 plt.clf()
 y = [0, 0.1 , 0.2 , 0.3 , 0.4,  0.5 , 0.6, 0.7 , 0.8 , 0.9 , 1.0 ];
 success  = [0 , 0.53 ,0.75 ,  0.65 , 0.67 , 0.76 , 0.59 , 0.58 , 0.69 , 0.7 , 0.56]
 plt.xlabel('Value of Y (for 10 nodes and 10 iterations)')
 plt.ylabel('Success Rate')
 plt.title('Average Throughput variating Y')
 plt.plot(y, success)
 plt.savefig('Graficos/ThroughputChange_Y.png')

def ThroughputPer_Threshold():
 plt.clf()
 th = [0, 1 , 2, 3 , 4,  5 ];
 success  = [0 ,  0.42 , 0.58 ,0.6 , 0.54 , 0.5]
 plt.xlabel('Value of Y (for 10 nodes and 10 iterations)')
 plt.ylabel('Success Rate')
 plt.title('Average Throughput variating Threshold')
 plt.plot(th, success)
 plt.savefig('Graficos/ThroughputChange_Threshold.png')
## Chama tudo
ConvergenciaCompleta()
ThroughputPerNodes()
ThroughputPer_E()
ThroughputPer_Y()
ThroughputPer_Threshold()