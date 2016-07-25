#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "distribution.h"
#include "RR.h"
#include "maxSNR.h"
#include "initialisation.h"


int main(){
	FILE* fichier = NULL;
	
	int nb_users1, nb_users2, nb_users3, nb_users4;
	int nb_sub1, nb_sub2, nb_sub3, nb_sub4;
	int nb_sub_restant ;
	
	double res_sommeUR =0;
	double res_sommeUR_ant1 =0;
	double res_sommeUR_ant2 =0;
	double res_sommeUR_ant3 =0;
	double res_sommeUR_ant4 =0;
	
	double bit_par_UR = 0;
	double bit_par_UR_ant1 = 0;
	double bit_par_UR_ant2 = 0;
	double bit_par_UR_ant3 = 0;
	double bit_par_UR_ant4 = 0;
	
	int user_sommeUR = 0;
	int user_sommeUR_ant1 = 0;
	int user_sommeUR_ant2 = 0;
	int user_sommeUR_ant3 = 0;
	int user_sommeUR_ant4 = 0;
	
	int debitTotal_ant1 = 0;
	int debitTotal_ant2 = 0;
	int debitTotal_ant3 = 0;
	int debitTotal_ant4 = 0;
	int debitTotal = 0;
	
	double sommeDelais = 0;
	double sommeDelais_ant1 = 0;
	double sommeDelais_ant2 = 0;
	double sommeDelais_ant3 = 0;
	double sommeDelais_ant4 = 0;
	
	int i,k, indice = 0;

	int nbPaquetsTotal = 0;
	int nbPaquetsTotal_ant1 = 0;
	int nbPaquetsTotal_ant2 = 0;
	int nbPaquetsTotal_ant3 = 0;
	int nbPaquetsTotal_ant4 = 0;
	
	int nbPaquetsNonEnvoyes = 0;
	int nbPaquetsNonEnvoyes_ant1=0;
	int nbPaquetsNonEnvoyes_ant2=0;
	int nbPaquetsNonEnvoyes_ant3=0;
	int nbPaquetsNonEnvoyes_ant4=0;
	
	int nbPaquetsconsommer_ant1=0;
	int nbPaquetsconsommer_ant2=0;
	int nbPaquetsconsommer_ant3=0;
	int nbPaquetsconsommer_ant4=0;
	int nbPaquetsconsommer=0;
	
	int PDOR = 0;
	int PDOR_ant1 = 0;
	int PDOR_ant2 = 0;
	int PDOR_ant3 = 0;
	int PDOR_ant4 = 0;
	
	int PDOR_temps_ant1 = 0;
	int PDOR_temps_ant2 = 0;
	int PDOR_temps_ant3 = 0;
	int PDOR_temps_ant4 = 0;
	int PDOR_temps = 0;
	
	int PDOR_ant1_temp = 0;
	int PDOR_ant2_temp = 0;
	int PDOR_ant3_temp = 0;
	int PDOR_ant4_temp = 0;
	int PDOR_temp = 0;
	
	int consommer_temps_ant1 = 0;
	int consommer_temps_ant2 = 0;
	int consommer_temps_ant3 = 0;
	int consommer_temps_ant4 = 0;
	int consommer_temps = 0;
	
	int nbPaquetsTotalPDOR = 0;
	int nbPaquetsTotalPDOR_ant1 = 0;
	int nbPaquetsTotalPDOR_ant2 = 0;
	int nbPaquetsTotalPDOR_ant3 = 0;
	int nbPaquetsTotalPDOR_ant4 = 0;
	int nb_user_temp = 1;
	
	double debit_ms = 0;
	double debit_ms_ant1 = 0;
	double debit_ms_ant2 = 0;
	double debit_ms_ant3 = 0;
	double debit_ms_ant4 = 0;
	
	double delais_ms = 0;
	double delais_ms_ant1 = 0;
	double delais_ms_ant2 = 0;
	double delais_ms_ant3 = 0;
	double delais_ms_ant4 = 0;
	
	double subSwitch[4];
	
	int nb_user = 4;
	int nb_tours = 100;
	
	Packet *tmpPacket = NULL;
	
	int choixAlgo=0;
	
	Antenne Antenne1;
	Antenne Antenne2;
	Antenne Antenne3;
	Antenne Antenne4;

	nb_users1 = nb_user/4;
	nb_users2 = nb_user/4;
	nb_users3 = nb_user/4;
	nb_users4 = nb_user-nb_users1-nb_users2-nb_users3;
	
	nb_sub1 = 32;
	nb_sub2 = 32;
	nb_sub3 = 32;
	nb_sub4 = 32;
	
	initAntenne(&Antenne1, nb_users1);
	initAntenne(&Antenne2, nb_users2);
	initAntenne(&Antenne3, nb_users3);
	initAntenne(&Antenne4, nb_users4);
	
	/*---INITIALISATIONS---*/
	printf("\nSIMULATION NTR\n\n");
	/*printf("Nombre d'utilisateur pour la simulation: ");
	scanf("%d", &nb_user);*/
	printf("Nombre de tours pour la simulation: ");
	scanf("%d", &nb_tours);
	printf("Algorithme : 1 pour RR, 2 pour MAXSNR, 3 pour PF :");
	scanf("%d", &choixAlgo);

	fichier = fopen("test.csv", "w+");
	if (fichier != NULL){
		fprintf(fichier,"nb_user=%d;nb_tours=%d;choixAlgo=%d;\n",nb_user, nb_tours, choixAlgo);
		/*fprintf(fichier,"nb_user;debit;delais;delai_proche;delai_loin;sommeDelaisProche;sommeDelaisLoin;nbPaquetsEnvoyesProche;nbPaquetsEnvoyesLoin\n");*/
		if(choixAlgo == 1){
			fprintf(fichier,"nb user RR;debit_ms RR;delais_ms RR; PDOR RR; Bandepassante RR; bit par UR RR; nbpaquet envoyer RR; debitant1; debitant2; debitant3; debitant4; delaisant1; delaisant2; delaisant3; delaisant4; PDORant1; PDORant2; PDORant3; PDORant4; nb_users1; nb_users2; nb_users3; nb_users4; nbsub1; nbsub2; nbsub3; nbsub4\n");
		}else if(choixAlgo == 2){
			fprintf(fichier,"nb user MAXSNR;debit_ms MAXSNR;delais_ms MAXSNR; PDOR MAXSNR; Bandepassante MAXSNR; bit par UR MAXSNR; nbpaquet envoyer MAXSNR; debitant1; debitant2; debitant3; debitant4; delaisant1; delaisant2; delaisant3; delaisant4; PDORant1; PDORant2; PDORant3; PDORant4; nb_users1; nb_users2; nb_users3; nb_users4; nbsub1; nbsub2; nbsub3; nbsub4\n");	
		}else if(choixAlgo == 3){
			fprintf(fichier,"nb user PF;debit_ms PF;delais_ms PF; PDOR PF; Bandepassante PF; bit par UR PF; nbpaquet envoyer PF; debitant1; debitant2; debitant3; debitant4; delaisant1; delaisant2; delaisant3; delaisant4; PDORant1; PDORant2; PDORant3; PDORant4; nb_users1; nb_users2; nb_users3; nb_users4; nbsub1; nbsub2; nbsub3; nbsub4\n");	
		}
		fclose(fichier);
	}

	while(nb_user <= 150){
		
		/*ALLOUE DYNAMIQUEMENT LES SUB*/
		/*nb_users1 = (rand() % (int)((nb_user / 2)-5)) + 5;
		nb_users2 = (rand() % (int)((nb_user / 2)-5)) + 5;
		nb_users3 = (rand() % (int)((nb_user / 2)-5)) + 5;
		nb_users4 = nb_user-nb_users1-nb_users2-nb_users3;*/

		nb_users1 = nb_user/4;
		nb_users2 = nb_user/4;
		nb_users3 = nb_user/4;
		nb_users4 = nb_user - nb_users1 -  nb_users2 - nb_users3;
		/*printf("nbuser %d %d %d %d\n",nb_users1,nb_users2,nb_users3,nb_users4);*/
		
		
		/*printf("\nnombre utilisateur : %d subcarrier : %d\n", nb_user_temp,NB_SUBCARRIERS);*/
		
		/*on donne un nb de subcarrier proportionel au nb de user */
		/*
		nb_user_temp = nb_users1 + nb_users2 + nb_users3 + nb_users4;
		nb_sub1 = ((double)nb_users1/(double)nb_user_temp)*NB_SUBCARRIERS;
		nb_sub2 = ((double)nb_users2/(double)nb_user_temp)*NB_SUBCARRIERS;
		nb_sub3 = ((double)nb_users3/(double)nb_user_temp)*NB_SUBCARRIERS;
		nb_sub4 = ((double)nb_users4/(double)nb_user_temp)*NB_SUBCARRIERS;*/
		/*if(nb_user > 4 && (PDOR_ant1_temp+PDOR_ant2_temp+PDOR_ant3_temp+PDOR_ant4_temp) != 0){
			nb_sub1 = 5+(int)(((double)PDOR_ant1_temp / ((double)(PDOR_ant1_temp+PDOR_ant2_temp+PDOR_ant3_temp+PDOR_ant4_temp))) * (128-5));
			nb_sub2 = 5+(int)(((double)PDOR_ant2_temp / ((double)(PDOR_ant1_temp+PDOR_ant2_temp+PDOR_ant3_temp+PDOR_ant4_temp))) * (128-5));
			nb_sub3 = 5+(int)(((double)PDOR_ant3_temp / ((double)(PDOR_ant1_temp+PDOR_ant2_temp+PDOR_ant3_temp+PDOR_ant4_temp))) * (128-5));
			nb_sub4 = 5+(int)(((double)PDOR_ant4_temp / ((double)(PDOR_ant1_temp+PDOR_ant2_temp+PDOR_ant3_temp+PDOR_ant4_temp))) * (128-5));
		}else{
			nb_sub1 = 32;
			nb_sub2 = 32;
			nb_sub3 = 32;
			nb_sub4 = 32;
			
		}
		*/
		nb_sub1 = 32;
		nb_sub2 = 32;
		nb_sub3 = 32;
		nb_sub4 = 32;
		
		/*printf("\nnombre sub 1 a allouer : %.1f\n", subSwitch[0]);
		printf("\nnombre sub 2 a allouer : %.1f\n", subSwitch[1]);
		printf("\nnombre sub 3 a allouer : %.1f\n", subSwitch[2]);
		printf("\nnombre sub 4 a allouer : %.1f\n", subSwitch[3]);*/

			
		/*---BOUCLE PRINCIPALE---*/
		for(i = 0; i < nb_tours; i++){
			
			/*Application de l'algorithme et ôtage des bits envoyés avec RR
			debitTotal += RR(&monAntenne);*/

			/*Application de l'algorithme et ôtage des bits envoyés avec maxSNR*/
			produceBit(&Antenne1, nb_users1);
			initMatriceDebits(&Antenne1, nb_users1);
			
			produceBit_Stable(&Antenne2, nb_users2);
			initMatriceDebits_Stable(&Antenne2, nb_users2);
			
			produceBit_Stable(&Antenne3, nb_users3);
			initMatriceDebits_Stable(&Antenne3, nb_users3);
			
			produceBit_Stable(&Antenne4, nb_users4);
			initMatriceDebits_Stable(&Antenne4, nb_users4);
			
			if(choixAlgo == 1){
				debitTotal_ant1 += RR(&Antenne1, nb_users1, nb_sub1);
				debitTotal_ant2 += RR_Stable(&Antenne2, nb_users2, nb_sub2);
				debitTotal_ant3 += RR_Stable(&Antenne3, nb_users3, nb_sub3);
				debitTotal_ant4 += RR_Stable(&Antenne4, nb_users4, nb_sub4);
			}else if(choixAlgo == 2){
				debitTotal_ant1 += maxSNR(&Antenne1, nb_users1, nb_sub1);
				debitTotal_ant2 += maxSNR_Stable(&Antenne2, nb_users2, nb_sub2);
				debitTotal_ant3 += maxSNR_Stable(&Antenne3, nb_users3, nb_sub3);
				debitTotal_ant4 += maxSNR_Stable(&Antenne4, nb_users4, nb_sub4);
			}else if(choixAlgo == 3){
				/*debitTotal_ant1 += PF(&Antenne1, nb_users1, nb_sub1);
				debitTotal_ant2 += PF(&Antenne2, nb_users2, nb_sub2);
				debitTotal_ant3 += PF(&Antenne3, nb_users3, nb_sub3);
				debitTotal_ant4 += PF(&Antenne4, nb_users4, nb_sub4);*/
			}else{
				printf("choix de l'algorithme mauvais. Arret. \n");
			}

			for(k = 0; k< nb_users1; k++){
				PDOR_temps_ant1 += Antenne1.users[k]->sommeDelaisPDOR_tpsreel;
				consommer_temps_ant1 += Antenne1.users[k]->sommePaquets_consommer_tpsreel;
				Antenne1.users[k]->sommeDelaisPDOR_tpsreel = 0;
				Antenne1.users[k]->sommePaquets_consommer_tpsreel = 0;
			}
			for(k = 0; k< nb_users2; k++){
				PDOR_temps_ant2 += Antenne2.users[k]->sommeDelaisPDOR_tpsreel;
				consommer_temps_ant2 += Antenne2.users[k]->sommePaquets_consommer_tpsreel;
				Antenne2.users[k]->sommeDelaisPDOR_tpsreel = 0;
				Antenne2.users[k]->sommePaquets_consommer_tpsreel = 0;
			}
			for(k = 0; k< nb_users3; k++){
				PDOR_temps_ant3 += Antenne3.users[k]->sommeDelaisPDOR_tpsreel;
				consommer_temps_ant3 += Antenne3.users[k]->sommePaquets_consommer_tpsreel;
				Antenne3.users[k]->sommeDelaisPDOR_tpsreel = 0;
				Antenne3.users[k]->sommePaquets_consommer_tpsreel = 0;
			}
			for(k = 0; k< nb_users4; k++){
				PDOR_temps_ant4 += Antenne4.users[k]->sommeDelaisPDOR_tpsreel;
				consommer_temps_ant4 += Antenne4.users[k]->sommePaquets_consommer_tpsreel;
				Antenne4.users[k]->sommeDelaisPDOR_tpsreel = 0;
				Antenne4.users[k]->sommePaquets_consommer_tpsreel = 0;
			}
			
			consommer_temps = consommer_temps_ant1 + consommer_temps_ant2 + consommer_temps_ant3 + consommer_temps_ant4;
			PDOR_temps = PDOR_temps_ant1 + PDOR_temps_ant2 + PDOR_temps_ant3 + PDOR_temps_ant4;
			
			PDOR_temp=((double)PDOR_temps/((double)(consommer_temps)))*100;
			PDOR_ant1_temp=((double)PDOR_temps_ant1/((double)(consommer_temps_ant1)))*100;
			PDOR_ant2_temp=((double)PDOR_temps_ant2/((double)(consommer_temps_ant2)))*100;
			PDOR_ant3_temp=((double)PDOR_temps_ant3/((double)(consommer_temps_ant3)))*100;
			PDOR_ant4_temp=((double)PDOR_temps_ant4/((double)(consommer_temps_ant4)))*100;
			
			if(nb_user > 4 && (PDOR_ant1_temp+PDOR_ant2_temp+PDOR_ant3_temp+PDOR_ant4_temp) != 0){
				nb_sub1 = 8+((int)(((double)PDOR_ant1_temp / ((double)(PDOR_ant1_temp+PDOR_ant2_temp+PDOR_ant3_temp+PDOR_ant4_temp))) * (128-32)));
				nb_sub2 = 8+((int)(((double)PDOR_ant2_temp / ((double)(PDOR_ant1_temp+PDOR_ant2_temp+PDOR_ant3_temp+PDOR_ant4_temp))) * (128-32)));
				nb_sub3 = 8+((int)(((double)PDOR_ant3_temp / ((double)(PDOR_ant1_temp+PDOR_ant2_temp+PDOR_ant3_temp+PDOR_ant4_temp))) * (128-32)));
				nb_sub4 = 8+((int)(((double)PDOR_ant4_temp / ((double)(PDOR_ant1_temp+PDOR_ant2_temp+PDOR_ant3_temp+PDOR_ant4_temp))) * (128-32)));
				
				if((nb_sub1+nb_sub2+nb_sub3+nb_sub4) < 128){
					
					nb_sub_restant = 128 - (nb_sub1+nb_sub2+nb_sub3+nb_sub4);
					if((nb_sub1 >= nb_sub2) && (nb_sub1 >= nb_sub3) && (nb_sub1 >= nb_sub4)){
						nb_sub1 = nb_sub1 + nb_sub_restant;
						nb_sub_restant=0;
					}
					if((nb_sub2 >= nb_sub1) && (nb_sub2 >= nb_sub3) && (nb_sub2 >= nb_sub4)){
						nb_sub2 = nb_sub2 + nb_sub_restant;
						nb_sub_restant=0;
					}
					if((nb_sub3 >= nb_sub2)&& (nb_sub3 >= nb_sub1) && (nb_sub3 >= nb_sub4)){
						nb_sub3 = nb_sub3 + nb_sub_restant;
						nb_sub_restant=0;
					}
					if((nb_sub4 >= nb_sub2) && (nb_sub4 >= nb_sub3) && (nb_sub4 >= nb_sub1)){
						nb_sub4 = nb_sub4 + nb_sub_restant;
						nb_sub_restant=0;
					}
				}
				
			}else{
				nb_sub1 = 32;
				nb_sub2 = 32;
				nb_sub3 = 32;
				nb_sub4 = 32;
			}/*regarder qui est dans le merde et lui donner le rab de subcarrier*/
		
			Antenne1.actualTime += 2;
			Antenne2.actualTime += 2;
			Antenne3.actualTime += 2;
			Antenne4.actualTime += 2;
			
		}
		
		
		
		for(i = 0; i< nb_users1; i++){
			user_sommeUR_ant1 += Antenne1.users[i]->sommeUR;
			nbPaquetsTotalPDOR_ant1 += Antenne1.users[i]->sommeDelaisPDOR;
			sommeDelais_ant1 += Antenne1.users[i]->sommeDelais;
			nbPaquetsTotal_ant1 += Antenne1.users[i]->sommePaquets;
			nbPaquetsconsommer_ant1 += Antenne1.users[i]->sommePaquets_consommer;
			/* Récupération des délais et nb de paquets restants dans les paquets non envoyes */
			if(Antenne1.users[i]->lePaquet != NULL){

				tmpPacket = Antenne1.users[i]->lePaquet;
				while(tmpPacket->nextPacket != NULL){
					nbPaquetsNonEnvoyes_ant1++;
					tmpPacket = tmpPacket->nextPacket;
				}
			}
		}
		for(i = 0; i< nb_users2; i++){
			user_sommeUR_ant2 += Antenne2.users[i]->sommeUR;
			nbPaquetsTotalPDOR_ant2 += Antenne2.users[i]->sommeDelaisPDOR;
			sommeDelais_ant2 += Antenne2.users[i]->sommeDelais;
			nbPaquetsTotal_ant2 += Antenne2.users[i]->sommePaquets;
			nbPaquetsconsommer_ant2 += Antenne2.users[i]->sommePaquets_consommer;
			/* Récupération des délais et nb de paquets restants dans les paquets non envoyes */
			if(Antenne2.users[i]->lePaquet != NULL){

				tmpPacket = Antenne2.users[i]->lePaquet;
				while(tmpPacket->nextPacket != NULL){
					nbPaquetsNonEnvoyes_ant2++;
					tmpPacket = tmpPacket->nextPacket;
				}
			}
		}
		for(i = 0; i< nb_users3; i++){
			user_sommeUR_ant3 += Antenne3.users[i]->sommeUR;
			nbPaquetsTotalPDOR_ant3 += Antenne3.users[i]->sommeDelaisPDOR;
			sommeDelais_ant3 += Antenne3.users[i]->sommeDelais;
			nbPaquetsTotal_ant3 += Antenne3.users[i]->sommePaquets;
			nbPaquetsconsommer_ant3 += Antenne3.users[i]->sommePaquets_consommer;
			/* Récupération des délais et nb de paquets restants dans les paquets non envoyes */
			if(Antenne3.users[i]->lePaquet != NULL){

				tmpPacket = Antenne3.users[i]->lePaquet;
				while(tmpPacket->nextPacket != NULL){
					nbPaquetsNonEnvoyes_ant3++;
					tmpPacket = tmpPacket->nextPacket;
				}
			}
		}
		for(i = 0; i< nb_users4; i++){
			user_sommeUR_ant4 += Antenne4.users[i]->sommeUR;
			nbPaquetsTotalPDOR_ant4 += Antenne4.users[i]->sommeDelaisPDOR;
			sommeDelais_ant4 += Antenne4.users[i]->sommeDelais;
			nbPaquetsTotal_ant4 += Antenne4.users[i]->sommePaquets;
			nbPaquetsconsommer_ant4 += Antenne4.users[i]->sommePaquets_consommer;
			/* Récupération des délais et nb de paquets restants dans les paquets non envoyes */
			if(Antenne4.users[i]->lePaquet != NULL){

				tmpPacket = Antenne4.users[i]->lePaquet;
				while(tmpPacket->nextPacket != NULL){
					nbPaquetsNonEnvoyes_ant4++;
					tmpPacket = tmpPacket->nextPacket;
				}
			}
		}
		debitTotal = debitTotal_ant1 + debitTotal_ant2 + debitTotal_ant3 + debitTotal_ant4;
		user_sommeUR = user_sommeUR_ant1 + user_sommeUR_ant2 + user_sommeUR_ant3 + user_sommeUR_ant4;
		nbPaquetsTotalPDOR = nbPaquetsTotalPDOR_ant1 + nbPaquetsTotalPDOR_ant2 + nbPaquetsTotalPDOR_ant3 + nbPaquetsTotalPDOR_ant4;
		sommeDelais = sommeDelais_ant1 + sommeDelais_ant2 + sommeDelais_ant3 + sommeDelais_ant4;
		nbPaquetsTotal = nbPaquetsTotal_ant1 + nbPaquetsTotal_ant2 + nbPaquetsTotal_ant3 + nbPaquetsTotal_ant4;
		nbPaquetsNonEnvoyes = nbPaquetsNonEnvoyes_ant1 + nbPaquetsNonEnvoyes_ant2 + nbPaquetsNonEnvoyes_ant3 + nbPaquetsNonEnvoyes_ant4;
		nbPaquetsconsommer = nbPaquetsconsommer_ant1 + nbPaquetsconsommer_ant2 + nbPaquetsconsommer_ant3 + nbPaquetsconsommer_ant4;
		
		res_sommeUR = ((double)(user_sommeUR)/(double)(5*128*nb_tours))*100;
		res_sommeUR_ant1 = ((double)(user_sommeUR_ant1)/(double)(5*128*nb_tours))*100;
		res_sommeUR_ant2 = ((double)(user_sommeUR_ant2)/(double)(5*128*nb_tours))*100;
		res_sommeUR_ant3 = ((double)(user_sommeUR_ant3)/(double)(5*128*nb_tours))*100;
		res_sommeUR_ant4 = ((double)(user_sommeUR_ant4)/(double)(5*128*nb_tours))*100;
		
		bit_par_UR = debitTotal/((double)user_sommeUR);
		bit_par_UR_ant1 = debitTotal_ant1/((double)user_sommeUR_ant1);
		bit_par_UR_ant2 = debitTotal_ant2/((double)user_sommeUR_ant2);
		bit_par_UR_ant3 = debitTotal_ant3/((double)user_sommeUR_ant3);
		bit_par_UR_ant4 = debitTotal_ant4/((double)user_sommeUR_ant4);
		
		PDOR=((double)nbPaquetsTotalPDOR/((double)(nbPaquetsTotal-nbPaquetsNonEnvoyes)))*100;
		PDOR_ant1=((double)nbPaquetsTotalPDOR_ant1/((double)(nbPaquetsconsommer_ant1)))*100;
		PDOR_ant2=((double)nbPaquetsTotalPDOR_ant2/((double)(nbPaquetsconsommer_ant2)))*100;
		PDOR_ant3=((double)nbPaquetsTotalPDOR_ant3/((double)(nbPaquetsconsommer_ant3)))*100;
		PDOR_ant4=((double)nbPaquetsTotalPDOR_ant4/((double)(nbPaquetsconsommer_ant4)))*100;
		
		debit_ms = ((double)debitTotal)/((double)nb_tours*2);
		debit_ms_ant1 = ((double)debitTotal_ant1)/((double)Antenne1.actualTime);
		debit_ms_ant2 = ((double)debitTotal_ant2)/((double)Antenne2.actualTime);
		debit_ms_ant3 = ((double)debitTotal_ant3)/((double)Antenne3.actualTime);
		debit_ms_ant4 = ((double)debitTotal_ant4)/((double)Antenne4.actualTime);
		
		
		delais_ms = (double)(sommeDelais/(nbPaquetsconsommer));
		delais_ms_ant1 = (double)(sommeDelais_ant1/(nbPaquetsconsommer_ant1));
		delais_ms_ant2 = (double)(sommeDelais_ant2/(nbPaquetsconsommer_ant2));
		delais_ms_ant3 = (double)(sommeDelais_ant3/(nbPaquetsconsommer_ant3));
		delais_ms_ant4 = (double)(sommeDelais_ant4/(nbPaquetsconsommer_ant4));
		
		printf("--------------------------------------------------------------\n");
		printf("Statistiques pour %d utilisateurs: \n", nb_user);
		printf("	User ant1 %d || ant2 %d || ant3 %d || ant4 %d || total %d \n", nb_users1, nb_users2, nb_users3, nb_users4, nb_users1+nb_users2+nb_users3+nb_users4);
		printf("	SUBcarrier ant1 %d || ant2 %d || ant3 %d || ant4 %d || total %d \n", nb_sub1, nb_sub2, nb_sub3, nb_sub4, nb_sub1+nb_sub2+nb_sub3+nb_sub4);
		printf("	Débit total simulation : %d bits || %.2f bits/ms\n", debitTotal, debit_ms);
		printf("	Débit total antenne 1 : %d bits || %.2f bits/ms\n", debitTotal_ant1, debit_ms_ant1);
		printf("	Débit total antenne 2 : %d bits || %.2f bits/ms\n", debitTotal_ant2, debit_ms_ant2);
		printf("	Débit total antenne 3 : %d bits || %.2f bits/ms\n", debitTotal_ant3, debit_ms_ant3);
		printf("	Débit total antenne 4 : %d bits || %.2f bits/ms\n", debitTotal_ant4, debit_ms_ant4);
		printf("	Somme des delais : %.3f ms || Delai moyen : %.3f ms\n", sommeDelais, delais_ms);
		printf("	Somme des delais antenne 1 : %.3f ms || Delai moyen antenne 1 : %.3f ms\n", sommeDelais_ant1, delais_ms_ant1);
		printf("	Somme des delais antenne 2 : %.3f ms || Delai moyen antenne 2 : %.3f ms\n", sommeDelais_ant2, delais_ms_ant2);
		printf("	Somme des delais antenne 3 : %.3f ms || Delai moyen antenne 3 : %.3f ms\n", sommeDelais_ant3, delais_ms_ant3);
		printf("	Somme des delais antenne 4 : %.3f ms || Delai moyen antenne 4 : %.3f ms\n", sommeDelais_ant4, delais_ms_ant4);
		printf("	PDOR : %d || ant 1 : %d || ant 2 : %d || ant 3 : %d || ant 4 : %d\n",PDOR, PDOR_ant1, PDOR_ant2, PDOR_ant3, PDOR_ant4);
		printf("	Pourcentage de bande passante utilisé : %.2f || ant 1 : %.2f || ant 2 : %.2f || ant 3 : %.2f || ant 4 : %.2f \n",res_sommeUR, res_sommeUR_ant1, res_sommeUR_ant2, res_sommeUR_ant3, res_sommeUR_ant4);
		printf("	Bit par Unité de ressource : %.2f || ant 1 : %.2f || ant 2 : %.2f || ant 3 : %.2f || ant 4 : %.2f \n",bit_par_UR, bit_par_UR_ant1, bit_par_UR_ant2, bit_par_UR_ant3, bit_par_UR_ant4);
		printf("	nbPaquetsTotal : %d || nbPaquetsNonEnvoyes : %d || nbPaquetEnvoyes : %d || addition : %d\n", nbPaquetsTotal, nbPaquetsNonEnvoyes,  nbPaquetsconsommer, nbPaquetsconsommer+nbPaquetsNonEnvoyes);
		printf("	nbPaquetEnvoyes ant 1 : %d || nbPaquetEnvoyes ant 2 : %d || nbPaquetEnvoyes ant 3 : %d || nbPaquetEnvoyes ant 4 : %d \n",nbPaquetsconsommer_ant1, nbPaquetsconsommer_ant2, nbPaquetsconsommer_ant3, nbPaquetsconsommer_ant4);
		

		fichier = fopen("test.csv", "a");
		if (fichier != NULL)
		{
	 
		 fprintf(fichier,"%d;%.2f;%.2f;%d;%.2f;%.2f;%d;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n", nb_user, debit_ms, delais_ms, PDOR, res_sommeUR, bit_par_UR, nbPaquetsconsommer, debit_ms_ant1, debit_ms_ant2, debit_ms_ant3, debit_ms_ant4,
		 delais_ms_ant1, delais_ms_ant2, delais_ms_ant3, delais_ms_ant4, PDOR_ant1, PDOR_ant2, PDOR_ant3, PDOR_ant4, nb_users1, nb_users2, nb_users3, nb_users4, nb_sub1, nb_sub2, nb_sub3, nb_sub4);
	 
			fclose(fichier);
		}
		
		/*ENVOI DE LA TRAME */

		/*Changement du nombre d'utilisateur*/
		/*
		nb_users1 = userSwitch[(indice)%4];
		nb_users2 = userSwitch[(indice+1)%4];
		nb_users3 = userSwitch[(indice+2)%4];
		nb_users4 = userSwitch[(indice+3)%4];*/

		/*Allocation du nombre de frequences*/
		/*
		nb_sub1 = subSwitch[(indice)%4];
		nb_sub2 = subSwitch[(indice+1)%4];
		nb_sub3 = subSwitch[(indice+2)%4];
		nb_sub4 = subSwitch[(indice+3)%4];*/

		indice = (indice + 1) % 4;
		nb_sub_restant =0;
		debit_ms = 0;
		debit_ms_ant1 = 0;
		debit_ms_ant2 = 0;
		debit_ms_ant3 = 0;
		debit_ms_ant4 = 0;
		
		delais_ms = 0;
		delais_ms_ant1 = 0;
		delais_ms_ant2 = 0;
		delais_ms_ant3 = 0;
		delais_ms_ant4 = 0;
		
		/*PDOR = 0;
		PDOR_ant1 = 0;
		PDOR_ant2 = 0;
		PDOR_ant3 = 0;
		PDOR_ant4 = 0;*/
		
		nbPaquetsconsommer_ant1=0;
		nbPaquetsconsommer_ant2=0;
		nbPaquetsconsommer_ant3=0;
		nbPaquetsconsommer_ant4=0;
		nbPaquetsconsommer=0;
		
		bit_par_UR = 0;
		bit_par_UR_ant1 = 0;
		bit_par_UR_ant2 = 0;
		bit_par_UR_ant3 = 0;
		bit_par_UR_ant4 = 0;
		
		user_sommeUR = 0;
		user_sommeUR_ant1 = 0;
		user_sommeUR_ant2 = 0;
		user_sommeUR_ant3 = 0;
		user_sommeUR_ant4 = 0;
		
		res_sommeUR =0;
		res_sommeUR_ant1 =0;
		res_sommeUR_ant2 =0;
		res_sommeUR_ant3 =0;
		res_sommeUR_ant4 =0;
		
		nbPaquetsTotalPDOR = 0;
		nbPaquetsTotalPDOR_ant1 = 0;
		nbPaquetsTotalPDOR_ant2 = 0;
		nbPaquetsTotalPDOR_ant3 = 0;
		nbPaquetsTotalPDOR_ant4 = 0;
		
		debitTotal_ant1 = 0;
		debitTotal_ant2 = 0;
		debitTotal_ant3 = 0;
		debitTotal_ant4 = 0;
		debitTotal=0;
		
		nbPaquetsTotal=0;
		nbPaquetsTotal_ant1=0;
		nbPaquetsTotal_ant3=0;
		nbPaquetsTotal_ant2=0;
		nbPaquetsTotal_ant4=0;
		
		nbPaquetsNonEnvoyes=0;
		nbPaquetsNonEnvoyes_ant1=0;
		nbPaquetsNonEnvoyes_ant2=0;
		nbPaquetsNonEnvoyes_ant3=0;
		nbPaquetsNonEnvoyes_ant4=0;
		
		sommeDelais_ant1 = 0;
		sommeDelais_ant2 = 0;
		sommeDelais_ant3 = 0;
		sommeDelais_ant4 = 0;
	
		nb_users1 = nb_user;
		nb_users2 = nb_user;
		nb_users3 = nb_user;
		nb_users4 = nb_user;

		
		sommeDelais=0;
		
		initAntenne(&Antenne1, nb_users1);
		initAntenne(&Antenne2, nb_users2);
		initAntenne(&Antenne3, nb_users3);
		initAntenne(&Antenne4, nb_users4);
		
		nb_user=nb_user+4;
	}

	return 0;
}