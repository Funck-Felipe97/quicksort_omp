"""
@author: funck
"""

import numpy as np
import matplotlib.pyplot as plt
%matplotlib inline

faixa_intervalos = ['10', '50', '100', '150', '200']
tempo_sequencial = [0.002000, 0.007000, 0.017000, 0.024000, 0.035000]
tempo_paralelo = [0.001000, 0.001000, 0.004000, 0.003000, 0.003000]

#Definindo largura das barras
barWidth = 0.30
    
#Aumentando o gráfico
plt.figure(figsize=(10,5))
    
#Definindo a posição das barras
r1 = np.arange(len(tempo_sequencial))
r2 = [x + barWidth for x in r1]

#Criando barras
plt.bar(r1, tempo_sequencial, color='red', width=barWidth, label='Tempo sequencial')
plt.bar(r2, tempo_paralelo, color='blue', width=barWidth, label='Tempo paralelo')
    
#Adicionando legendas as barras
plt.xlabel('Quandidade de números ordenados (Mil)')
plt.xticks([r + barWidth for r in range(len(faixa_intervalos))], faixa_intervalos)
plt.ylabel('Tempo de execução (segundos)')
    
#Criando a legenda e exibindo o gráfico
plt.legend()
plt.title('Comparação com 4 nucleos')
plt.show()

