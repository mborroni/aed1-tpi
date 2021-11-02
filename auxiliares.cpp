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

bool individuoEnTabla(individuo ind, eph_i ti) {
    for (int i = 0; i < ti.size(); i++) {
        if (ti[i] == ind) {
            return true;
        }
    }
    return false;
}

bool hogarEnTabla(hogar h, eph_h th) {
    for (int i = 0; i < th.size(); i++) {
        if (th[i] == h) {
            return true;
        }
    }
    return false;
}

bool esVacia(vector<vector<dato>> t) {
    return (t.size() == 0);
}

int cantidadItemsIndividuo() {
    return 11;
}

int cantidadItemsHogar() {
    return 12;
}

bool cantidadCorrectaDeColumnasI(eph_i ti) {
    for (int i = 0; i < ti.size(); i++) {
        if (ti[i].size() != cantidadItemsIndividuo()) {
            return false;
        }
    }
    return true;
}

bool cantidadCorrectaDeColumnasH(eph_h th) {
    for (int i = 0; i < th.size(); i++) {
        if (th[i].size() != cantidadItemsHogar()) {
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
        if (th[i][ItemHogar::IV2] < th[i][ItemHogar::II2]) {
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
    return (h[ItemHogar::HOGCODUSU] > 0 && h[ItemHogar::HOGTRIMESTRE] > 0 && h[ItemHogar::HOGTRIMESTRE] <= 4
            && h[ItemHogar::II7] > 0 && h[ItemHogar::II7] <= 3 && valorRegionValido(h[ItemHogar::REGION])
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
