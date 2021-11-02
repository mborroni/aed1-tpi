#ifndef SOLUCION_AUXILIARES_H
#define SOLUCION_AUXILIARES_H

#include "definiciones.h"

bool esMatriz(vector<vector<dato>> t);

bool individuoEnTabla(individuo ind, eph_i ti);

bool hogarEnTabla(hogar h, eph_h th);

bool esVacia(vector<vector<dato>> t);

int cantidadItemsIndividuo();

int cantidadItemsHogar();

bool cantidadCorrectaDeColumnasI(eph_i ti);

bool cantidadCorrectaDeColumnasH(eph_h th);

bool hayIndividuoConCodigo(eph_i ti, int codigo);

bool hayHogarConCodigo(eph_h th, int codigo);

bool hayIndividuosSinHogares(eph_i ti, eph_h th);

bool hayHogaresSinIndividuos(eph_i ti, eph_h th);

bool mismoCodusuYComponente(individuo i1, individuo i2);

bool hayRepetidosI(eph_i ti);

bool hayRepetidosH(eph_h th);

bool mismoAnioYTrimestreI(eph_i ti, int anio, int trimestre);

bool mismoAnioYTrimestreH(eph_h th, int anio, int trimestre);

bool mismoAnioYTrimestre(eph_i ti, eph_h th);

bool esSuHogar(hogar h, individuo i);

int cantidadDeHabitantes(hogar h, eph_i ti);

bool menosDe21MiembrosPorHogar(eph_h th, eph_i ti);

bool cantidadValidaDormitorios(eph_h th);

bool individuoValido(individuo i);

bool valoresEnRangoI(eph_i ti);

bool valorRegionValido(int r);

bool hogarValido(hogar h);

bool valoresEnRangoH(eph_h th);

bool esValida(eph_h th, eph_i ti);

#endif //SOLUCION_AUXILIARES_H
