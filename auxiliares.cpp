#include "definiciones.h"
#include "auxiliares.h"
#include "gtest/gtest.h"
#include "ejercicios.h"

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
