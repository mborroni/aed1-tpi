#include "ejercicios.h"
#include "auxiliares.h"
#include "definiciones.h"
#include <math.h>

using namespace std;

// Implementacion Problema 1
bool esEncuestaValida(eph_h th, eph_i ti) {
    return esValida(th, ti);
}

// Implementacion Problema 2
vector<int> histHabitacional(eph_h th, eph_i ti, int region) {
    eph_h hogaresEnRegion = obtenerCasasEnRegion(th, region);

    int maxHabitaciones = obtenerMaximoHabitaciones(hogaresEnRegion);

    vector<int> resultado(maxHabitaciones, 0);
    for (int i = 0; i < hogaresEnRegion.size(); i++) {
        resultado[hogaresEnRegion[i][IV2] - 1]++;
    }
    return resultado;
}

// Implementacion Problema 3
vector<pair<int, float> > laCasaEstaQuedandoChica(eph_h th, eph_i ti) {
    vector<pair<int, float>> resp = {make_pair(1, 0.0),
                                     make_pair(40, 0.0),
                                     make_pair(41, 0.0),
                                     make_pair(42, 0.0),
                                     make_pair(43, 0.0),
                                     make_pair(44, 0.0)};

    float casasConHC = 0;
    float hogaresValidos = 0;

    for (int i = 0; i < CANTIDAD_DE_REGIONES; i++) {
        for (int j = 0; j < th.size(); j++) {
            if (th[j][IV1] == CASA &&
                th[j][REGION] == resp[i].first &&
                th[j][MAS_500] == 0) {
                hogaresValidos++;
                if (cantidadDeHabitantes(th[j], ti) > 3 * th[j][II2]) {
                    casasConHC++;
                }
            }
        }
        if (hogaresValidos > 0) {
            resp[i].second = casasConHC / hogaresValidos;
        }
    }
    return resp;
}

// Implementacion Problema 4
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

bool creceElTeleworkingEnCiudadesGrandes(eph_h t1h, eph_i t1i, eph_h t2h, eph_i t2i) {
    bool resp = false;
    resp = (proporcionTeleworking(t2h, t2i) > proporcionTeleworking(t1h, t1i));
    return resp;
}

// Implementacion Problema 5
bool tieneCasaPropia(hogar h) {
    return (h[II7] == 1);
}

bool tieneCasaChica(hogar h, eph_i ti) {
    return ((cantidadDeHabitantes(h, ti) - 2) > h[II2]);
}

int costoSubsidioMejora(eph_h th, eph_i ti, int monto) {
    int resp = 0;
    for (int i = 0; i < th.size(); i++) {
        if (tieneCasaPropia(th[i]) && tieneCasaChica(th[i], ti)) {
            resp += monto;
        }
    }
    return resp;
}

// Implementacion Problema 6
join_hi generarJoin(eph_h th, eph_i ti) {
    join_hi resp = {};
    for (int i = 0; i < ti.size(); i++) {
        for (int j = 0; j < th.size(); j++) {
            if (esSuHogar(ti[i], th[j])) {
                resp.push_back(make_pair(th[j], ti[i]));
            }
        }
    }
    return resp;
}

// Implementacion Problema 7

//bubble sort
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

void bubbleSort(vector<vector<dato>> &lista) {
    for (int i = 0; i < lista.size(); i++) {
        burbujeo(lista, i);
    }
    return;
}

void ordenarIndividuosPorComponente(eph_i &ti) {
    for(int i = 0; i < ti.size(); i++) {
        for(int j = i+1; j < ti.size() - 1; j++) {
            if(ti[j][COMPONENTE] < ti[i][COMPONENTE]) {
                swap(ti, i, j);
            }
        }
    }
}

void ordenarIndividuosPorHogar(eph_h &th, eph_i &ti) {
    vector<individuo> res = {};
    for(int i = 0; i < th.size(); i++) {
        vector<individuo> indsDeLaCasa = {};
        for(int j = 0; j < ti.size(); j++) {
            if(esSuHogar(th[i], ti[j])) {
                indsDeLaCasa.push_back(ti[j]);
            }
        }
        for(int j = 0; j < indsDeLaCasa.size(); j++) {
            res.push_back(indsDeLaCasa[i]);
        }
    }
    ti = res;
}

void ordenarRegionYCODUSU(eph_h &th, eph_i &ti) {
    bubbleSort(th);

    ordenarIndividuosPorHogar(th, ti);
    ordenarIndividuosPorComponente(ti);
    return;
}

// AUXILIARES 8
typedef pair<hogar, int> hogarIngresos;

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

// Implementacion Problema 8
vector<hogar> muestraHomogenea(eph_h &th, eph_i &ti) {
    vector<hogarIngresos> tmp = crearTuplaHogarIngresos(th, ti);
    ordenarHogaresPorIngreso(tmp);
    vector<hogar> resp = buscarMuestraHomogeneaMaxima(tmp);
    return resp;
}

// Implementacion Problema 9
void corregirRegion(eph_h &th, eph_i ti) {
    for (int i = 0; i < th.size(); i++) {
        if (th[i][REGION] == GBA) {
            th[i][REGION] = PAMPEANA;
        }
    }
}

// Implementacion Problema 10
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

vector<int> histogramaDeAnillosConcentricos(eph_h th, eph_i ti, pair<int, int> centro, vector<int> distancias) {
    vector<int> resp = {};
    resp.push_back(cantidadDeHogaresEnAnillo(th, 0, distancias[0], centro));
    for (int i = 0; i < distancias.size() - 1; i++) {
        int hogaresEnAnillo = cantidadDeHogaresEnAnillo(th, distancias[i], distancias[i + 1], centro);
        resp.push_back(hogaresEnAnillo);
    }
    return resp;

}

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

pair<eph_h, eph_i> quitarIndividuos(eph_i &ti, eph_h &th, vector<pair<int, dato>> busqueda) {
    eph_h rth = {};
    eph_i rti = {};

    eph_i ti0 = ti;

    for (int i = 0; i < ti0.size(); i++) {
        if (cumpleBusqueda(ti0[i], busqueda)) {
            // si todavía no agregamos el hogar a res
            if (indiceEnTablaHogares(ti0[i][INDCODUSU], rth) == -1) {
                rth.push_back(th[indiceEnTablaHogares(ti0[i][INDCODUSU], th)]);
            }

            // agrego el individuo a res
            rti.push_back(ti0[i]);
            // borro del ti original al individuo
            ti.erase(ti.begin() + i - rti.size() + 1);
        }
    }
    eliminarHogaresSinIndividuos(ti, th);

    pair<eph_h, eph_i> resp = make_pair(rth, rti);

    return resp;
}
