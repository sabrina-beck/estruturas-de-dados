# Testes com parênteses
Infixa: (a)
Prefixa: a
Posfixa: a


Infixa: (((a)))
Prefixa: a
Posfixa: a


Infixa: (+a)
Prefixa: &a
Posfixa: a&


Infixa: (a+b)*c^d
Prefixa: *+ab^cd
Posfixa: ab+cd^*


Infixa: ((a-b)*(c-d)/e)
Prefixa: /*-ab-cde
Posfixa: ab-cd-*e/


Infixa: a^(b*c-d)^e-f
Prefixa: -^a^-*bcdef
Posfixa: abc*d-e^^f-


Infixa: (-a^b*(c-b))
Prefixa: ~*^ab-cb
Posfixa: ab^cb-*~


Infixa: ((((a-b)*c)^d^e))
Prefixa: ^*-abc^de
Posfixa: ab-c*de^^


Processamento terminado
