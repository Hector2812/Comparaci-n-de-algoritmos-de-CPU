#include <stdio.h>

typedef struct Proceso 
{
    char nombre;
    int prioridad;
    int Tllegada;
    int Tcpu;
    int Tretorn;
    int Trestante;
    int TEspera;
} Proceso;

void PintarEncabezado(char algoritmo[]) {
    printf("\n");
    printf("\033[1;34m");
    printf("RESULTADO DEL ALGORITMO %s\n\n", algoritmo);
    printf("\033[0m");

    printf("\033[1;34m");
    printf("  +-----------+-----------+----------+--------+\n");
    printf("  |  \033[1;37mProceso\033[0m  | \033[1;37mPrioridad\033[0m | \033[1;37mTllegada\033[0m |  \033[1;37mTcpu\033[0m  |\n");
    printf("  +-----------+-----------+----------+--------+\n");
    printf("\033[0m");
}


void PintarDatos(Proceso proceso) {
    printf("\033[1;34m");
    printf("  |     %c     |   %5d   |   %4d   |   %2d   |\n",
           proceso.nombre, proceso.prioridad, proceso.Tllegada, proceso.Tcpu);
}

void AlgoritmoSPN(Proceso procesosSPN[],int n,int procesos) 
{
    Proceso aux;
    for (int i=0;i<n-1;i++) 
    {
        for (int j=0;j<n-i-1;j++) 
        {
            int Intercambio=0;
            if (!procesos) 
            {
                if (procesosSPN[j].Tllegada>procesosSPN[j+1].Tllegada) 
                {
                    Intercambio=1;
                } 
                else if (procesosSPN[j].Tllegada==procesosSPN[j+1].Tllegada) 
                {
                    if (procesosSPN[j].Tcpu>procesosSPN[j+1].Tcpu) 
                    {
                        Intercambio=1;
                    } 
                    else if (procesosSPN[j].Tcpu==procesosSPN[j+1].Tcpu) 
                    {
                        if (procesosSPN[j].prioridad>procesosSPN[j+1].prioridad) 
                        {
                            Intercambio=1;
                        } 
                        else if (procesosSPN[j].prioridad==procesosSPN[j+1].prioridad) 
                        {
                            if (procesosSPN[j].nombre>procesosSPN[j+1].nombre) 
                            {
                                Intercambio=1;
                            }
                        }
                    }
                }
            } 
            else 
                {
                    if (procesosSPN[j].Tcpu>procesosSPN[j+1].Tcpu) 
                    {
                        Intercambio=1;
                    } 
                    else if (procesosSPN[j].Tcpu==procesosSPN[j+1].Tcpu) 
                    {
                        if (procesosSPN[j].prioridad>procesosSPN[j+1].prioridad) 
                        {
                            Intercambio=1;
                        } 
                        else if (procesosSPN[j].prioridad==procesosSPN[j+1].prioridad) 
                        {
                            if (procesosSPN[j].Tllegada>procesosSPN[j + 1].Tllegada) 
                            {
                                Intercambio=1;
                            } 
                            else if (procesosSPN[j].Tllegada==procesosSPN[j+1].Tllegada) 
                            {
                                if (procesosSPN[j].nombre>procesosSPN[j+1].nombre) 
                                {
                                    Intercambio=1;
                                }
                            }
                        }
                    }
                }

            if (Intercambio) 
            {
                aux=procesosSPN[j];
                procesosSPN[j]=procesosSPN[j+1];
                procesosSPN[j+1]=aux;
            }
        }
    }
}

void calcularTiemposEspera(Proceso procesos[],int n) 
{
    for (int i=0;i<n;i++) 
    {
        procesos[i].TEspera=procesos[i].Tretorn-procesos[i].Tcpu;
    }
}

int calcularQuantum(int n,Proceso procesosRR[]) 
{
    int sumaTcpu=0;
    for (int i=0;i<n;i++) 
    {
        sumaTcpu+=procesosRR[i].Tcpu;
    }
    int quantum=sumaTcpu/n;
    return quantum;
}

