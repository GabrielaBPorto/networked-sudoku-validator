Alunas: Gabriela Bairros Porto GRR20167286 & Helena Regina Salome D Espindula GRR20161445
--Comandos usuário--
Como funciona o jogo do sudoku.
É pedido o nome do usuário que está jogando, então é repassado um tabuleiro para o cliente.
Os comandos que podem ser utilizados pelo cliente são:
Coordenadas : C<número da linha><número da coluna>
Seguido do que você deseja fazer nas coordenadas.
	Escrever: WT<valor>
	Deletar: DEL
Desistir : GUP
Se você desistir o jogo acabará no mesmo momento, caso o contrário o jogo só irá acabar quando você preencher completamente o tabuleiro.


--Dentro do código--
São utilizados palavras de 3 letras de protocolo que são trocados entre o cliente e o servidor, códigos de confirmação se foi gravado.
1) Teste da conexão.
2) Começo jogo: Cliente pede jogo ao servidor 
3) Servidor sorteia jogo e manda ao cliente. Atualmente só possui um jogo.
4) Cliente imprime o jogo na tela
5) Quando o cliente quer preencher ou apagar um numero ele envia a posição e o número ao servidor
6) Servidor testa se o numero já existe naquela linha, coluna ou quadrado, se sim retorna erro para o cliente (se não retorna ok para cliente e atualiza a tela para o cliente).
7a) Se o cliente recebe ok o cliente atualiza a tela de jogo
7b) Se recebe erro imprime mensagem de erro para usuario
8) Se o cliente apaga algum numero ele avisa o servidor, o servidor aceita ou recusa (se for parte do mapa original) o apagar.
9a) Se aceita manda um aceite para o cliente com um novo mapa
9b) Se recusa manda erro
10) Quando matriz de jogo cheia o servidor avisa o cliente que é fim de jogo (e pode mandar o tempo que levou desde que o jogo começou).

STR - Começar jogo;
OK1 - STR recebido; 
OK2 - Nome jogador recebido; 
G00 - Numero do jogo sorteado (segue mapa atualizado - 81 bytes); 
BRD - Tabuleiro recebido; 
C00 - Posiçao do cursor na matriz (segue Write ou Del); 
WT1 - Escrito esse numero; 
ER1 - Erro 1 - ja existe na linha; 
ER2 - Erro 2 - Ja existe na coluna; 
ER3 - Erro 3 - Ja existe no quadrado;
AKW - Escrita aceita (segue mapa atualizado - 81 bytes); 
DEL - Agagou o numero; 
AKD - Aceitou o apagar (segue mapa atualizado - 81 bytes); 
GUP - Give up; 
ERD - Erro no apagar; 
END - Fim de jogo;
TIM - Tempo de jogo
