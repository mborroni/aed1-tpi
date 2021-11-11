#include "definiciones.h"
#include "auxiliares.h"
#include "gtest/gtest.h"
#include "ejercicios.h"

bool esMatriz(vector<vector<dato>> t) {
    for (int i = 0; i < t.size() - 1; i++) {
        if (t[i].size() != t[i + 1].size()) {
            return false;
        }
    }
    return true;
}

bool esVacia(vector<vector<dato>> t) {
    return (t.size() == 0);
}

bool cantidadCorrectaDeColumnasI(eph_i ti) {
    for (int i = 0; i < ti.size(); i++) {
        if (ti[i].size() != FILAS_INDIVIDUO) {
            return false;
        }
    }
    return true;
}

bool cantidadCorrectaDeColumnasH(eph_h th) {
    for (int i = 0; i < th.size(); i++) {
        if (th[i].size() != FILAS_HOGAR) {
            return false;
        }
    }
    return true;
}

bool hayIndividuoConCodigo(eph_i ti, int codigo) {
    for (int j = 0; j < ti.size(); j++) {
        if (codigo == ti[j][ItemInd::INDCODUSU]) {
            return true;
        }
    }
    return false;
}

bool hayHogarConCodigo(eph_h th, int codigo) {
    for (int j = 0; j < th.size(); j++) {
        if (codigo == th[j][ItemHogar::HOGCODUSU]) {
            return true;
        }
    }
    return false;
}

bool hayIndividuosSinHogares(eph_i ti, eph_h th) {
    for (int i = 0; i < ti.size(); i++) {
        if (!hayHogarConCodigo(th, ti[i][ItemInd::INDCODUSU])) {
            return true;
        }
    }
    return false;
}

bool hayHogaresSinIndividuos(eph_i ti, eph_h th) {
    for (int i = 0; i < th.size(); i++) {
        if (!hayIndividuoConCodigo(ti, th[i][ItemHogar::HOGCODUSU])) {
            return true;
        }
    }
    return false;
}

bool mismoCodusuYComponente(individuo i1, individuo i2) {
    return (i1[ItemInd::INDCODUSU] == i2[ItemInd::INDCODUSU] && i1[ItemInd::COMPONENTE] == i2[ItemInd::COMPONENTE]);
}

bool hayRepetidosI(eph_i ti) {
    for (int i = 0; i < ti.size(); i++) {
        for (int j = i + 1; j < ti.size(); j++) {
            if (mismoCodusuYComponente(ti[j], ti[i])) {
                return true;
            }
        }
    }
    return false;
}

bool hayRepetidosH(eph_h th) {
    for (int i = 0; i < th.size(); i++) {
        for (int j = i + 1; j < th.size(); j++) {
            if (th[i][ItemHogar::HOGCODUSU] == th[j][ItemHogar::HOGCODUSU]) {
                return true;
            }
        }
    }
    return false;
}

bool mismoAnioYTrimestreI(eph_i ti, int anio, int trimestre) {
    for (int i = 0; i < ti.size(); i++) {
        if (ti[i][ItemInd::INDTRIMESTRE] != trimestre || ti[i][ItemInd::INDANIO] != anio) {
            return false;
        }
    }
    return true;
}

bool mismoAnioYTrimestreH(eph_h th, int anio, int trimestre) {
    for (int i = 0; i < th.size(); i++) {
        if (th[i][ItemHogar::HOGTRIMESTRE] != trimestre || th[i][ItemHogar::HOGANIO] != anio) {
            return false;
        }
    }
    return true;
}

bool mismoAnioYTrimestre(eph_i ti, eph_h th) {
    int anio = ti[0][ItemInd::INDANIO];
    int trimestre = ti[0][ItemInd::INDTRIMESTRE];
    return (mismoAnioYTrimestreI(ti, anio, trimestre) && mismoAnioYTrimestreH(th, anio, trimestre));
}