void roundRobin(Proceso procesosRR[],int n,int quantum) 
{
    int tiempoActual=0;
    int procesosRestantes=n;
    int procesoActual=0;

    while (procesosRestantes>0) 
    {
        if (procesosRR[procesoActual].Trestante>0) 
        {
            int tiempoEjecucion;
            if (procesosRR[procesoActual].Trestante>quantum)
                tiempoEjecucion=quantum;
            else
                tiempoEjecucion=procesosRR[procesoActual].Trestante;

            tiempoActual+=tiempoEjecucion;
            procesosRR[procesoActual].Trestante-=tiempoEjecucion;

            procesosRR[procesoActual].Tretorn=tiempoActual-procesosRR[procesoActual].Tllegada;

            if (procesosRR[procesoActual].Trestante==0)
                procesosRestantes--;
        }

        if (procesosRR[procesoActual].Trestante>0) 
        {
            int procesoExpulsar=-1;
            for (int i=0;i<n;i++) 
            {
                if (procesosRR[i].Trestante>0 && procesosRR[i].prioridad>procesosRR[procesoActual].prioridad) {
                    procesoExpulsar=i;
                    break;
                }
            }

            if (procesoExpulsar!=-1) 
            {
                procesoActual=procesoExpulsar;
            }
        }
        procesoActual=(procesoActual+1)%n;
    }
}

void compararAlgoritmos(double promTRNSPN,double promTRNRR) 
{
    if (promTRNSPN<promTRNRR) 
    {
        printf("\033[1;31mRESULTADO:\n");
        printf("\033[1;31mEl algoritmo SPN es el mejor.\n");
        printf("\033[0m");
    } 
    else if (promTRNSPN>promTRNRR) 
    {
        printf("\033[1;31mRESULTADO:\n");
        printf("\033[1;31mEl algoritmo Round Robin es el mejor.\n");
        printf("\033[0m");
    } 
    else 
    {
        printf("\033[1;31mRESULTADO:\n");
        printf("\033[1;31mAmbos algoritmos son iguales en rendimiento.\n");
        printf("\033[0m");
    }
}

void guardarComparacionAlgoritmos(double promTRNSPN,double promTRNRR) 
{
    FILE *archivo;
    archivo = fopen("resultados.txt","a"); 
    if (promTRNSPN<promTRNRR) 
    {
        fprintf(archivo,"RESULTADO:\n");
        fprintf(archivo,"El algoritmo SPN es el mejor.\n");
    } 
    else if (promTRNSPN>promTRNRR) 
    {
        fprintf(archivo,"RESULTADO:\n");
        fprintf(archivo,"El algoritmo Round Robin es el mejor.\n");
    } 
    else 
    {
        fprintf(archivo,"RESULTADO:\n");
        fprintf(archivo,"Ambos algoritmos son iguales en rendimiento.\n");
    }
    fclose(archivo); 
}


void guardarResultadosEnArchivo(char algoritmo[],Proceso procesos[],int n,double tiempoRetornoPromedio,double tiempoEsperaPromedio,double tiempoServicioPromedio,double tiempoRetornoNormalizadoPromedio) 
{
    FILE *archivo;
    archivo = fopen("resultados.txt","a"); 

    fprintf(archivo, "RESULTADO DEL ALGORITMO %s\n",algoritmo);
    fprintf(archivo, "Proceso | Prioridad | Tllegada | Tcpu | Tretorn\n");
    for (int i = 0; i < n; i++) {
        fprintf(archivo, "   %c    |   %5d   |   %4d   |  %2d  |   %2d\n",
                procesos[i].nombre,procesos[i].prioridad, procesos[i].Tllegada,procesos[i].Tcpu,procesos[i].Tretorn);
    }
    fprintf(archivo, "Tiempo de retorno promedio: %.3lf\n",tiempoRetornoPromedio);
    fprintf(archivo, "Tiempo de espera promedio: %.3lf\n",tiempoEsperaPromedio);
    fprintf(archivo, "Tiempo de servicio promedio: %.3lf\n",tiempoServicioPromedio);
    fprintf(archivo, "Tiempo de retorno normalizado promedio: %.3lf\n\n",tiempoRetornoNormalizadoPromedio);

    fclose(archivo); 
}

