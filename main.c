#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include "SharedMemory.h"
#include "course.c"
#include <fcntl.h>
#include <semaphore.h>

int V = 21;

struct F1 classment[21];

void afficheTab(char *NumCourse) {
	int kTemp;
	system("clear");
if(strcmp(NumCourse , "C1")!=0)
{
	printf("%*s | %*s | %*s | %*s | %*s | %*s | %*s | %*s | %*s |\n",5,"N°",6,"IDV",5,"S1",5,"S2",5,"S3",6,"TEMP",5,"BTEMP",5,"STATUS",5,"ECART");
	printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
	memcpy(&classment,voitcpy,sizeof(struct F1)*21);
	for (int i=0; i<V-1;i++){ // classement des voitures
		for (int y=i+1; y<V-1;y++){
			if(classment[i].temp[4]==0)
			{
				classment[i].temp[4] = 500;
			}
			if(classment[i].temp[4]>classment[y].temp[4])
			{
				classment[20] = classment[i];
				classment[i] = classment[y];
				classment[y] = classment[20];
			}
		}
		if(classment[i].temp[4]==500)
			{
				classment[i].temp[4] = 0;
			}
	}
}
else
{
	printf("%*s | %*s | %*s | %*s | %*s | %*s | %*s | %*s | %*s | %*s |\n",5,"N°",6,"IDV",5,"S1",5,"S2",5,"S3",6,"TEMP",5,"BTEMP",5,"STATUS",5,"TEMP TOT",5,"ECART");
	printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
	memcpy(&classment,voitcpy,sizeof(struct F1)*21);
	for (int i=0; i<V-1;i++){ // classement des voitures
		for (int y=i+1; y<V-1;y++){
				if(classment[i].temp[5]>classment[y].temp[5])
				{
					classment[20] = classment[i];
					classment[i] = classment[y];
					classment[y] = classment[20];
				}
		}
	}
	for (int i=0; i<V-1;i++){
		if (classment[i].statut == 'O'){
			classment[i].temp[5] -= 500;
		}
	}
}

for(int k=0;k<V-1;k++)//affichage du classement
    {
		if (classment[k].lost == 0){
			if(strcmp(NumCourse , "C1")==0)
			{
			   printf("N°%*d | F%*d | %*d | %*d | %*d | %*ds | %*ds | %*c | %*ds |",2,k+1,5,classment[k].id,5,classment[k].temp[0],5,classment[k].temp[1],5,classment[k].temp[2],5,classment[k].temp[3],5,classment[k].temp[4],4,classment[k].statut,5,classment[k].temp[5]);
			   if(k == 0)
			   {
				   printf("%*ds |\n",4,0);
				   
			   }
			   else
			   {
				   kTemp = k-1;
				   printf("%*ds |\n",4,abs(classment[k].temp[5] - classment[kTemp].temp[5]));
				}
			}
			else{
				printf("N°%*d | F%*d | %*d | %*d | %*d | %*ds | %*ds | %*c |",2,k+1,5,classment[k].id,5,classment[k].temp[0],5,classment[k].temp[1],5,classment[k].temp[2],5,classment[k].temp[3],5,classment[k].temp[4],4,classment[k].statut);
			   if(k == 0)
			   {
				   printf("%*ds |\n",4,0);
			   }
			   else
			   {
				   kTemp = k-1;
				   printf("%*ds |\n",4,abs(classment[k].temp[4] - classment[kTemp].temp[4]));
				}
			}
		}
    }
	printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
	printf(" Best S1 par F%2d: %2d\n",voitcpy[20].idBst[0], voitcpy[20].BStemp[0]);
	printf(" Best S2 par F%2d: %2d\n",voitcpy[20].idBst[1], voitcpy[20].BStemp[1]);
	printf(" Best S3 par F%2d: %2d\n",voitcpy[20].idBst[2], voitcpy[20].BStemp[2]);
	printf(" Best Temp par F%2d: %2d\n",voitcpy[20].idBst[3], voitcpy[20].BStemp[3]);
	printf("--------------------------------------------------------------\n");

}
void Ecrit(char *tour){ // ecriture sur fichier des classement
	char buff[1024];
	int f;
	if(strcmp(tour , "P1")==0){
		if(!(f = open("P1.txt", O_WRONLY)))
		{}
		else{
			system("touch P1.txt");
			f = open("P1.txt", O_WRONLY);
		}
	}
	else if(strcmp(tour , "P2")==0){
		if(!(f = open("P2.txt", O_WRONLY)))
		{}
		else{
			system("touch P2.txt");
			f = open("P2.txt", O_WRONLY);
			}
	}
	else if(strcmp(tour , "P3")==0){
		if(!(f = open("P3.txt", O_WRONLY)))
		{}
		else{
			system("touch P3.txt");
			f = open("P3.txt", O_WRONLY);
			}
	}
	else if(strcmp(tour , "Q1")==0){
		if(!(f = open("Q1.txt", O_WRONLY)))
		{}
		else{
			system("touch Q1.txt");
			f = open("Q1.txt", O_WRONLY);
			}
	}
	else if(strcmp(tour , "Q2")==0){
		if(!(f = open("Q2.txt", O_WRONLY)))
		{}
		else{
			system("touch Q2.txt");
			f = open("Q2.txt", O_WRONLY);
			}
	}
	else if(strcmp(tour , "Q3")==0){
		if(!(f = open("Q3.txt", O_WRONLY)))
		{}
		else{
			system("touch Q3.txt");
			f = open("Q3.txt", O_WRONLY);
			}
	}
	else if(strcmp(tour , "C1")==0){
		if(!(f = open("C1.txt", O_WRONLY)))
		{}
		else{
			system("touch C1.txt");
			f = open("C1.txt", O_WRONLY);
			}
	}
    if(f < 0){ // vérifie que le fichier se soit ouvert
        perror("file ");
        exit(0);
    }
    for(int k=0;k<20;k++)//voiture
    {
       sprintf(buff,"%d\n",classment[k].id);
       write(f, buff, strlen(buff));
	}
	if (strcmp(tour , "C1")==0)
	{
		sprintf(buff,"Best Temp:%d Voiture F%d\n",voitcpy[20].BStemp[3],voitcpy[20].idBst[3]);
		write(f, buff, strlen(buff));
	}
	close(f);
}
int main(int argc,char *argv[])
{
srand(time(NULL));
if (argc > 1)
{
	// if anti erreur n'accepte que ces argument
	if (strcmp(argv[1],"C1")==0 || strcmp(argv[1],"P1")==0 || strcmp(argv[1],"P2")==0 || strcmp(argv[1],"P3")==0 || strcmp(argv[1],"Q1")==0 || strcmp(argv[1],"Q2")==0 || strcmp(argv[1],"Q3")==0)
	{
		int NumVoit[20] = {44, 77, 11, 33, 3, 4, 5, 18, 14, 31, 16, 55, 10, 22, 7, 99, 9, 47, 6, 63}; 
		connectShm();
		sem_init(sm, 1, 1);//initialise la sémaphore des fils a 1 (passant de base)
		sem_init(sm_reader, 1, 0);//initialise la sémaphore du pêre a 0 (bloquand de base)

		for(int k = 0; k<V-1 ; k++) // initialise les var
		{
			voitures[k].lost = 0;
			voitures[k].id = NumVoit[k];
		}
		V = getTour(argv[1]);
		for(int i=0;i<4;i++){
		voitures[20].BStemp[i] = 999; // init
		}
		for(int k = 0; k<V-1 ; k++) // init
		{
			voitures[k].statut = 'E';
			voitures[k].temp[5] = 0;
		}
		struct timeval tempInitial , tempFinal;
		int seconde = 0;
		int pid; 
		if (strcmp(argv[1],"C1")!=0)
		{
			
			while(seconde < 4)//Le nombre de secondes que les voitures vont tourner
			{
				*count_parent = 0;//Mets le compteur sert a débloquer la sémaphore du père a zero
				gettimeofday(&tempInitial , NULL);//temps avant l'execution du tour
				sleep(1);
					for(int k = 0; k<V-1 ; k++)
					{
						if ((pid = fork()) == 0)
						{
							if (voitures[k].lost == 0)
							{
								essaiQualifCourse(k);
								
							}
						}
					}
				//sleep(1);
				sem_wait(sm_reader);//sémaphore du père
					//S.C.
					memcpy(&voitcpy,voitures,sizeof(struct F1)*21);//Le père lis la mémoire partagée voitures
				sem_post(sm_reader);//sémaphore du père
				gettimeofday(&tempFinal , NULL);//temps après l'execution du tour
				seconde += (tempFinal.tv_sec - tempInitial.tv_sec);// additionne les temps
				 
				afficheTab(argv[1]);
				Ecrit(argv[1]);
				printf("\nTotal time taken is : %d seconds and %lu microseconds\n",(seconde),(tempFinal.tv_usec - tempInitial.tv_usec));
			}
		}
		else
		{
			for(int i=0;i<3;i++)
			{
				*count_parent = 0;//Mets le compteur sert a débloquer la sémaphore du père a zero
				gettimeofday(&tempInitial , NULL);//temps avant l'execution du tour
					for(int k = 0; k<V-1 ; k++)
					{
						if ((pid = fork()) == 0)
						{
							CourseV(k);
						}
					}
				sleep(1);
				sem_wait(sm_reader);//sémaphore du père
					//S.C.
					memcpy(&voitcpy,voitures,sizeof(struct F1)*21);//Le père lis la mémoire partagée voitures
				sem_post(sm_reader);//sémaphore du père
				gettimeofday(&tempFinal , NULL);//temps après l'execution du tour
				seconde += (tempFinal.tv_sec - tempInitial.tv_sec);
				 
				afficheTab(argv[1]);
				Ecrit(argv[1]);
				printf("\nTours numéro: %d\n",i+1);
			}
		}
		disconectShm();
	}
	else
	{
		printf("Mauvais argument veuillez entrée un des suivant: P1, P2, P3, Q1, Q2, Q3, C1\n");
	}
}
else
{
	printf("Veuillez entrée un argument: P1, P2, P3, Q1, Q2, Q3, C1\n");
}
//détruit les sémaphores
sem_destroy(sm);
sem_destroy(sm_reader);
return 0;
}