bool esSuHogar(hogar h, individuo i) {
    return h[ItemHogar::HOGCODUSU] == i[ItemInd::INDCODUSU];
}

int cantidadDeHabitantes(hogar h, eph_i ti) {
    int habitantes = 0;
    for (int i = 0; i < ti.size(); i++) {
        if (esSuHogar(h, ti[i])) {
            habitantes++;
        }
    }
    return habitantes;
}

bool menosDe21MiembrosPorHogar(eph_h th, eph_i ti) {
    for (int i = 0; i < th.size(); i++) {
        if (cantidadDeHabitantes(th[i], ti) > 20) {
            return false;
        }
    }
    return true;
}

bool cantidadValidaDormitorios(eph_h th) {
    for (int i = 0; i < th.size(); i++) {
        if (th[i][IV2] < th[i][II2]) {
            return false;
        }
    }
    return true;
}

bool individuoValido(individuo i) {
    return (i[ItemInd::INDCODUSU] > 0 && i[ItemInd::COMPONENTE] > 0 && i[ItemInd::INDTRIMESTRE] <= 4
            && i[ItemInd::INDTRIMESTRE] > 0 && i[ItemInd::CH4] > 0 && i[ItemInd::CH4] <= 2 && i[ItemInd::CH6] >= 0
            && (i[ItemInd::NIVEL_ED] == 0 || i[ItemInd::NIVEL_ED] == 1) && i[ItemInd::ESTADO] >= -1 &&
            i[ItemInd::ESTADO] <= 1
            && i[ItemInd::CAT_OCUP] >= 0 && i[ItemInd::CAT_OCUP] <= 4 &&
            (i[ItemInd::p47T] >= 0 || i[ItemInd::p47T] == -1) &&
            i[ItemInd::PP04G] >= 0 && i[ItemInd::PP04G] <= 10);
}

bool valoresEnRangoI(eph_i ti) {
    for (int i = 0; i < ti.size(); i++) {
        if (!individuoValido(ti[i])) {
            return false;
        }
    }
    return true;
}

bool valorRegionValido(int region) {
    return (region == 1 || (region >= 40 && region <= 44));
}

bool hogarValido(hogar h) {
    return (h[ItemHogar::HOGCODUSU] > 0 &&
            h[ItemHogar::HOGTRIMESTRE] > 0 &&
            h[ItemHogar::HOGTRIMESTRE] <= 4 &&
            h[ItemHogar::II7] > 0 && h[ItemHogar::II7] <= 3 &&
            valorRegionValido(h[ItemHogar::REGION])
            && (h[ItemHogar::MAS_500] == 0 || h[ItemHogar::MAS_500 == 1]) && h[ItemHogar::IV1] > 0 &&
            h[ItemHogar::IV1] <= 5
            && h[ItemHogar::IV2] > 0 && h[ItemHogar::II2] >= 1 && (h[ItemHogar::II3] == 1 || h[ItemHogar::II3] == 2));
}

bool valoresEnRangoH(eph_h th) {
    for (int i = 0; i < th.size(); i++) {
        if (!hogarValido(th[i])) {
            return false;
        }
    }
    return true;
}

bool esValida(eph_h th, eph_i ti) {
    return (!esVacia(ti) && !esVacia(th) && esMatriz(ti) && esMatriz(th)
            && cantidadCorrectaDeColumnasI(ti) && cantidadCorrectaDeColumnasH(th)
            && !hayIndividuosSinHogares(ti, th) && !hayHogaresSinIndividuos(ti, th)
            && !hayRepetidosI(ti) && !hayRepetidosH(th) && mismoAnioYTrimestre(ti, th)
            && menosDe21MiembrosPorHogar(th, ti) && cantidadValidaDormitorios(th)
            && valoresEnRangoI(ti) && valoresEnRangoH(th));
}

// auxiliares ejercicio 2
int obtenerMaximoHabitacionesEnRegion(eph_h &th, int region) {
    int maxHabitaciones = 0;
    for (int i = 0; i < th.size(); i++) {
        if (th[i][REGION] == region && th[i][IV2] >= maxHabitaciones) {
            maxHabitaciones = th[i][IV2];
        }
    }
    return maxHabitaciones;
}

