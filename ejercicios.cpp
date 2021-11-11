#include "ejercicios.h"
#include "auxiliares.h"
#include "definiciones.h"

using namespace std;

// Implementacion Problema 1
bool esEncuestaValida(eph_h th, eph_i ti) {
    return esValida(th, ti);
}

// Implementacion Problema 2
vector<int> histHabitacional(eph_h th, eph_i ti, int region) {
    int maxHabitaciones = obtenerMaximoHabitacionesEnRegion(th, region);
    vector<int> resultado(maxHabitaciones, 0);
    for (int i = 0; i < th.size(); i++) {
        if (th[i][REGION] == region && th[i][IV1] == CASA) {
            resultado[th[i][IV2] - 1]++;
        }
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
bool creceElTeleworkingEnCiudadesGrandes(eph_h t1h, eph_i t1i, eph_h t2h, eph_i t2i) {
    return proporcionTeleworking(t2h, t2i) > proporcionTeleworking(t1h, t1i);
}

// Implementacion Problema 5
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
}

void ordenarIndividuosPorComponente(eph_i &ti) {
    for (int i = 0; i < ti.size(); i++) {
        for (int j = i + 1; j < ti.size() - 1; j++) {
            if (ti[j][COMPONENTE] < ti[i][COMPONENTE]) {
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

void ordenarRegionYCODUSU(eph_h &th, eph_i &ti) {
    bubbleSort(th);

    ordenarIndividuosPorComponente(ti);
    ordenarIndividuosPorHogar(th, ti);
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
