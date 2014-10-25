# Express�es simples sem par�nteses
Infixa: a
Posfixa: a

Infixa: -a
Posfixa: a~

Infixa: +a
Posfixa: a&

Infixa: a+b
Posfixa: ab+

Infixa: a-b
Posfixa: ab-

Infixa: a*b
Posfixa: ab*

Infixa: a/b
Posfixa: ab/

Infixa: a^b
Posfixa: ab^

# Express�es com os operadores bin�rios + - * / 
Infixa: a+b+c
Posfixa: ab+c+

Infixa: a+b-c
Posfixa: ab+c-

Infixa: a*b*c
Posfixa: ab*c*

Infixa: a*b/c
Posfixa: ab*c/

Infixa: a-b*c/d-e
Posfixa: abc*d/-e-

Infixa: a-b*c+d+e/f*g-h
Posfixa: abc*-d+ef/g*+h-

Infixa: a/b-c*d+e-f-g-h+i*j*k*l/m
Posfixa: ab/cd*-e+f-g-h-ij*k*l*m/+

# Express�es com os operadores bin�rios + - * / e ^
Infixa: a^b^c
Posfixa: abc^^

Infixa: a^b^c*d
Posfixa: abc^^d*

Infixa: a^b^c*d^e
Posfixa: abc^^de^*

Infixa: a+b-c/d^e
Posfixa: ab+cde^/-

Infixa: a*b+c*d^e/f-g*h^i*j
Posfixa: ab*cde^*f/+ghi^*j*-

# Testes com par�nteses
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

# Testes com espa�os em branco
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

# Teste com express�es inv�lidas
# Operando esperado
Infixa: +
Erro:    ^
        Operando esperado nesta posi��o.

Infixa: *
Erro:   ^
        Operando esperado nesta posi��o.

Infixa: (
Erro:    ^
        Operando esperado nesta posi��o.

Infixa: )
Erro:   ^
        Operando esperado nesta posi��o.

Infixa: a-
Erro:     ^
        Operando esperado nesta posi��o.

Infixa:   a  -
Erro:         ^
        Operando esperado nesta posi��o.

Infixa: a--b
Erro:     ^
        Operando esperado nesta posi��o.

Infixa: a - - b
Erro:       ^
        Operando esperado nesta posi��o.

Infixa: a*b/  
Erro:         ^
        Operando esperado nesta posi��o.

Infixa:  a * b/
Erro:          ^
        Operando esperado nesta posi��o.

Infixa: a*b/((c+d)-                
Erro:                              ^
        Operando esperado nesta posi��o.

Infixa: ()
Erro:    ^
        Operando esperado nesta posi��o.

Infixa: a+( )
Erro:       ^
        Operando esperado nesta posi��o.

Infixa: ((((a-b)*c)^d^e)-)
Erro:                    ^
        Operando esperado nesta posi��o.

# Operador esperado
Infixa: ab
Erro:    ^
        Operador esperado nesta posi��o.

Infixa: a      b
Erro:          ^
        Operador esperado nesta posi��o.

Infixa: a*b+c*d^e/f-gh^i*j
Erro:                ^
        Operador esperado nesta posi��o.

Infixa: a+b)+c
Erro:      ^
        Operador esperado nesta posi��o.

Infixa: ((a-b)))+c
Erro:          ^
        Operador esperado nesta posi��o.

# Fecha par�nteses esperado
Infixa: (a-b
Erro:       ^
        Fecha par�ntese esperado nesta posi��o.

Infixa: (((a-b))
Erro:           ^
        Fecha par�ntese esperado nesta posi��o.

Infixa: ((a-b)*(b-c)
Erro:               ^
        Fecha par�ntese esperado nesta posi��o.

Infixa: a*b*c-(e-f
Erro:             ^
        Fecha par�ntese esperado nesta posi��o.

# Caracteres inv�lidos
Infixa: !
Erro:   ^
        Caractere inv�lido nesta posi��o.

Infixa: a;
Erro:    ^
        Caractere inv�lido nesta posi��o.

Infixa: a - b @
Erro:         ^
        Caractere inv�lido nesta posi��o.

Infixa: a%c
Erro:    ^
        Caractere inv�lido nesta posi��o.

# Express�es longas
Infixa: (-(+(-(+(-(+(-(+(-(+(-(+a))))))))))))*(-(+(-(+(-(+(-(+(-(+(-(+a))))))))))))
Posfixa: a&~&~&~&~&~&~a&~&~&~&~&~&~*

Infixa: ((-(+(-(+(-(+(-(+(-(+(-(+a))))))))))))*(-(+(-(+(-(+(-(+(-(+(-(+a))))))))))))+(((((((b))))))))
Posfixa: a&~&~&~&~&~&~a&~&~&~&~&~&~*b+

Infixa: (-(+(-(+(-(+(-(+(-(+(-(+a))))))))))))*(-(+(-(+(-(+(-(+(-(+(-(+a))))))))))))+(-(+(-(+(-(+(-(+(-(+(-(+a))))))))))))/(-(+(-(+(-(+(-(+(-(+(-(+a))))))))))))
Erro:   Cadeia de entrada muito longa.

Infixa: (((((((((((((((((((((((((((((((((((((((a)))))))))))))))))))))))))))))))))))))))/b
Posfixa: ab/

Infixa: (((((((((((((((((((((((((((((((((((((((a)))))))))))))))))))))))))))))))))))))))/(((((((((((((((((((((((((((((((((((((((a)))))))))))))))))))))))))))))))))))))))
Erro:   Cadeia de entrada muito longa.

Infixa:     ##########
Erro:       ^
        Caractere inv�lido nesta posi��o.

Processamento terminado
