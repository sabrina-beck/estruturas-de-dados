# Testes com parênteses
Infixa: (a)
Posfixa: a

Infixa: (((a)))
Posfixa: a

Infixa: (+a)
Posfixa: a&

Infixa: (a+b)*c^d
Posfixa: ab+cd^*

Infixa: ((a-b)*(c-d)/e)
Posfixa: ab-cd-*e/

Infixa: a^(b*c-d)^e-f
Posfixa: abc*d-e^^f-

Infixa: (-a^b*(c-b))
Posfixa: ab^cb-*~

Infixa: ((((a-b)*c)^d^e))
Posfixa: ab-c*de^^

Processamento terminado
