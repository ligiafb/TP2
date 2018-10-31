**Exercício de aquecimento A [10%]: Varie o tamanho da janela fixa editando controller.cc para ver o que acontece. Faça um gráfico 2D de taxa de transferência versus um atraso no sinal com percentil de 95 a medida que você altera esse valor. Qual é o melhor tamanho de janela única que você pode encontrar para maximizar a potência (taxa de transferência/atraso)? Quão repetíveis são as medições feitas com o mesmo tamanho de janela em várias execuções?**

Foram testados vários tamanhos de janela com um intervalo incremental de tamanho 5. A Tabela 1 apresenta o resultado de cada simulação e a potência que foi calculada a partir da taxa de transferência e o atraso.


[![Tabela 1](https://image.ibb.co/eZRoV0/Tabela1.jpg "Tabela 1")](https://image.ibb.co/eZRoV0/Tabela1.jpg "Tabela 1")


Os valores médios das simulações (por janela) foram utilizados para gerar os gráficos apresentados abaixo. A figura 1 apresenta o gráfico 2D de taxa de transferência versus o atraso no sinal com percentil de 95.

[![Figura 1](https://image.ibb.co/nporiL/figura1.jpg "Figura 1")](https://image.ibb.co/nporiL/figura1.jpg "Figura 1")

Para compreender melhor os resultados, foi gerado o gráfico  para a potência versus o tamanho da janela (Figura 2).

[![Figura 2](https://image.ibb.co/nxH6Hf/figura2.jpg "Figura 2")](https://image.ibb.co/nxH6Hf/figura2.jpg "Figura 2")

Conforme pode ser observado na figura 1, ao passo que a taxa de tranferência é aumentada é observado um maior atraso. O gráfico da potência (Figura 2) mostrou que a janela de tamanho 15 foi a que apresentou os melhores resultados.	

Para analisar quão repetíveis são as medições feitas com o mesmo tamanho de janela em várias execuções, foram realizadas 20 repetições para o tamanho de janela 90. A tabela 2 apresenta o resultado das simulações e a Tabela 3 uma análise dos dados com estatística descritiva.