// auxiliares ejercicio 3


// auxiliares ejercicio 4
bool trabaja(individuo i) {
    return (i[ESTADO] == OCUPADO);
}

bool esDeCiudadGrande(individuo i, eph_h th) {
    for (int j = 0; j < th.size(); j++) {
        if (esSuHogar(th[j], i) && th[j][MAS_500] == 1) {
            return true;
        }
    }
    return false;
}

bool esCasaODepartamento(hogar h) {
    return (h[IV1] == CASA || h[IV1] == DEPARTAMENTO);
}

bool suHogarEsCasaODepartamento(individuo i, eph_h th) {
    for (int j = 0; j < th.size(); j++) {
        if (esSuHogar(th[j], i) && esCasaODepartamento(th[j])) {
            return true;
        }
    }
    return false;
}

bool individuoEnHogarValido(individuo i, eph_h th) {
    bool res = (esDeCiudadGrande(i, th) && suHogarEsCasaODepartamento(i, th));
    return (res);
}

bool realizaSusTareasEnEsteHogar(individuo i) {
    return (i[PP04G] == 6);
}

bool tieneEspaciosReservadosParaElTrabajo(hogar h) {
    return (h[II3] == 1);
}

bool suHogarTieneEspaciosReservadosParaElTrabajo(individuo i, eph_h th) {
    for (int j = 0; j < th.size(); j++) {
        if (esSuHogar(th[j], i) && tieneEspaciosReservadosParaElTrabajo(th[j])) {
            return true;
        }
    }
    return false;
}


bool trabajaEnSuVivienda(individuo i, eph_h th) {
    return (realizaSusTareasEnEsteHogar(i) && suHogarTieneEspaciosReservadosParaElTrabajo(i, th));
}

int cantIndividuosQueTrabajan(eph_h th, eph_i ti) {
    int suma = 0;
    for (int i = 0; i < ti.size(); i++) {
        if (trabaja(ti[i]) && individuoEnHogarValido(ti[i], th)) {
            suma++;
        }
    }
    return suma;
}

int cantIndividuosTrabajandoEnSuVivienda(eph_h th, eph_i ti) {
    int suma = 0;
    for (int i = 0; i < ti.size(); i++) {
        if (trabaja(ti[i]) && trabajaEnSuVivienda(ti[i], th) && individuoEnHogarValido(ti[i], th)) {
            suma++;
        }
    }
    return suma;
}

float proporcionTeleworking(eph_h th, eph_i ti) {
    if (cantIndividuosQueTrabajan(th, ti) > 0) {
        float res = float(cantIndividuosTrabajandoEnSuVivienda(th, ti)) / float(cantIndividuosQueTrabajan(th, ti));
        return (res);
    } else {
        return 0;
    }
}

// auxiliares ejercicio 5
bool tieneCasaPropia(hogar h) {
    return (h[II7] == 1);
}

bool tieneCasaChica(hogar h, eph_i ti) {
    return ((cantidadDeHabitantes(h, ti) - 2) > h[II2]);
}

// auxiliares ejercicio 6

// auxiliares ejercicio 7

// auxiliares ejercicio 8
int ingresosDelHogar(hogar h, vector<individuo> inds) {
    int suma = 0;
    for (int i = 0; i < inds.size(); i++) {
        if (esSuHogar(h, inds[i]) && inds[i][p47T] != -1) {
            suma += inds[i][p47T];
        }
    }
    return suma;
}

vector<hogarIngresos> crearTuplaHogarIngresos(vector<hogar> listaHogares, vector<individuo> listaIndividuos) {
    vector<hogarIngresos> res = {};
    for (int i = 0; i < listaHogares.size(); i++) {
        hogarIngresos p = make_pair(listaHogares[i], ingresosDelHogar(listaHogares[i], listaIndividuos));
        res.push_back(p);
    }
    return res;
}