void MostrarTabla(Proceso procesos[], int n) 
{
    int maxTiempo=0;
    int maxTiempoProceso=0;

    for (int i=0;i<n;i++) 
    {
        int tiempoProceso=procesos[i].Tllegada+procesos[i].Tretorn;
        if (tiempoProceso>maxTiempo) 
        {
            maxTiempo=tiempoProceso;
        }
        if (procesos[i].Tllegada>maxTiempoProceso) 
        {
            maxTiempoProceso=procesos[i].Tllegada;
        }
    }
    printf("\nTabla de tiempos de CPU (\033[1;32mX\033[0m) y tiempos de espera (\033[1;33mW\033[0m) por proceso para SPN:\n\n");
    printf("   Proceso ");
    
    for (int i=0;i<(maxTiempo+maxTiempoProceso);i++) 
    {
        printf("|%2d ",i);
    }
    printf("|\n");
    printf("  ---------");

    for (int i=0;i<(maxTiempo+maxTiempoProceso);i++) 
    {
        printf("|---");
    }
    printf("|\n");
    
    for (int i=0;i<n;i++) 
    {
        printf("      %c    ",procesos[i].nombre);

        for (int j = 0; j<maxTiempo;j++)
        {
            if (j>=procesos[i].Tllegada && j<(procesos[i].Tllegada+procesos[i].TEspera)) 
            {
                printf("| \033[1;33mW\033[0m ");
            } 
            else if (j>=procesos[i].Tllegada+procesos[i].TEspera && j<(procesos[i].Tllegada + procesos[i].Tretorn)) 
            {
                printf("| \033[1;32mX\033[0m "); 
            } 
            else 
            {
                printf("|   ");
            }
        }
        printf("|\n");
    }
}

void guardarTablaEnArchivo(Proceso procesos[],int n,char algoritmo[]) 
{
    int maxTiempo=0;
    int maxTiempoProceso=0;

    for (int i=0;i<n;i++) 
    {
        int tiempoProceso=procesos[i].Tllegada+procesos[i].Tretorn;
        if (tiempoProceso>maxTiempo) 
        {
            maxTiempo=tiempoProceso;
        }
        if (procesos[i].Tllegada>maxTiempoProceso) 
        {
            maxTiempoProceso=procesos[i].Tllegada;
        }
    }

    FILE *archivo;
    archivo=fopen("resultados.txt", "a"); 

    fprintf(archivo, "\nTabla de tiempos de CPU (X) y tiempos de espera (W) por proceso para %s:\n\n", algoritmo);
    fprintf(archivo, "   Proceso ");

    for (int i=0;i<(maxTiempo+maxTiempoProceso);i++) 
    {
        fprintf(archivo, "|%2d ",i);
    }
    fprintf(archivo, "|\n");
    fprintf(archivo, "  ---------");

    for (int i=0;i<(maxTiempo+maxTiempoProceso);i++) 
    {
        fprintf(archivo, "|---");
    }
    fprintf(archivo, "|\n");

    for (int i=0;i<n;i++) 
    {
        fprintf(archivo, "      %c    ",procesos[i].nombre);

        for (int j=0;j<maxTiempo;j++) 
        {
            if (j>=procesos[i].Tllegada && j<(procesos[i].Tllegada+procesos[i].TEspera)) 
            {
                fprintf(archivo, "| W ");
            } 
            else if (j >= procesos[i].Tllegada+procesos[i].TEspera && j<(procesos[i].Tllegada+procesos[i].Tretorn)) 
            {
                fprintf(archivo, "| X ");
            } 
            else 
            {
                fprintf(archivo, "|   ");
            }
        }
        fprintf(archivo, "|\n");
    }

    fclose(archivo);
}


