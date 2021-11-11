#ifndef SOLUCION_AUXILIARES_H
#define SOLUCION_AUXILIARES_H

#include "definiciones.h"

bool esMatriz(vector<vector<dato>> t);

bool esVacia(vector<vector<dato>> t);

bool cantidadCorrectaDeColumnasI(eph_i ti);

bool cantidadCorrectaDeColumnasH(eph_h th);

bool hayIndividuoConCodigo(eph_i ti, int codigo);

bool hayHogarConCodigo(eph_h th, int codigo);

bool hayIndividuosSinHogares(eph_i ti, eph_h th);

bool hayHogaresSinIndividuos(eph_i ti, eph_h th);

bool mismoCodusuYComponente(individuo i1, individuo i2);

bool hayRepetidosI(eph_i ti);

bool hayRepetidosH(eph_h th);

bool mismoAnioYTrimestreI(eph_i &ti, int anio, int trimestre);

bool mismoAnioYTrimestreH(eph_h &th, int anio, int trimestre);

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

int obtenerMaximoHabitacionesEnRegion(eph_h &th, int region);

bool trabaja(individuo i);

bool esDeCiudadGrande(individuo i, eph_h th);

bool esCasaODepartamento(hogar h);

bool suHogarEsCasaODepartamento(individuo i, eph_h th);

bool individuoEnHogarValido(individuo i, eph_h th);

bool realizaSusTareasEnEsteHogar(individuo i);

bool tieneEspaciosReservadosParaElTrabajo(hogar h);

bool suHogarTieneEspaciosReservadosParaElTrabajo(individuo i, eph_h th);

bool trabajaEnSuVivienda(individuo i, eph_h th);

int cantIndividuosQueTrabajan(eph_h th, eph_i ti);

int cantIndividuosTrabajandoEnSuVivienda(eph_h th, eph_i ti);

float proporcionTeleworking(eph_h th, eph_i ti);

bool tieneCasaPropia(hogar h);

bool tieneCasaChica(hogar h, eph_i ti);

int ingresosDelHogar(hogar h, vector<individuo> inds);

vector<hogarIngresos> crearTuplaHogarIngresos(vector<hogar> listaHogares, vector<individuo> listaIndividuos);

void ordenarHogaresPorIngreso(vector<hogarIngresos> &vecHogarIngresos);

vector<hogar> listaConDiferencia(vector<hogarIngresos> vecHogarIngresos, int start, int first, int diferencia);

vector<hogar> buscarMuestraHomogeneaMaxima(vector<hogarIngresos> vecHogarIngresos);

float distanciaEuclideana(pair<int, int> centro, int latitud, int longitud);

bool hogarEnAnillo(hogar hogar, int desde, int hasta, pair<int, int> centro);

int cantidadDeHogaresEnAnillo(eph_h th, int desde, int hasta, pair<int, int> centro);

bool cumpleBusqueda(individuo individuo, vector<pair<int, dato>> busqueda);

int indiceEnTablaHogares(int codusu, eph_h th);

void eliminarHogaresSinIndividuos(eph_i &ti, eph_h &th);

#endif //SOLUCION_AUXILIARES_H
