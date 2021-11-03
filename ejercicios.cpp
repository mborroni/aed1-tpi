#include "ejercicios.h"
#include "auxiliares.h"
#include "definiciones.h"

using namespace std;

// Implementacion Problema 1

bool esEncuestaValida(eph_h th, eph_i ti) {
    bool resp = esValida(th, ti);
    return resp;
}

eph_h obtenerCasasEnRegion(eph_h th, int region) {
    eph_h hogaresEnRegion;
    for (int i = 0; i < th.size(); i++) {
        if (th[i][ItemHogar::REGION] == region && th[i][ItemHogar::IV1] == 1) {
            hogaresEnRegion.push_back(th[i]);
        }
    }
    return hogaresEnRegion;
}

int obtenerMaximoHabitaciones(eph_h &hogares) {
    int maxHabitaciones = 0;
    for (int i = 0; i < hogares.size(); i++) {
        if (hogares[i][ItemHogar::IV2] > maxHabitaciones) {
            maxHabitaciones = hogares[i][ItemHogar::IV2];
        }
    }
    return maxHabitaciones;
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

    vector<pair<int, float>> resp = {make_pair(1, -1.0),
                                     make_pair(40, -1.0),
                                     make_pair(41, -1.0),
                                     make_pair(42, -1.0),
                                     make_pair(43, -1.0),
                                     make_pair(44, -1.0)};
    // TODO

    return resp;
}

// Implementacion Problema 4
bool creceElTeleworkingEnCiudadesGrandes(eph_h t1h, eph_i t1i, eph_h t2h, eph_i t2i) {
    bool resp = false;

    // TODO

    return resp;
}

// Implementacion Problema 5
int costoSubsidioMejora(eph_h th, eph_i ti, int monto) {
    int resp = -1;

    // TODO

    return resp;
}

// Implementacion Problema 6
join_hi generarJoin(eph_h th, eph_i ti) {
    hogar h = {};
    individuo i = {};
    join_hi resp = {make_pair(h, i)};

    // TODO

    return resp;
}

// Implementacion Problema 7
void ordenarRegionYCODUSU(eph_h &th, eph_i &ti) {

    // TODO

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

    // TODO

    return;
}

// Implementacion Problema 10
vector<int> histogramaDeAnillosConcentricos(eph_h th, eph_i ti, pair<int, int> centro, vector<int> distancias) {
    vector<int> resp = {};

    // TODO

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
