#include <semaphore.h>

struct F1
{
	int id;
	int idBst[4];
	int temp[6];
	int BStemp[4];
	char statut; //S=stand O=out E=enCourse
	int lost;
};

struct F1 *voitures;
sem_t *sm, *sm_reader;
int shmid;
int key = 22;
int *count_parent;//Sert pour le compteur qui débloque le père grace aux fils
int shmid_count_parent;

void connectShm()//crée les mémoires partagées
{

	shmid = shmget(key, sizeof(struct F1) * 21, IPC_CREAT | 0666);
	voitures = (struct F1 *)shmat(shmid, 0, 0);
	int shmid_sem = shmget(IPC_PRIVATE, sizeof(sem_t), 0666 | IPC_CREAT);
	sm = shmat(shmid_sem, NULL, 0);
	int shmid_sem_reader = shmget(1, sizeof(sem_t), 0666 | IPC_CREAT);
	sm_reader = shmat(shmid_sem_reader, NULL, 0);
	shmid_count_parent = shmget(2, sizeof(int), 0666 | IPC_CREAT);
	count_parent = shmat(shmid_count_parent, NULL, 0);
}

void disconectShm()//Néttoie les mémoires partagées
{
	shmdt(count_parent);
	shmdt(voitures);
	shmctl(shmid, IPC_RMID, NULL);
	shmctl(shmid_count_parent, IPC_RMID, NULL);
}