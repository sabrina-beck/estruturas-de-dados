Ação: # Testes sem rotação para a função remove
Ação: # Remove a raiz 
Ação: i 036462 João Moreira
Ação: r 036462
Ra 036462 removido.
Ação: n
Número de nós na base de dados: 0.
Ação: d

Árvore vazia

Ação: l
Ação: # Remove raiz contendo apenas o filho direito
Ação: i 036462 João Moreira
Ação: i 661116 José Neves
Ação: r 036462
Ra 036462 removido.
Ação: p
661116 José Neves
Ação: d

 661116

Ação: l
Ação: # Remove raiz contendo apenas o filho esquerdo
Ação: i 661116 José Neves
Ação: i 036462 João Moreira
Ação: r 661116
Ra 661116 removido.
Ação: p
036462 João Moreira
Ação: d

  36462

Ação: l
Ação: # Remove folha da sub-árvore esquerda
Ação: i 013774 Mário Bragança
Ação: i 032875 José Souza
Ação: i 006924 Ricardo Silva
Ação: r 006924
Ra 006924 removido.
Ação: p  
013774 Mário Bragança
032875 José Souza
Ação: d

   / 32875
  13774

Ação: l
Ação: # Remove folha da sub-árvore direita
Ação: i 013774 Mário Bragança
Ação: i 032875 José Souza
Ação: i 006924 Ricardo Silva
Ação: r 032875
Ra 032875 removido.
Ação: p  
006924 Ricardo Silva
013774 Mário Bragança
Ação: d

  13774
   \  6924

Ação: l
Ação: # Remove nó contendo apenas o filho esquerdo
Ação: i 031780 Elaine Ferreira
Ação: i 036206 Carlos Nogueira
Ação: i 025680 Renato de Souza
Ação: i 014098 Pedro Silveira
Ação: r 025680
Ra 025680 removido.
Ação: p
014098 Pedro Silveira
031780 Elaine Ferreira
036206 Carlos Nogueira
Ação: a
Altura da base de dados: 2.
Ação: d

   / 36206
  31780
   \ 14098

Ação: l
Ação: # Remove folha 
Ação: i 031780 Elaine Ferreira
Ação: i 036206 Carlos Nogueira
Ação: i 025680 Renato de Souza
Ação: i 014098 Pedro Silveira
Ação: r 014098
Ra 014098 removido.
Ação: p
025680 Renato de Souza
031780 Elaine Ferreira
036206 Carlos Nogueira
Ação: a
Altura da base de dados: 2.
Ação: d

   / 36206
  31780
   \ 25680

Ação: l
Ação: # Remove nó contendo apenas o filho direito
Ação: i 031780 Elaine Ferreira
Ação: i 036206 Carlos Nogueira
Ação: i 014098 Pedro Silveira
Ação: i 025680 Renato de Souza
Ação: r 014098
Ra 014098 removido.
Ação: p
025680 Renato de Souza
031780 Elaine Ferreira
036206 Carlos Nogueira
Ação: a
Altura da base de dados: 2.
Ação: d

   / 36206
  31780
   \ 25680

Ação: l
Ação: # Remove folha 
Ação: i 031780 Elaine Ferreira
Ação: i 036206 Carlos Nogueira
Ação: i 014098 Pedro Silveira
Ação: i 025680 Renato de Souza
Ação: r 025680
Ra 025680 removido.
Ação: # Testa remoção de elemento ausente
Ação: r 021470
Ra 021470 não encontrado na base de dados.
Ação: p
014098 Pedro Silveira
031780 Elaine Ferreira
036206 Carlos Nogueira
Ação: a
Altura da base de dados: 2.
Ação: d

   / 36206
  31780
   \ 14098

Ação: l
Ação: x
Processamento terminado
