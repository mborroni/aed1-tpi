#include "ejercicios.h"
#include "auxiliares.h"
#include "definiciones.h"
#include <math.h>

using namespace std;

// Implementacion Problema 1

bool esEncuestaValida(eph_h th, eph_i ti) {
    bool resp = esValida(th, ti);
    return resp;
}

// Implementacion Problema 2
vector<int> histHabitacional(eph_h th, eph_i ti, int region) {
    eph_h hogaresEnRegion = obtenerCasasEnRegion(th, region);

    int maxHabitaciones = obtenerMaximoHabitaciones(hogaresEnRegion);

    vector<int> resultado(maxHabitaciones, 0);
    for (int i = 0; i < hogaresEnRegion.size(); i++) {
        resultado[hogaresEnRegion[i][ItemHogar::IV2] - 1]++;
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

    int casasConHC = 0;
    int hogaresValidos = 0;

    for (int i = 1; i < resp.size(); i++) {
        for (int j = 0; j < th.size(); j++) {
            if (th[j][ItemHogar::IV1] == 1 && th[j][ItemHogar::REGION] == resp[i].first &&
                th[j][ItemHogar::MAS_500] == 0) {
                hogaresValidos++;
                if (cantidadDeHabitantes(th[j], ti) > 3 * th[j][ItemHogar::II2]) {
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
    return (i[ItemInd::ESTADO] == 1);
}

bool esDeCiudadGrande(individuo i, eph_h th) {
    for (int j = 0; j < th.size(); j++) {
        if (esSuHogar(th[j], i) && th[j][ItemHogar::MAS_500] == 1) {
            return true;
        }
    }
    return false;
}

bool esCasaODepartamento(hogar h) {
    return (h[ItemHogar::IV1] == 1 || h[ItemHogar::IV1] == 2);
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
    return (i[ItemInd::PP04G] == 6);
}

bool tieneEspaciosReservadosParaElTrabajo(hogar h) {
    return (h[ItemHogar::II3] == 1);
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
    return (h[ItemHogar::II7] == 1);
}

bool tieneCasaChica(hogar h, eph_i ti) {
    return ((cantidadDeHabitantes(h, ti) - 2) > h[ItemHogar::II2]);
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

void swap(vector<vector<dato>> &lista, int i, int j) {
    vector<dato> k = lista[i];
    lista[i] = lista[j];
    lista[j] = k;
}


void burbujeo(vector<vector<dato>> &lista, int i) {
    for (int j = lista.size() - 1; j > i; j--) {
        if (lista[j] < lista[j - 1]) {
            swap(lista, j, j - 1);
        }
    }
}

vector<vector<dato>> bubbleSort(vector<vector<dato>> lista) {
    for (int i = 0; i < lista.size(); i++) {
        burbujeo(lista, i);
    }
    return lista;
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
        if (lista[j][ItemHogar::REGION] < lista[j - 1][ItemHogar::REGION] ||
        (lista[j][ItemHogar::REGION] == lista[j - 1][ItemHogar::REGION] &&
        lista[j][ItemHogar::HOGCODUSU] < lista[j - 1][ItemHogar::HOGCODUSU])) {
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


void ordenarRegionYCODUSU(eph_h &th, eph_i &ti) {
    bubbleSort(th);

        return;
    }




// Implementacion Problema 8
    vector<hogar> muestraHomogenea(eph_h &th, eph_i &ti) {
        hogar h = {};
        vector<hogar> resp = {h};

        // TODO

        return resp;
    }

// Implementacion Problema 9
    void corregirRegion(eph_h &th, eph_i ti) {
        for (int i = 0; i < th.size(); i++) {
            if (th[i][ItemHogar::REGION] == 1) {
                th[i][ItemHogar::REGION] = 43;
            }
        }
    }

// Implementacion Problema 10
    float distanciaEuclideana(pair<int, int> centro, int latitud, int longitud) {
        return sqrt(pow((centro.first - latitud), 2) + pow(centro.second - longitud, 2));
    }

    bool hogarEnAnillo(hogar hogar, int desde, int hasta, pair<int, int> centro) {
        float distancia = distanciaEuclideana(centro, hogar[ItemHogar::HOGLATITUD], hogar[ItemHogar::HOGLONGITUD]);
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

// Implementacion Problema 11
    pair<eph_h, eph_i> quitarIndividuos(eph_i &ti, eph_h &th, vector<pair<int, dato> > busqueda) {
        eph_h rth = {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};
        eph_i rti = {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};
        pair<eph_h, eph_i> resp = make_pair(rth, rti);

        // TODO

        return resp;
    }
