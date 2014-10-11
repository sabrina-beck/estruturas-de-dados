# Testes com espaços em branco
Infixa:          a
Posfixa: a

Infixa:       +    a-a
Posfixa: a&a-

Infixa:  a  +  b
Posfixa: ab+

Infixa:  a / b   - c*d + e -f- g-h + i*  j*k*l/m
Posfixa: ab/cd*-e+f-g-h-ij*k*l*m/+

Infixa: ( (a-b) * (c-d)/e )
Posfixa: ab-cd-*e/

Infixa:    ( ( (   (a - b) *c    )^ d ^ e)   )
Posfixa: ab-c*de^^

# Agora vem uma cadeia de 10 brancos
Infixa:           
Erro:   ^
        Cadeia de brancos.

Processamento terminado
