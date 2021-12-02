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
    bool existe = false;
    for (int j = 0; j < ti.size(); j++) {
        if (codigo == ti[j][ItemInd::INDCODUSU]) {
            existe = true;
        }
    }
    return existe;
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

bool mismoAnioYTrimestreI(eph_i &ti, int anio, int trimestre) {
    for (int i = 0; i < ti.size(); i++) {
        if (ti[i][ItemInd::INDTRIMESTRE] != trimestre || ti[i][ItemInd::INDANIO] != anio) {
            return false;
        }
    }
    return true;
}

bool mismoAnioYTrimestreH(eph_h &th, int anio, int trimestre) {
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
    return mismoAnioYTrimestreI(ti, anio, trimestre) && mismoAnioYTrimestreH(th, anio, trimestre);
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
            && (h[ItemHogar::MAS_500] == 0 || h[ItemHogar::MAS_500] == 1) && h[ItemHogar::IV1] > 0 &&
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

bool realizaSusTareasEnEsteHogar(individuo i) {
    return i[PP04G] == EN_ESTE_HOGAR;
}

bool tieneEspaciosReservadosParaElTrabajo(hogar h) {
    return h[II3] == 1;
}

bool suHogarTieneEspaciosReservadosParaElTrabajo(individuo i, eph_h th) {
    for (int j = 0; j < th.size(); j++) {
        if (esSuHogar(th[j], i) && tieneEspaciosReservadosParaElTrabajo(th[j])) {
            return true;
        }
    }
    return false;
}

int cantIndividuosQueTrabajan(eph_h th, eph_i ti) {
    int suma = 0;
    for (int i = 0; i < ti.size(); i++) {
        if (trabaja(ti[i]) &&
            esDeCiudadGrande(ti[i], th) &&
            suHogarEsCasaODepartamento(ti[i], th)) {
            suma++;
        }
    }
    return suma;
}

int cantIndividuosTrabajandoEnSuVivienda(eph_h th, eph_i ti) {
    int suma = 0;
    for (int i = 0; i < ti.size(); i++) {
        if (trabaja(ti[i]) &&
            realizaSusTareasEnEsteHogar(ti[i]) &&
            suHogarTieneEspaciosReservadosParaElTrabajo(ti[i], th) &&
            esDeCiudadGrande(ti[i], th) &&
            suHogarEsCasaODepartamento(ti[i], th)) {
            suma++;
        }
    }
    return suma;
}

float proporcionTeleworking(eph_h th, eph_i ti) {
    if (cantIndividuosQueTrabajan(th, ti) > 0) {
        return float(cantIndividuosTrabajandoEnSuVivienda(th, ti)) / float(cantIndividuosQueTrabajan(th, ti));
    }
    return 0;
}

// auxiliares ejercicio 5
bool tieneCasaPropia(hogar h) {
    return (h[II7] == 1);
}

bool tieneCasaChica(hogar h, eph_i ti) {
    return cantidadDeHabitantes(h, ti) - 2 > h[II2];
}

// auxiliares ejercicio 7
void swap(vector<vector<dato>> &lista, int i, int j) {
    vector<dato> k = lista[i];
    lista[i] = lista[j];
    lista[j] = k;
}

void burbujeo(vector<vector<dato>> &lista, int i) {
    for (int j = lista.size() - 1; j > i; j--) {
        if (lista[j][REGION] < lista[j - 1][REGION] ||
            (lista[j][REGION] == lista[j - 1][REGION] &&
             lista[j][HOGCODUSU] < lista[j - 1][HOGCODUSU])) {
            swap(lista, j, j - 1);
        }
    }
}

void ordenarHogaresPorRegionYCODUSU(vector<vector<dato>> &lista) {
    for (int i = 0; i < lista.size(); i++) {
        burbujeo(lista, i);
    }
}

void ordenarIndividuosPorComponente(eph_i &ti) {
    for (int i = 0; i < ti.size(); i++) {
        for (int j = i + 1; j <= ti.size() - 1; j++) {
            if ((ti[j][COMPONENTE] < ti[i][COMPONENTE]) && (ti[j][INDCODUSU] == ti[i][INDCODUSU])) {
                swap(ti, i, j);
            }
        }
    }
}

void ordenarIndividuosPorHogar(eph_h &th, eph_i &ti) {
    vector<individuo> res = {};
    for (int i = 0; i < th.size(); i++) {
        vector<individuo> indsDeLaCasa = {};
        for (int j = 0; j < ti.size(); j++) {
            if (esSuHogar(th[i], ti[j])) {
                indsDeLaCasa.push_back(ti[j]);
            }
        }
        for (int j = 0; j < indsDeLaCasa.size(); j++) {
            res.push_back(indsDeLaCasa[j]);
        }
    }
    ti = res;
}

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
        for (int j = i + 1; j <= vecHogarIngresos.size() - 1; j++) {
            if (vecHogarIngresos[j].second < vecHogarIngresos[i].second) {
                hogarIngresos temp = vecHogarIngresos[j];
                vecHogarIngresos[j] = vecHogarIngresos[i];
                vecHogarIngresos[i] = temp;
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
            continue;
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
            if (diferencia > 0) {
                vector<hogar> lista = listaConDiferencia(vecHogarIngresos, i, j, diferencia);
                int largo = lista.size();
                if (largo > largoMaximo) {
                    largoMaximo = largo;
                    res = lista;
                }
            }
        }
    }
    if (largoMaximo < 3) {
        return {};
    }
    return res;
}

// auxiliares ejercicio 10
bool cumpleBusqueda(individuo individuo, vector<pair<int, dato>> busqueda) {
    bool cumpleCondicion = true;
    for (int j = 0; j < busqueda.size(); j++) {
        if (individuo[busqueda[j].first] != busqueda[j].second) {
            cumpleCondicion = false;
        }
    }
    return cumpleCondicion;
}

int indiceEnTablaHogares(int codusu, eph_h th) {
    for (int i = 0; i < th.size(); i++) {
        if (th[i][HOGCODUSU] == codusu) {
            return i;
        }
    }
    return -1;
}

// auxiliares ejercicio 11
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