void ordenarHogaresPorIngreso(vector<hogarIngresos> &vecHogarIngresos) {
    for (int i = 0; i < vecHogarIngresos.size(); i++) {
        for (int j = i; j < vecHogarIngresos.size() - 1; j++) {
            if (vecHogarIngresos[j].second > vecHogarIngresos[j + 1].second) {
                hogarIngresos temp = vecHogarIngresos[j];
                vecHogarIngresos[j] = vecHogarIngresos[j + 1];
                vecHogarIngresos[j + 1] = temp;
            }
        }
    }
}

vector<hogar> listaConDiferencia(vector<hogarIngresos> vecHogarIngresos, int start, int first, int diferencia) {
    vector<hogar> res = {};
    res.push_back(vecHogarIngresos[start].first);
    res.push_back(vecHogarIngresos[first].first);
    int last = first;
    for (int i = first + 1; i < vecHogarIngresos.size(); i++) {
        int dif = vecHogarIngresos[i].second - vecHogarIngresos[last].second;
        if (dif < diferencia) {
            continue;
        }
        if (dif == diferencia) {
            res.push_back(vecHogarIngresos[i].first);
            last = i;
        }
        if (dif > diferencia) {
            break;
        }
    }
    return res;
}

vector<hogar> buscarMuestraHomogeneaMaxima(vector<hogarIngresos> vecHogarIngresos) {
    vector<hogar> res;
    int largoMaximo = 0;
    for (int i = 0; i < vecHogarIngresos.size() - 1; i++) {
        for (int j = i + 1; j < vecHogarIngresos.size(); j++) { // Vemos todas las posibles diferencias de ingresos
            int diferencia = vecHogarIngresos[j].second - vecHogarIngresos[i].second;
            vector<hogar> lista = listaConDiferencia(vecHogarIngresos, i, j, diferencia);
            int largo = lista.size();
            if (largo > largoMaximo) {
                largoMaximo = largo;
                res = lista;
            }
        }
    }
    if (largoMaximo < 3) {
        return {};
    }
    return res;
}

// auxiliares ejercicio 10
float distanciaEuclideana(pair<int, int> centro, int latitud, int longitud) {
    return sqrt(pow((centro.first - latitud), 2) + pow(centro.second - longitud, 2));
}

bool hogarEnAnillo(hogar hogar, int desde, int hasta, pair<int, int> centro) {
    float distancia = distanciaEuclideana(centro, hogar[HOGLATITUD], hogar[HOGLONGITUD]);
    return float(desde) < distancia && distancia <= float(hasta);
}

int cantidadDeHogaresEnAnillo(eph_h th, int desde, int hasta, pair<int, int> centro) {
    int cantidadHogares = 0;
    for (int i = 0; i < th.size(); i++) {
        if (hogarEnAnillo(th[i], desde, hasta, centro)) {
            cantidadHogares++;
        }
    }
    return cantidadHogares;
}

// auxiliares ejercicio 11
bool cumpleBusqueda(individuo individuo, vector<pair<int, dato>> busqueda) {
    bool cumpleCondicion = true;
    for (int j = 0; j < busqueda.size(); j++) {
        if (individuo[busqueda[j].first] != busqueda[j].second) {
            cumpleCondicion = false;
        }
    }
    return cumpleCondicion;
}

// Implementacion Problema 11
int indiceEnTablaHogares(int codusu, eph_h th) {
    for (int i = 0; i < th.size(); i++) {
        if (th[i][HOGCODUSU] == codusu) {
            return i;
        }
    }
    return -1;
}

void eliminarHogaresSinIndividuos(eph_i &ti, eph_h &th) {
    eph_h th0 = th;
    int eliminados = 0;
    for (int i = 0; i < th0.size(); i++) {
        if (cantidadDeHabitantes(th0[i], ti) == 0) {
            th.erase(th.begin() + i - eliminados);
            eliminados++;
        }
    }
}
