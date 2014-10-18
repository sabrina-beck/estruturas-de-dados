Ação: # Teste 23
Ação: a A 2 3.0           A <- 3x^2 
Ação: a B 1 2.0           B <- 2x
Ação: r C AB*~            C <- -(A*B)
Ação: i C                 imprime C
----> ( 3, -6.0) 
Ação: r D CC~+            D <- C +(-C)
Ação: i D                 imprime D
----> Polinômio nulo
Ação: r E AB+C+D*         E <- (A+B+C)*D
Ação: i E 
----> Polinômio nulo
Ação: l A                 libera A
Ação: l B                 libera B 
Ação: l C                 libera C
Ação: l D                 libera D
Ação: l E                 libera E
Ação: x                   termina 
Processamento terminado
