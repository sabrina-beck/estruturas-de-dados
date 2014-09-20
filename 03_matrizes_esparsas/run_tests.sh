#!/bin/bash
set -e

usage () {
	echo "/******************************************************************/"
	echo "Instruções: "
	echo "	1.Coloque esse script no diretório que contem os arquivos de teste."
	echo "	2.O padrão de nomeação dos arquivos de teste deve ser arqXX.in (entrada) e arqXX.res (saída esperada)."
	echo "	3.O padrão de nomeação do arquivo de código é labXX.c."
	echo "	4.O primeiro parametro deve ser o número do lab."
	echo "	5.O segundo parametro deve ser o número de testes a serem rodados."
	echo "	6.A saída será a diferença entre os arquivos de saída gerados pelo programa no padrão arqXX.out e os arquivos arqXX.res."
	echo
	echo "Exemplo: sh run_tests.sh 1 20"
	echo "/******************************************************************/"
	exit 0
}

if test $# -lt 2; then
	usage
fi

if test $1 -lt 10; then
	nomeLab=lab0$1
else
	nomeLab=lab$1
fi

gcc -Wall -Werror -ansi -pedantic -std=c99 $nomeLab.c matrizes.c balloc.c -o $nomeLab.exe

if test $2 -gt 0; then
	echo "Analise dos arquivos de saida"
fi

for i in $(seq 01 $2)
do
	if test $i -lt 10; then
		nomeArq=arq0$i
	else
		nomeArq=arq$i
	fi
	./$nomeLab.exe < $nomeArq.in > $nomeArq.out
	echo
	echo "/*********** arq0$i.out : arq0$i.res ***********/"
	diff $nomeArq.out $nomeArq.res
	echo
	echo "/* Terminou analise do arq0$i */"
	echo
done
