**Exercício de aquecimento A [10%]:** _Varie o tamanho da janela fixa editando controller.cc para ver o que acontece. Faça um gráfico 2D de taxa de transferência versus um atraso no sinal com percentil de 95 a medida que você altera esse valor. Qual é o melhor tamanho de janela única que você pode encontrar para maximizar a potência (taxa de transferência/atraso)? Quão repetíveis são as medições feitas com o mesmo tamanho de janela em várias execuções?


Foram testados vários tamanhos de janela com um intervalo incremental de tamanho 5. A Tabela 1 apresenta o resultado de cada simulação e a potência que foi calculada a partir da taxa de transferência e o atraso.

<p float="center" align="center" >
    <img src='img/Tabela1.JPG' width='70%' title='Figura 1' alt='Figura 1' /> 
</p>

Os valores médios das simulações (por janela) foram utilizados para gerar os gráficos apresentados abaixo. A figura 1 apresenta o gráfico 2D de taxa de transferência versus o atraso no sinal com percentil de 95.

<p float="center" align="center" >
    <img src='img/fig 1.JPG' width='70%' title='Figura 1' alt='Figura 1' /> 
</p>

Para compreender melhor os resultados, foi gerado o gráfico (Figura 2) para a potência versus o tamanho da janela.

<p float="center" align="center" >
    <img src='img/fig 2.JPG' width='70%' title='Figura 1' alt='Figura 1' /> 
</p>

Conforme pode ser observado na figura 1, ao passo que a taxa de tranferência é aumentada é observado um maior atraso. O gráfico da potência (Figura 2) mostrou que a janela de tamanho 15 foi a que apresentou os melhores resultados.

Para analisar quão repetíveis são as medições feitas com o mesmo tamanho de janela em várias execuções, foram realizadas 20 repetições para o tamanho de janela 90. A tabela 2 apresenta o resultado das simulações.

**Tabela**  **2**  **- Resultado das vinte repetições para a janela de tamanho 90**


A Tabela 3 apresenta uma análise dos dados utilizando estatística descritiva

**Tabela**  **3** **- Estatística descritiva (Janela de tamanho 90)**

 Após observar a tabela 2 concluiu-se que os dados são bastante repetíveis. Em 20 execuções foram repetidos apenas 5 valores para a taxa de transferência e 4 para o atraso. Na estatística descritiva (Tabela 3) é possível observar que o intervalo entre o valor mínimo e máximo é pequeno, então não há grandes variações nos resultados. A média e mediana também são muito próximas (poucos centésimos de Mbits/s e Ms) assim ambas podem ser utilizadas para representar a taxa de transferência e o atraso para a janela.

**Exercício de aquecimento B [****40%]:**_Implemente um esquema AIMD simples, semelhante `a fase de prevenção de congestionamento do TCP. Quão bem isso funciona? Quais constantes você escolheu._

 Para este exercício foi implementado um esquema simples de ajuste da janela de congestionamento que imita o comportamento do AIMD (_Additive Increase, Multiplicative Decrease_). Este mecanismo reage ao congestionamento de acordo com a largura de banda (detectada) utilizando a seguinte abordagem: Quando não há indicação de perda o remetente aumenta taxa de transmissão (tamanho da janela em 1 slot/RTT), sondando a capacidade utilizável. Quando há um indício de congestionamento (detecção da perda) ocorre a diminuição multiplicativa (janela de congestionamento é reduzida). Nesta implementação foram utilizadas as variáveis Diminuição Multiplicativa e a Variação da Janela, estes valores são estáticos e fixados manualmente. O tamanho _threshold_ foi configurado de acordo com os melhores resultados de atraso obtido no exercício A. Foram realizadas várias simulações alterando os valores das variáveis Diminuição Multiplicativa/Variação da Janela. Os resultados da performance são apresentados na Tabela 4.

**Tabela**  **4**  **– Taxa de transferência e atraso para várias constantes do AIMD**

| Variação da Janela | Diminuição multiplicativa | Taxa de transferência (Mbits/s) | Atraso (ms) | Potência  |
| --- | --- | --- | --- | --- |
| 1 | 0,5 | 3,01 | 257 | 11,73 |
| **1** | **0,66** | **3,6** | **138** | **26,84** |
| 2 | 0,66 | 3,21 | 190 | 16,91 |
| 3 | 0,66 | 3,52 | 225 | 15,66 |
| 4 | 0,66 | 3,38 | 235 | 14,37 |
| 1 | 1 | 4,9 | 915 | 5,36 |
| 1 | 2 | 4,96 | 44887 | 0,11 |
| 1 | 3 | 4,99 | 54508 | 0,09 |
| 1 | 4 | 4,96 | 70559 | 0,07 |
|   |   |   |   |   |

 Para a construção da Tabela 4, foram testadas as Variações da janela com os valores 1, 2, 3 e 4 e a Diminuição multiplicativa com 0.5, 0.6, 1, 2, 3 e 4. Os resultados mostram que a melhor configuração encontrada é a Variação da janela = 1 e a Diminuição multiplicativa = 0.66 para confirmar esse resultado, esta simulação foi repetida mais de 35 vezes. Os resultados destas repetições são apresentados na Tabela 5. A análise estatística (Tabela 6) mostra que está configuração apresenta a melhor potência quando comparado com as demais (Tabela 4).

**Tabela 5 -  Repetições da melhor configuração encontrada para o AIMD**



**Tabela**  **6** **- Estatística descritiva AIMD (Variação janela=1/Diminuição multiplicativa=0.66)**



**Exercício D [50%]: Tente diferentes abordagens e trabalhe para maximizar a potência (compare com os resultados dos demais colegas da sala e tente melhorar). Em seu relatório, explique sua abordagem, incluindo as decisões importantes que você teve que tomar e como você as fez. Inclua gráficos ilustrativos com os resultados.**

Para maximizar a potência o algoritmo foi otimizado para aumentar ou diminuir o tamanho da janela de forma adaptativa. A abordagem é menos agressiva que a apresentada no exercício B com relação ao congestionamento, sendo mais focada no controle e com o objetivo de evitar o congestionamento.  O esquema possui o seguinte funcionamento:  O atraso é calculado a partir do RTT (atraso = tempo do ACK recebido menos o tempo do ACK enviado), se o atraso for maior que o valor estipulado o tamanho da janela é reduzido até a normalização da fila. Caso o atraso seja menor que o valor estipulado, a janela é incrementada.  Em caso de congestionamento, isto é, se após o _timeout_ a janela ainda estiver apresentando um valor alto, o tamanho da janela é dividido pela metade.

  Após encontrar a melhor configuração, a simulação foi repetida 40 vezes para verificar a consistência dos resultados. A estatística descritiva das repetições (Tabela 7) mostra que a variação entre o valor mínimo e máximo é pequena. Com relação à média da potência (34,15), verificou-se que esta implementação apresentou uma melhora no desempenho quando comparado com o esquema proposto no exercício B (24,30).

**Tabela**  **7**  **– Estatística descritiva das 40 repetições**


**Exercício E [0%]: escolha um nome legal para o seu esquema**

[http://cs344g.keithw.org/report?Lih-1540948299-faleefei](http://cs344g.keithw.org/report?Lih-1540948299-faleefei)
