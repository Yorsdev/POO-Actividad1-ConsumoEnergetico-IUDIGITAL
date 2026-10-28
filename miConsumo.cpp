/*
 * =====================================================================
 * PROGRAMA: MiConsumo - Consumo de energia en el hogar
 * CURSO:    Programacion Orientada a Objetos - IU Digital - 2026-2
 * EVIDENCIA: EA1. Programa orientado a objetos con vectores y matrices
 * NOMBRE: Jorge Andrés González Foronda
 * =====================================================================
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int DIAS = 7;
const int MAX_EQUIPOS = 4;

const string NOMBRE_DIA[DIAS] = {"Lun", "Mar", "Mie", "Jue", "Vie", "Sab", "Dom"};

class Equipo
{
private:
    string nombre;
    float potenciaW;
    float horas[DIAS];

public:
    Equipo()
    {
        nombre = "";
        potenciaW = 0;
        for (int d = 0; d < DIAS; d++)
        {
            horas[d] = 0;
        }
    }

    Equipo(string n, float p, const float h[DIAS])
    {
        nombre = n;
        potenciaW = p;
        for (int d = 0; d < DIAS; d++)
        {
            horas[d] = h[d];
        }
    }

    string getNombre()
    {
        return nombre;
    }

    float getPotenciaW()
    {
        return potenciaW;
    }

    void mostrar()
    {
        cout << nombre << " (" << potenciaW << " W) - horas:";
        for (int d = 0; d < DIAS; d++)
        {
            cout << " " << horas[d];
        }
        cout << endl;
    }

    float energiaDia(int d)
    {
        return potenciaW * horas[d] / 1000.0f;
    }

    float energiaSemana()
    {
        float total = 0;
        for (int d = 0; d < DIAS; d++)
        {
            total += energiaDia(d);
        }
        return total;
    }

    float horasSemana()
    {
        float totalH = 0;
        for (int d = 0; d < DIAS; d++)
        {
            totalH += horas[d];
        }
        return totalH;
    }

    int diaDeMayorUso()
    {
        int mayor = 0;
        for (int d = 1; d < DIAS; d++)
        {
            if (horas[d] > horas[mayor])
            {
                mayor = d;
            }
        }
        return mayor;
    }

    void reducirHoras(float porcentaje)
    {
        float factor = 1.0f - (porcentaje / 100.0f);
        for (int d = 0; d < DIAS; d++)
        {
            horas[d] = horas[d] * factor;
        }
    }
};

class Hogar
{
private:
    string nombre;
    float tarifa;
    Equipo equipos[MAX_EQUIPOS];
    int cantidad;
    float consumo[DIAS][MAX_EQUIPOS];

public:
    Hogar(string n, float t)
    {
        nombre = n;
        tarifa = t;
        cantidad = 0;
    }

    void setDatos(string n, float t)
    {
        nombre = n;
        tarifa = t;
    }

    int getCantidad()
    {
        return cantidad;
    }

    void vaciar()
    {
        cantidad = 0;
    }

    Equipo getEquipo(int e)
    {
        return equipos[e];
    }

    void mostrarEquipos()
    {
        cout << defaultfloat << setprecision(6);
        if (cantidad == 0)
        {
            cout << "Todavia no hay equipos" << endl;
        }
        for (int e = 0; e < cantidad; e++)
        {
            cout << e << ". ";
            equipos[e].mostrar();
        }
    }

    void agregarEquipo(Equipo e)
    {
        if (cantidad < MAX_EQUIPOS)
        {
            equipos[cantidad] = e;
            cantidad++;
        }
        else
        {
            cout << "No caben mas equipos" << endl;
        }
    }

    void calcularMatriz()
    {
        for (int d = 0; d < DIAS; d++)
        {
            for (int e = 0; e < cantidad; e++)
            {
                consumo[d][e] = equipos[e].energiaDia(d);
            }
        }
    }

    float totalDia(int d)
    {
        float total = 0;
        for (int e = 0; e < cantidad; e++)
        {
            total += consumo[d][e];
        }
        return total;
    }

    float totalEquipo(int e)
    {
        float total = 0;
        for (int d = 0; d < DIAS; d++)
        {
            total += consumo[d][e];
        }
        return total;
    }

    float totalSemana()
    {
        float total = 0;
        for (int d = 0; d < DIAS; d++)
        {
            total += totalDia(d);
        }
        return total;
    }

    int diaMasCaro()
    {
        int mayor = 0;
        for (int d = 1; d < DIAS; d++)
        {
            if (totalDia(d) > totalDia(mayor))
            {
                mayor = d;
            }
        }
        return mayor;
    }

    int equipoQueMasGasta()
    {
        int mayor = 0;
        for (int e = 1; e < cantidad; e++)
        {
            if (totalEquipo(e) > totalEquipo(mayor))
            {
                mayor = e;
            }
        }
        return mayor;
    }

    int diaMasBarato()
    {
        int menor = 0;
        for (int d = 1; d < DIAS; d++)
        {
            if (totalDia(d) < totalDia(menor))
            {
                menor = d;
            }
        }
        return menor;
    }

    float porcentajeEquipo(int e)
    {
        float totalS = totalSemana();
        if (totalS == 0)
            return 0;
        return (totalEquipo(e) / totalS) * 100.0f;
    }

    float promedioDiario()
    {
        return totalSemana() / (float)DIAS;
    }

    void simularAhorro(int e, float porcentaje)
    {
        calcularMatriz();
        float consumoAntes = totalSemana();
        float costoAntes = consumoAntes * tarifa;

        // Modificamos una copia temporal del equipo
        Equipo equipoModificado = equipos[e];
        equipoModificado.reducirHoras(porcentaje);

        Equipo backup = equipos[e];
        equipos[e] = equipoModificado;
        calcularMatriz();

        float consumoDespues = totalSemana();
        float costoDespues = consumoDespues * tarifa;
        float ahorroPesos = costoAntes - costoDespues;

        cout << fixed << setprecision(0);
        cout << endl
             << "=== SIMULACION DE AHORRO (" << backup.getNombre() << " -" << porcentaje << "%) ===" << endl;
        cout << "Costo semanal ANTES:   " << costoAntes << " COP" << endl;
        cout << "Costo semanal DESPUES: " << costoDespues << " COP" << endl;
        cout << "AHORRO SEMANAL:        " << ahorroPesos << " COP" << endl;
        cout << "AHORRO MENSUAL ESTIMADO (x4): " << ahorroPesos * 4 << " COP" << endl;

        equipos[e] = backup;
        calcularMatriz();
    }

    void mostrarMatriz()
    {
        cout << fixed << setprecision(2);
        cout << endl
             << "Consumo en kWh (filas = dias, columnas = equipos)" << endl;

        cout << setw(5) << "Dia";
        for (int e = 0; e < cantidad; e++)
        {
            cout << setw(18) << equipos[e].getNombre();
        }
        cout << setw(10) << "Total" << endl;

        for (int d = 0; d < DIAS; d++)
        {
            cout << setw(5) << NOMBRE_DIA[d];
            for (int e = 0; e < cantidad; e++)
            {
                cout << setw(18) << consumo[d][e];
            }
            cout << setw(10) << totalDia(d) << endl;
        }

        cout << setw(5) << "Total";
        for (int e = 0; e < cantidad; e++)
        {
            cout << setw(18) << totalEquipo(e);
        }
        cout << setw(10) << totalSemana() << endl;
    }

    void reporte()
    {
        int dCaro = diaMasCaro();
        int dBarato = diaMasBarato();
        int eGasta = equipoQueMasGasta();
        float costoSemana = totalSemana() * tarifa;

        cout << fixed << setprecision(0);
        cout << endl
             << "===== REPORTE DE CONSUMO: " << nombre << " =====" << endl;
        cout << "Tarifa contratada: " << tarifa << " COP/kWh" << endl;
        cout << "Consumo promedio diario: " << fixed << setprecision(2) << promedioDiario() << " kWh/dia" << endl;
        cout << fixed << setprecision(0);
        cout << "Dia de MAYOR consumo (Mas caro):   " << NOMBRE_DIA[dCaro] << " (" << totalDia(dCaro) * tarifa << " COP)" << endl;
        cout << "Dia de MENOR consumo (Mas barato): " << NOMBRE_DIA[dBarato] << " (" << totalDia(dBarato) * tarifa << " COP)" << endl;
        cout << "Equipo que mas gasta:              " << equipos[eGasta].getNombre()
             << " (" << totalEquipo(eGasta) * tarifa << " COP/semana)" << endl;

        cout << endl
             << "--- PARTICIPACION POR EQUIPO EN EL CONSUMO TOTAL ---" << endl;
        for (int e = 0; e < cantidad; e++)
        {
            cout << "- " << setw(20) << left << equipos[e].getNombre()
                 << ": " << fixed << setprecision(1) << porcentajeEquipo(e) << " %" << endl;
        }

        cout << fixed << setprecision(0);
        cout << endl
             << "Costo total semanal:       " << costoSemana << " COP" << endl;
        cout << "Proyeccion costo mensual:  " << costoSemana * 4 << " COP" << endl;
    }
};

int main()
{
    Hogar casa("Mi Casa Real", 0);
    int opcion;

    do
    {
        cout << endl
             << "===== MiConsumo (El Nino 2026) =====" << endl;
        cout << "1. Datos de la casa (nombre y tarifa)" << endl;
        cout << "2. Agregar un equipo" << endl;
        cout << "3. Ver los equipos" << endl;
        cout << "4. Ver la matriz de consumo" << endl;
        cout << "5. Ver el reporte detallado" << endl;
        cout << "6. Cargar los datos REALES de mi casa" << endl;
        cout << "7. Simular un ahorro" << endl;
        cout << "8. Ver un equipo en detalle" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {

        case 1:
        {
            string nombre;
            float tarifa;
            cout << "Nombre de la casa: ";
            getline(cin >> ws, nombre);
            do
            {
                cout << "Tarifa de su factura (COP por kWh): ";
                cin >> tarifa;
            } while (tarifa <= 0);
            casa.setDatos(nombre, tarifa);
            cout << "Datos guardados." << endl;
            break;
        }

        case 2:
        {
            if (casa.getCantidad() == MAX_EQUIPOS)
            {
                cout << "Ya hay " << MAX_EQUIPOS << " equipos guardados. No caben mas." << endl;
                break;
            }
            string nombre;
            float potencia;
            float horas[DIAS];
            cout << "Nombre del equipo: ";
            getline(cin >> ws, nombre);
            do
            {
                cout << "Potencia en vatios (W): ";
                cin >> potencia;
            } while (potencia <= 0);

            for (int d = 0; d < DIAS; d++)
            {
                do
                {
                    cout << "Horas el " << NOMBRE_DIA[d] << " (0 a 24): ";
                    cin >> horas[d];
                } while (horas[d] < 0 || horas[d] > 24);
            }
            casa.agregarEquipo(Equipo(nombre, potencia, horas));
            cout << "Equipo agregado exitosamente." << endl;
            break;
        }

        case 3:
            casa.mostrarEquipos();
            break;

        case 4:
            if (casa.getCantidad() == 0)
            {
                cout << "Primero agregue equipos (opcion 2 o 6)." << endl;
            }
            else
            {
                casa.calcularMatriz();
                casa.mostrarMatriz();
            }
            break;

        case 5:
            if (casa.getCantidad() == 0)
            {
                cout << "Primero agregue equipos (opcion 2 o 6)." << endl;
            }
            else
            {
                casa.calcularMatriz();
                casa.reporte();
            }
            break;

        case 6:
        {
            casa.vaciar();
            casa.setDatos("Hogar Jorge Gonzalez", 964.13f);

            // 1. Router de internet SDMC (12 W)
            float hRouter[DIAS] = {24.0f, 24.0f, 24.0f, 24.0f, 24.0f, 24.0f, 24.0f};
            // 2. Televisor de 55 Pulgadas LG (180 W)
            float hTv[DIAS] = {3.0f, 2.0f, 3.6f, 0.0f, 0.3f, 2.0f, 10.5f};
            // 3. Computador Portátil Hp(220 W)
            float hComp[DIAS] = {0.0f, 0.0f, 6.0f, 6.0f, 6.0f, 5.0f, 1.0f};
            // 4. Lavadora Lg(500 W)
            float hLava[DIAS] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 6.0f, 3.0f};

            casa.agregarEquipo(Equipo("Router", 12, hRouter));
            casa.agregarEquipo(Equipo("Televisor", 160, hTv));
            casa.agregarEquipo(Equipo("Computador Portatil", 45, hComp));
            casa.agregarEquipo(Equipo("Lavadora", 500, hLava));

            cout << "Datos REALES de la casa cargados correctamente (4 equipos, Tarifa: 964.13 COP/kWh)." << endl;
            break;
        }

        case 7:
        {
            if (casa.getCantidad() == 0)
            {
                cout << "Primero agregue o cargue los equipos (opcion 2 o 6)." << endl;
                break;
            }
            int numEq;
            float porc;

            casa.mostrarEquipos();

            do
            {
                cout << "Seleccione el numero del equipo (0 a " << casa.getCantidad() - 1 << "): ";
                cin >> numEq;
            } while (numEq < 0 || numEq >= casa.getCantidad());

            do
            {
                cout << "Digite el porcentaje de reduccion (1 a 100 %): ";
                cin >> porc;
            } while (porc < 1.0f || porc > 100.0f);

            casa.simularAhorro(numEq, porc);
            break;
        }

        case 8:
        {
            if (casa.getCantidad() == 0)
            {
                cout << "Primero agregue o cargue los equipos (opcion 2 o 6)." << endl;
                break;
            }
            int numEq;
            casa.mostrarEquipos();

            do
            {
                cout << "Seleccione el numero del equipo a consultar (0 a " << casa.getCantidad() - 1 << "): ";
                cin >> numEq;
            } while (numEq < 0 || numEq >= casa.getCantidad());

            casa.calcularMatriz();
            Equipo eq = casa.getEquipo(numEq);

            cout << endl
                 << "=== DETALLE DEL EQUIPO: " << eq.getNombre() << " ===" << endl;
            cout << "Potencia: " << eq.getPotenciaW() << " W" << endl;
            cout << "Total horas de uso en la semana: " << eq.horasSemana() << " horas" << endl;
            cout << "Dia de MAYOR uso: " << NOMBRE_DIA[eq.diaDeMayorUso()] << endl;
            cout << "Participacion en el consumo del hogar: " << fixed << setprecision(1)
                 << casa.porcentajeEquipo(numEq) << " %" << endl;
            break;
        }

        case 0:
            cout << "Gracias por usar MiConsumo. ¡A cuidar la energia!" << endl;
            break;

        default:
            cout << "Opcion invalida. Intente de nuevo." << endl;
        }

    } while (opcion != 0);

    return 0;
}