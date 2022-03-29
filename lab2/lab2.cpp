// MSMPI_try1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdio.h"
#include "mpi.h"
#include "stdlib.h"

#define N1 32
#define N2 64

int main(int argc, char** argv)
{
    float A[N1], B[N1], C[N1], Y[N1];
    int S1, S2, rank, size, cicle, i, j, k;
    double time, time1, time2;
    MPI_Status status; // Mepemenan - ctpyktypa 8 KoTopye 6yayT
                           // coxpakaTcA napameTpy MpHHMMaeMbix
                        //   coobyennii c AaHHbMn
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("Hello(%d)-%d\n", rank, size);
    scanf_s("%i", &S1);
    scanf_s("%i", &S2);
    if (rank == 0) // Ecam npoyecc HyneBon
    {
        for (i = 0; i < N1; i++) {
            A[i] = i * 3;
            B[i] = i * i;
            C[i] = 3 * i * i + 1;
        }


        time1 = MPI_Wtime();  //Onpegenerne epemenn Havana o6pa6oTKn
        for (cicle = 0; cicle < 10000; cicle++) // «wxaxpatHoctn»
        {

            for (i = 1; i < size; i++) // Pacnpenenenne anementos maccnea B
            // mexay npoyeccamn
                MPI_Send(&B[(int)i * N1 / size], (int)N1 / size, MPI_FLOAT, i, 0, MPI_COMM_WORLD);

            for (i = 0; i < N1 / size; i++) // ka poancnennit
            {
                Y[i] = (S1 + S2) * B[i] + A[i] / C[i];
            }
            for (i = 1; i < size; i++) // C6op peaynbtatos 8 maccns Y
                MPI_Recv(&Y[(int)i * N1 / size], (int)N1 / size, MPI_FLOAT, i, 0, MPI_COMM_WORLD, &status);
        }
        // Koxey ynkna KpatHocth
        time2 = MPI_Wtime(); // OnpeneneHne epemeHn KoHUa o6pa6orKn
        time = time2 - time1;
        for (i = 0; i < N1; i++) printf("%f", Y[i]); // BuBon pesyrbtaToe

        if (rank == 0) printf("\nTIME = %f\n", time); // Boisoa spemenh
        // ebinonHeHnA

    }
    else //Ecan npowecc He KyjeRon
    {
        for (i = 0; i < N1; i++)
            for (j = 0; j < N2; j++) {
                A[i] = i * 3;
                 // Wnnynannaayna maccnea A
            }  // 0 scex npoyecax



        for (cicle = 0; cicle < 10000; cicle++) // «l|akn KpatHocTA»    
        {
            MPI_Recv(&B[(int)rank * N1 / size], (int)N1 / size, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &status); // Mpvem anemeHtoa maccnaa B
            MPI_Recv(&C[(int)rank * N1 / size], (int)N1 / size, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &status);
                   // ot Hynesoro npoyecca

            for (i = rank * N1 / size; i < (rank + 1) * N1 / size; i++)
            {
                Y[i] = (S1 + S2) * B[i] + A[i] / C[i];

            }

            // Nepegaya pesyrbtatos HyneBomy npoyeccy
            MPI_Send(&Y[(int)rank * N1 / size], (int)N1 / size, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
        }

    }
    MPI_Finalize();

}

/*
#include "stdio.h"
#include "mpi.h"
#include "stdlib.h"

#define N1 32

int main(int argc, char** argv)
{
    float A[N1], B[N1], C[N1], Y[N1];
    int S1,S2, i, j, k;
    scanf_s("%i", &S1);
    scanf_s("%i", &S2);

    //Инициализация
    for (int i = 0; i < N1; i++)
    {
        A[i] = i * 3;
        B[i] = i * i;
        C[i] = 3 * i * i + 1;
    }
    //Расчет
    for (int i = 0; i < N1; i++)
    {
        Y[i]= (S1 + S2) * B[i] + A[i] / C[i];
    }
    for (int i = 0; i < N1; i++)
    {
        printf_s("%f ", Y[i]);
    }




}
*/