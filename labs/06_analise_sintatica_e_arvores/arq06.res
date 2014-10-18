# Teste com expressões inválidas
# Operando esperado
Infixa: +
Erro:    ^
        Operando esperado nesta posição.


Infixa: *
Erro:   ^
        Operando esperado nesta posição.


Infixa: (
Erro:    ^
        Operando esperado nesta posição.


Infixa: )
Erro:   ^
        Operando esperado nesta posição.


Infixa: a-
Erro:     ^
        Operando esperado nesta posição.


Infixa:   a  -
Erro:         ^
        Operando esperado nesta posição.


Infixa: a--b
Erro:     ^
        Operando esperado nesta posição.


Infixa: a - - b
Erro:       ^
        Operando esperado nesta posição.


Infixa: a*b/  
Erro:         ^
        Operando esperado nesta posição.


Infixa:  a * b/
Erro:          ^
        Operando esperado nesta posição.


Infixa: a*b/((c+d)-                
Erro:                              ^
        Operando esperado nesta posição.


Infixa: ()
Erro:    ^
        Operando esperado nesta posição.


Infixa: a+( )
Erro:       ^
        Operando esperado nesta posição.


Infixa: ((((a-b)*c)^d^e)-)
Erro:                    ^
        Operando esperado nesta posição.


# Operador esperado
Infixa: ab
Erro:    ^
        Operador esperado nesta posição.


Infixa: a      b
Erro:          ^
        Operador esperado nesta posição.


Infixa: a*b+c*d^e/f-gh^i*j
Erro:                ^
        Operador esperado nesta posição.


Infixa: a+b)+c
Erro:      ^
        Operador esperado nesta posição.


Infixa: ((a-b)))+c
Erro:          ^
        Operador esperado nesta posição.


# Fecha parênteses esperado
Infixa: (a-b
Erro:       ^
        Fecha parêntese esperado nesta posição.


Infixa: (((a-b))
Erro:           ^
        Fecha parêntese esperado nesta posição.


Infixa: ((a-b)*(b-c)
Erro:               ^
        Fecha parêntese esperado nesta posição.


Infixa: a*b*c-(e-f
Erro:             ^
        Fecha parêntese esperado nesta posição.


# Caracteres inválidos
Infixa: !
Erro:   ^
        Caractere inválido nesta posição.


Infixa: a;
Erro:    ^
        Caractere inválido nesta posição.


Infixa: a - b @
Erro:         ^
        Caractere inválido nesta posição.


Infixa: a%c
Erro:    ^
        Caractere inválido nesta posição.


Processamento terminado
