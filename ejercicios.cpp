#include "ejercicios.h"
#include "auxiliares.h"
#include "definiciones.h"

using namespace std;

// Implementacion Problema 1
bool esEncuestaValida(eph_h th, eph_i ti) {
    return !esVacia(ti) && !esVacia(th)
    && esMatriz(ti) && esMatriz(th)
    && cantidadCorrectaDeColumnasI(ti) && cantidadCorrectaDeColumnasH(th)
    && !hayIndividuosSinHogares(ti, th) && !hayHogaresSinIndividuos(ti, th)
    && !hayRepetidosI(ti) && !hayRepetidosH(th) && mismoAnioYTrimestre(ti, th)
    && menosDe21MiembrosPorHogar(th, ti) && cantidadValidaDormitorios(th)
    && valoresEnRangoI(ti) && valoresEnRangoH(th);
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

    for (int i = 0; i < CANTIDAD_DE_REGIONES; i++) {
        float casasConHC = 0;
        float hogaresValidos = 0;
        for (int j = 0; j < th.size(); j++) {
            if (th[j][IV1] == CASA && th[j][REGION] == resp[i].first && th[j][MAS_500] == 0) {
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
void ordenarRegionYCODUSU(eph_h &th, eph_i &ti) {
    ordenarHogaresPorRegionYCODUSU(th);

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
pair<eph_h, eph_i> quitarIndividuos(eph_i &ti, eph_h &th, vector<pair<int, dato>> busqueda) {
    eph_h rth = {};
    eph_i rti = {};

    eph_i ti0 = ti;
    eph_h th0 = th;
    ti = {};
    th = {};

    for (int i = 0; i < ti0.size(); i++) {
        if (cumpleBusqueda(ti0[i], busqueda)) {
            // si todavía no agregamos el hogar a res
            if (indiceEnTablaHogares(ti0[i][INDCODUSU], rth) == -1) {
                rth.push_back(th0[indiceEnTablaHogares(ti0[i][INDCODUSU], th0)]);
            }

            // agrego el individuo a res
            rti.push_back(ti0[i]);
        } else {
            // Dejo en ti original al individuo
            ti.push_back(ti0[i]);

            // Y dejo su hogar
            if (indiceEnTablaHogares(ti0[i][INDCODUSU], th) == -1) {
                th.push_back(th0[indiceEnTablaHogares(ti0[i][INDCODUSU], th0)]);
            }
        }
    }

    pair<eph_h, eph_i> resp = make_pair(rth, rti);

    return resp;
}

// Implementacion Problema 11
vector<int> histogramaDeAnillosConcentricos(eph_h th, eph_i ti, pair<int, int> centro, vector<int> distancias) {
    vector<int> resp = {};
    resp.push_back(cantidadDeHogaresEnAnillo(th, 0, distancias[0], centro));
    for (int i = 0; i < distancias.size() - 1; i++) {
        int hogaresEnAnillo = cantidadDeHogaresEnAnillo(th, distancias[i], distancias[i + 1], centro);
        resp.push_back(hogaresEnAnillo);
    }
    return resp;

}
