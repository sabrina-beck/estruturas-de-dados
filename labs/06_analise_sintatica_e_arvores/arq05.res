# Testes com espaços em branco
Infixa:          a
Prefixa: a
Posfixa: a


Infixa:       +    a-a
Prefixa: -&aa
Posfixa: a&a-


Infixa:  a  +  b
Prefixa: +ab
Posfixa: ab+


Infixa:  a / b   - c*d + e -f- g-h + i*  j*k*l/m
Prefixa: +---+-/ab*cdefgh/***ijklm
Posfixa: ab/cd*-e+f-g-h-ij*k*l*m/+


Infixa: ( (a-b) * (c-d)/e )
Prefixa: /*-ab-cde
Posfixa: ab-cd-*e/


Infixa:    ( ( (   (a - b) *c    )^ d ^ e)   )
Prefixa: ^*-abc^de
Posfixa: ab-c*de^^


# Agora vem uma cadeia de 10 brancos
Infixa:           
Erro:   ^
        Cadeia de brancos.


Processamento terminado
