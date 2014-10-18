Ação: # Teste 31
Ação: C 1          v[1] := 0
Ação: T 1  1  1.0    acrescenta (1,1.0) a v[1]
Ação: I 1          imprime v[1]               
----> ( 1,  1.0) 
Ação: C 2          v[2] := 0                  
Ação: T 2  2  2.0    acrescenta (2,2.0) a v[2]  
Ação: I 2	     imprime v[2]               
----> ( 2,  2.0) 
Ação: S 3 1 2      v[3] := v[1]+v[2]
Ação: I 3          imprime v[3]    
----> ( 1,  1.0) ( 2,  2.0) 
Ação: L 1          libera v[1]
Ação: L 2          libera v[2]
Ação: L 3          libera v[3]
Ação: X            termina
Processamento terminado