int main() 
{
    Proceso procesosSPN[5];
    Proceso procesosRR[5];
    double TretornTotalSPN=0;
    double TcpuTotalSPN=0;
    double TretornTotalRR=0;
    double TcpuTotalRR=0;
    double TEsperaTotal=0;
    
    printf("Ingrese los datos de los procesos:\n");
    for (int i=0;i<5;i++) 
    {
        printf("Proceso %c\n",'A'+i);
        procesosSPN[i].nombre='A'+i;
        procesosRR[i].nombre='A'+i;
        printf("Prioridad: ");
        scanf("%d", &procesosSPN[i].prioridad);
        procesosRR[i].prioridad=procesosSPN[i].prioridad;
        printf("Tllegada: ");
        scanf("%d", &procesosSPN[i].Tllegada);
        procesosRR[i].Tllegada=procesosSPN[i].Tllegada;
        printf("Tcpu: ");
        scanf("%d", &procesosSPN[i].Tcpu);
        procesosRR[i].Tcpu=procesosSPN[i].Tcpu;
        
        TcpuTotalSPN+=procesosSPN[i].Tcpu;
        TcpuTotalRR+=procesosRR[i].Tcpu;
        procesosRR[i].Trestante = procesosRR[i].Tcpu;
    }

    AlgoritmoSPN(procesosSPN,5,0);
    int TactualSPN=procesosSPN[0].Tllegada;

    for (int i=0;i<5;i++) 
    {
        procesosSPN[i].Tretorn=TactualSPN+procesosSPN[i].Tcpu-procesosSPN[i].Tllegada;
        TactualSPN+=procesosSPN[i].Tcpu;
        TretornTotalSPN+=(double)procesosSPN[i].Tretorn;

        if (i<4) 
        {
            AlgoritmoSPN(procesosSPN+i+1,4-i,1);
        }
    }
    
    calcularTiemposEspera(procesosSPN, 5);
    for (int i=0;i<5;i++) 
    {
        TEsperaTotal+=procesosSPN[i].TEspera;
    }

    PintarEncabezado("SPN");
    for (int i=0;i<5;i++) 
    {
        PintarDatos(procesosSPN[i]);
    }
    printf("  +-----------+-----------+----------+--------+\n\n");

    double promTRNSPN=TretornTotalSPN/TcpuTotalSPN;
    printf("\033[1;32m");
    printf("El tiempo de retorno promedio es: %.3lf\n",TretornTotalSPN/5);
    printf("El tiempo de espera promedio es: %.3lf\n",TEsperaTotal/5);
    printf("El tiempo de servicio promedio es: %.3lf\n",TcpuTotalSPN/5);
    printf("El tiempo de retorno normalizado promedio usando el Algoritmo SPN es: %.3lf\n",promTRNSPN);
    printf("\033[0m");
    printf("\n");
    
    int quantum=calcularQuantum(5,procesosRR);
    roundRobin(procesosRR,5,quantum);
    
    for (int i=0;i<5;i++) 
    {
        TretornTotalRR+=(double)procesosRR[i].Tretorn;
    }
    
    PintarEncabezado("Round Robin");
    for (int i=0;i<5;i++) 
    {
        PintarDatos(procesosRR[i]);
    }
    printf("  +-----------+-----------+----------+--------+\n\n");

    printf("\033[1;33mQuantum calculado automaticamente: %d\n\033[0m",quantum);

   
    double promTRNRR=TretornTotalRR/TcpuTotalRR;
    printf("\033[1;32m");
    printf("El tiempo de retorno promedio es: %.3lf\n",TretornTotalRR/5);
    printf("El tiempo de espera promedio es: %.3lf\n",TretornTotalRR/5-TcpuTotalRR/5);
    printf("El tiempo de servicio promedio es: %.3lf\n",TcpuTotalRR/5);
    printf("El tiempo de retorno normalizado promedio usando el Algoritmo Round Robin es: %.3lf\n",promTRNRR);
    printf("\033[0m");
    printf("\n\n");
    
    compararAlgoritmos(promTRNSPN,promTRNRR);
    MostrarTabla(procesosSPN, 5);
    printf("\n\n");

    guardarResultadosEnArchivo("SPN",procesosSPN,5,TretornTotalSPN/5,TEsperaTotal/5,TcpuTotalSPN/5,promTRNSPN);
    guardarResultadosEnArchivo("Round Robin",procesosRR,5,TretornTotalRR/5,TretornTotalRR/5-TcpuTotalRR/5,TcpuTotalRR/5,promTRNRR);
    guardarComparacionAlgoritmos(promTRNSPN,promTRNRR);
    guardarTablaEnArchivo(procesosSPN, 5, "SPN");
    
    return 0;
}