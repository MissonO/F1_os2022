#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

struct F1 voitcpy[21];

int geneTemp (int x){
	int r=(abs(rand()*x)% (40000 -25000 +1))+25000;
	return  r/1000;
}

void essaiQualifCourse(int k)
{
	sem_wait(sm);//sémaphore du fils
	//S.C.
				if (voitures[k].statut != 'O') // verifie si la voiture est out
					{
						if (voitures[k].statut == 'S') // si la voiture est au stand la remts en course
						{
							voitures[k].statut = 'E';
						}
						if (geneTemp(getpid()) == 39) // chance random d'etre au stand
						{
							voitures[k].statut = 'S';
						}
						if (geneTemp(getpid())+geneTemp(getpid())+geneTemp(getpid())+geneTemp(getpid()) == 143) // chance d'etre out
						{
							voitures[k].statut = 'O';
							if(voitures[k].temp[4]==0)
							{
								voitures[k].temp[4] = 500;
							}
						}
						if (voitures[k].statut == 'E') // si la voiture roule
						{
							voitures[k].temp[0] = geneTemp(getpid()); // géné temp S1
							
							voitures[k].temp[1] = geneTemp(getpid()); // s2
									
							voitures[k].temp[2] = geneTemp(getpid()); // s3
									
							voitures[k].temp[3] = voitures[k].temp[0] + voitures[k].temp[1] +voitures[k].temp[2]; // temp total 1 tour
									
							voitures[k].temp[4] = voitures[k].temp[0] + voitures[k].temp[1] +voitures[k].temp[2];
							if(voitures[k].temp[4] > voitcpy[k].temp[4] && voitcpy[k].temp[4] != 0)
							{
								voitures[k].temp[4] = voitcpy[k].temp[4]; // meilleur temps total d'un tour
							}

							if(voitures[20].BStemp[0]>voitures[k].temp[0])
							{
								voitures[20].BStemp[0] = voitures[k].temp[0]; // best S1
								voitures[20].idBst[0] = voitures[k].id;
							}
							if(voitures[20].BStemp[1]>voitures[k].temp[1])
							{
								voitures[20].BStemp[1] = voitures[k].temp[1]; // best S2
								voitures[20].idBst[1] = voitures[k].id;
							}
							if(voitures[20].BStemp[2]>voitures[k].temp[2])
							{
								voitures[20].BStemp[2] = voitures[k].temp[2]; // best S3
								voitures[20].idBst[2] = voitures[k].id;
							}
							if(voitures[20].BStemp[3]>voitures[k].temp[3])
							{
								voitures[20].BStemp[3] = voitures[k].temp[3]; // best temps total
								voitures[20].idBst[3] = voitures[k].id;
							}
						}
					}
					else
					{
						voitures[k].temp[4] = 500;
					}
					if(*count_parent == 19)//si tout les fils sont passés alors débloque le père
					{
						sem_post(sm_reader);//sémapore du père
					}
					else//si tout les fils ne sont pas encore passés alors incrémentation du compteur
					{
						(*count_parent)++;
					}
					sem_post(sm);//sémaphore du fils
					exit(1);
}

void CourseV(int k)
{
			sem_wait(sm);//sémaphore du fils
			//S.C.
			do{
					if (voitures[k].statut != 'O')
					{
						if (voitures[k].statut == 'S')
						{
							voitures[k].statut = 'E';
						}
						if (geneTemp(getpid()) == 36)
						{
							voitures[k].statut = 'S';
							voitures[k].temp[5] += 3;
						}
						if (geneTemp(getpid())+geneTemp(getpid())+geneTemp(getpid())+geneTemp(getpid()) == 143)
						{
							voitures[k].statut = 'O';
							voitures[k].temp[5] += 500;
						}
						if (voitures[k].statut == 'E')
						{
							voitures[k].temp[0] = geneTemp(getpid());
							
							voitures[k].temp[1] = geneTemp(getpid());
									
							voitures[k].temp[2] = geneTemp(getpid());
									
							voitures[k].temp[3] = voitures[k].temp[0] + voitures[k].temp[1] +voitures[k].temp[2];
									
							voitures[k].temp[4] = voitures[k].temp[0] + voitures[k].temp[1] +voitures[k].temp[2];
							
							voitures[k].temp[5] += voitures[k].temp[3];
							if(voitures[k].temp[4] > voitcpy[k].temp[4] && voitcpy[k].temp[4] != 0)
							{
								voitures[k].temp[4] = voitcpy[k].temp[4];
							}

							if(voitures[20].BStemp[0]>voitures[k].temp[0])
							{
								voitures[20].BStemp[0] = voitures[k].temp[0];
								voitures[20].idBst[0] = voitures[k].id;
							}
							if(voitures[20].BStemp[1]>voitures[k].temp[1])
							{
								voitures[20].BStemp[1] = voitures[k].temp[1];
								voitures[20].idBst[1] = voitures[k].id;
							}
							if(voitures[20].BStemp[2]>voitures[k].temp[2])
							{
								voitures[20].BStemp[2] = voitures[k].temp[2];
								voitures[20].idBst[2] = voitures[k].id;
							}
							if(voitures[20].BStemp[3]>voitures[k].temp[3])
							{
								voitures[20].BStemp[3] = voitures[k].temp[3];
								voitures[20].idBst[3] = voitures[k].id;
							}
						}
					}
			}while(voitures[k].statut == 'S');
			if(*count_parent == 19)//si tout les fils sont passés alors débloque le père
					{
						sem_post(sm_reader);//sémapore du père
					}
					else//si tout les fils ne sont pas encore passés alors incrémentation du compteur
					{
						(*count_parent)++;
					}
			sem_post(sm);//sémaphore du fils

			exit(1);
		
			
}

int getTour(char * tour){
	int V = 21;
	if (strcmp(tour,"Q2")==0 || strcmp(tour,"Q3")==0 || strcmp(tour,"C1")==0)
	{
		int fichier =0;
		if (strcmp(tour,"Q2")==0)
		{
			V = V-5;
			fichier = open("Q1.txt", O_RDONLY );
			for(int k = 15; k<20 ; k++) // on fait plus rouler les 5 derniere voitures
			{
				voitures[k].lost = 1;
			}
		}
		else if(strcmp(tour,"Q3")==0)
		{
			V = V-10;
			fichier = open("Q2.txt", O_RDONLY );
			for(int k = 10; k<20 ; k++) // on fait plus rouler les 10 derniere voitures
			{
				voitures[k].lost = 1;
			}
		}
		else
		{
			fichier = open("Q3.txt", O_RDONLY );
		}
		char* str = malloc(sizeof(char)*500);
		int red;
		char *classement;
		red = read(fichier, str, sizeof(str)*30); // recup le classement de la course d'avant
		close(fichier);
		int pos[20];
		int i=0;
		classement = strtok(str,"\n");
		while(classement!=NULL){
	   		pos[i] = atoi(classement); // stockage
			classement = strtok(NULL,"\n"); // prochaine phrase si présente
			i++;
		}
		for(int k = 0; k<20 ; k++)
		{
			voitures[k].id = pos[k]; // remets les voiture dans le bonne ordre
		}
	}
	return V;
}