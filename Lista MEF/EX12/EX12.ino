/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Exercício 12, Resfriadora de Peças (MEF)

Autor: Augusto Bredlau Pinz
Data: 14/06/2026
Versão: 1.0

************************************************************************ */

const int EstadoAguardandoStart = 0;
const int EstadoAvancandoC1 = 1;
const int EstadoMovendoAteS2 = 2;
const int EstadoResfriando = 3;
const int EstadoMovendoAteS3 = 4;