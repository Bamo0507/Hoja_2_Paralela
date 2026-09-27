/*----------------------------------------------------------------------
 * Universidad del Valle de Guatemala
 * Curso:     CC3169 - Computacion Paralela y Distribuida
 * Miembros:  Bryan Alberto Martínez Orellana 23542
 *            Adriana Sophia Palacios Contreras 23044
 * Ejercicio: Hoja de Trabajo 02 - Introduccion a Open MPI
 *            Inciso 4
 * Descripcion: simulacion de la distribucion de pedidos desde la
 *              Oficina Central hacia las sucursales.
 *
 *              Cada proceso MPI representa una ubicacion diferente:
 *                  rank 0 -> Oficina central
 *                  rank 1 -> Sucursal 1
 *                  rank 2 -> Sucursal 2
 *                  rank 3 -> Sucursal 3
 *
 *              La Oficina Central posee una lista de pedidos y
 *              distribuye una parte a cada proceso utilizando
 *              MPI_Scatter().
 *----------------------------------------------------------------------*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int rank;
    int size;
    int pedidos[8]; // Pares consecutivos: pedidos y empleados por ubicacion
    int datos_recibidos[2];

    // Inicializa el entorno MPI
    MPI_Init(&argc, &argv);

    // Obtener el identificador del proceso actual
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Obtener el numero total de procesos que participan
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Este ejercicio requiere exactamente 4 procesos
    if (size != 4) {

        if (rank == 0) {
            printf("Este programa requiere exactamente 4 procesos.\n");
        }

        MPI_Finalize();
        return 0;
    }

    // La Oficina Central define la cantidad de pedidos para cada ubicacion
    if (rank == 0) {

        pedidos[0] = 120;
        pedidos[1] = 6;   // Empleados de la Oficina Central
        pedidos[2] = 95;
        pedidos[3] = 5;   // Empleados de la Sucursal 1
        pedidos[4] = 140;
        pedidos[5] = 7;   // Empleados de la Sucursal 2
        pedidos[6] = 110;
        pedidos[7] = 4;   // Empleados de la Sucursal 3

        printf("Oficina Central: distribuyendo pedidos y empleados...\n");
    }

    // Distribuir dos enteros consecutivos a cada proceso, incluido rank 0
    MPI_Scatter(
        pedidos,
        2,
        MPI_INT,
        datos_recibidos,
        2,
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );

    // Cada proceso muestra el valor que recibio
    if (rank == 0) {
        printf("Oficina Central: %d pedidos asignados, %d empleados disponibles.\n",
               datos_recibidos[0], datos_recibidos[1]);
    } else {
        printf("Sucursal %d: %d pedidos asignados, %d empleados disponibles.\n",
               rank, datos_recibidos[0], datos_recibidos[1]);
    }

    // Finaliza correctamente el entorno MPI
    MPI_Finalize();

    return 0;
}