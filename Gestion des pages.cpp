#include<stdio.h>
#include<stdlib.h>

typedef struct{
	int id;
	int liens[8];
}Page;


int testerPage(int i){
	FILE *f_out=fopen("pages.bin","rb");
	Page p;
	if(f_out!=NULL){
		while(!feof(f_out)){
			if(fread(&p,sizeof(Page),1,f_out)){
				if(p.id==i){
					fclose(f_out);
					return 1;
				}
			}
		}
	}
	fclose(f_out);
	return 0;
}

void ajouterPage(int i){
	FILE *f_out=fopen("pages.bin","ab+");
	Page p;
	p.id=i;
	for(int j=0;j<8;j++){
		p.liens[j]=-1;
	}
	fwrite(&p,sizeof(Page),1,f_out);
	fclose(f_out);
}
int testerLien(int np,int nl){
	FILE* f_in=fopen("pages.bin","rb");
	Page p;
	if(f_in!=NULL){
		while(!feof(f_in)){
			if(fread(&p,sizeof(Page),1,f_in)!=0){
				if(p.id==np){
					for(int i=0;i<8;i++){
						if(p.liens[i]==nl){
							fclose(f_in);
							return 1;
						}
					}	
				}
			}
		}
	}
	fclose(f_in);
	return 0;
}

int positionTab(int tab[8]){
	for(int i=0;i<8;i++){
		if(tab[i]==-1){
			return i;
		}
	}
return -1;
}
void ajouterLien(int np,int nl){
	FILE *f_in=fopen("pages.bin","rb");
	FILE *f_out=fopen("tmp.bin","wb+");
	Page p;
	if(f_in!=NULL && f_out!=NULL){
		while(!feof(f_in)){
			if(fread(&p,sizeof(Page),1,f_in)){
				if(p.id!=np){
					fwrite(&p,sizeof(Page),1,f_out);
				}
				else{
					int i=positionTab(p.liens);
					p.liens[i]=nl;
					fwrite(&p,sizeof(Page),1,f_out);
				}
			}
		}
	}
	fclose(f_in);
	fclose(f_out);
	remove("pages.bin");
	rename("tmp.bin","pages.bin");
}


void importation(char *nomfichier){
	FILE*f_in=fopen(nomfichier,"r+");
	FILE*f_out=fopen("importation.html","w+");
	char* tmp=(char*)malloc(150*sizeof(char*));
	if(f_in!=NULL && f_out!=NULL){
		while(!feof(f_in)){
			if(fscanf(f_in,"%s",tmp)!=-1){
				fprintf(f_out,"%s",tmp);
			}
		}
	printf("\n Votre fichier a ete bien importe \n");
	}
	fclose(f_in);
	fclose(f_out);
	}

void gererLien(){
	char choix,choix2;
	printf("Vous voulez presonnaliser les lien de la page d'acceuil o/n'");
	fflush(stdin);
	choix=getchar();
	if(choix=='o'){
		FILE *f_out=fopen("index.html","a");
		if(f_out!=NULL){
		printf("\n Quel lien vous voulez ajouter dans la page d'acceuil /n '");
		printf("1)\n Lien vers ajouter livre \n");
		printf("2)Lien vers lister livres \n");
		printf("3)Lien vers supprimer livre \n");
		printf("4)Lien vers ajouter emprunteur \n");
		printf("5)Lien vers lister emprunteur \n");
		printf("6)Lien vers supprimer emprunteur \n");



		fflush(stdin);
		choix2=getchar();
		switch(choix2){
			case '1' : if(testerLien(0,2)==0){
						fprintf(f_out,"<a href=\"ajouterlivre.html\" style=\"color:black\">Ajouter livre</a> <br>");
						ajouterLien(0,2);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '2' : if(testerLien(0,3)==0){
						fprintf(f_out,"<a href=\"listerlivres.html\" style=\"color:black\">Lister livre</a> <br>");
						ajouterLien(0,3);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '3' : if(testerLien(0,4)==0){
						fprintf(f_out,"<a href=\"supprimerlivre.html\" style=\"color:black\">Supprimer livre</a> <br>");
						ajouterLien(0,4);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '4' : if(testerLien(0,5)==0){
						fprintf(f_out,"<a href=\"ajouteremprunteur.html\" style=\"color:black\">Ajouter emprunteur</a> <br>");
						ajouterLien(0,5);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '5' : if(testerLien(0,6)==0){
						fprintf(f_out,"<a href=\"listeremprunteur.html\" style=\"color:black\">Lister emprunteur</a> <br>");
						ajouterLien(0,6);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '6' : if(testerLien(0,7)==0){
						fprintf(f_out,"<a href=\"supprimeremprunteur.html\" style=\"color:black\">Supprimer emprunteur</a> <br>");
						ajouterLien(0,7);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
		}
	}
	fclose(f_out);
	}
	
	
	printf("Vous voulez presonnaliser les lien de la page ajouter livre o/n'");
	fflush(stdin);
	choix=getchar();
	if(choix=='o'){
		FILE *f_out=fopen("ajouterlivre.html","a");
		if(f_out!=NULL){
		printf("\n Quel lien vous voulez ajouter dans la page ajouter livre /n '");
		printf("1)\n Lien vers page d'acceuil' \n");
		printf("2)Lien vers lister livres \n");
		printf("3)Lien vers supprimer livre \n");
		printf("4)Lien vers ajouter emprunteur \n");
		printf("5)Lien vers lister emprunteur \n");
		printf("6)Lien vers supprimer emprunteur \n");



		fflush(stdin);
		choix2=getchar();
		switch(choix2){
			case '1' : if(testerLien(2,0)==0){
						fprintf(f_out,"<a href=\"index.html\" style=\"color:black\">Page d'acceuil</a> <br>");
						ajouterLien(2,0);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '2' : if(testerLien(2,3)==0){
						fprintf(f_out,"<a href=\"listerlivres.html\" style=\"color:black\">Lister livre</a> <br>");
						ajouterLien(2,3);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '3' : if(testerLien(2,4)==0){
						fprintf(f_out,"<a href=\"supprimerlivre.html\" style=\"color:black\">Supprimer livre</a> <br>");
						ajouterLien(2,4);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '4' : if(testerLien(2,5)==0){
						fprintf(f_out,"<a href=\"ajouteremprunteur.html\" style=\"color:black\">Ajouter emprunteur</a> <br>");
						ajouterLien(2,5);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '5' : if(testerLien(2,6)==0){
						fprintf(f_out,"<a href=\"listeremprunteur.html\" style=\"color:black\">Lister emprunteur</a> <br>");
						ajouterLien(2,6);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '6' : if(testerLien(2,7)==0){
						fprintf(f_out,"<a href=\"supprimeremprunteur.html\" style=\"color:black\">Supprimer emprunteur</a> <br>");
						ajouterLien(2,7);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
		}
	}
		fclose(f_out);
	}	
	
	
//////	printf("Vous voulez presonnaliser les liens de la page lister livres o/n'");
//////	fflush(stdin);
//////	choix=getchar();
//////	if(choix=='o'){
//////		FILE *f_out=fopen("listerlivres.html","a");
//////		if(f_out!=NULL){
//////		printf("\n Quel lien vous voulez ajouter dans la page lister livres /n '");
//////		printf("1)\n Lien vers page d'acceuil' \n");
//////		printf("2)Lien vers ajouter livre \n");
//////		printf("3)Lien vers supprimer livre \n");
//////		printf("4)Lien vers ajouter emprunteur \n");
//////		printf("5)Lien vers lister emprunteur \n");
//////		printf("6)Lien vers supprimer emprunteur \n");
//////
//////
//////
//////		fflush(stdin);
//////		choix2=getchar();
//////		switch(choix2){
//////			case '1' : if(testerLien(3,0)==0){
//////						fprintf(f_out,"<a href=\"index.html\" style=\"color:black\">Page d'acceuil</a> <br>");
//////						ajouterLien(3,0);
//////						printf("\n Le lien a ete bien ajoute \n");
//////						}
//////						else{
//////							printf("\n Ce lien est deja ajoute \n");
//////						}
//////						break;
//////			case '2' : if(testerLien(3,2)==0){
//////						fprintf(f_out,"<a href=\"ajouterlivre.html\" style=\"color:black\">Ajouter livre</a> <br>");
//////						ajouterLien(3,2);
//////						printf("\n Le lien a ete bien ajoute \n");
//////						}
//////						else{
//////							printf("\n Ce lien est deja ajoute \n");
//////						}
//////						break;
//////			case '3' : if(testerLien(3,4)==0){
//////						fprintf(f_out,"<a href=\"supprimerlivre.html\" style=\"color:black\">Supprimer livre</a> <br>");
//////						ajouterLien(3,4);
//////						printf("\n Le lien a ete bien ajoute \n");
//////						}
//////						else{
//////							printf("\n Ce lien est deja ajoute \n");
//////						}
//////						break;
//////			case '4' : if(testerLien(3,5)==0){
//////						fprintf(f_out,"<a href=\"ajouteremprunteur.html\" style=\"color:black\">Ajouter emprunteur</a> <br>");
//////						ajouterLien(3,5);
//////						printf("\n Le lien a ete bien ajoute \n");
//////						}
//////						else{
//////							printf("\n Ce lien est deja ajoute \n");
//////						}
//////						break;
//////			case '5' : if(testerLien(3,6)==0){
//////						fprintf(f_out,"<a href=\"listeremprunteur.html\" style=\"color:black\">Lister emprunteur</a> <br>");
//////						ajouterLien(3,6);
//////						printf("\n Le lien a ete bien ajoute \n");
//////						}
//////						else{
//////							printf("\n Ce lien est deja ajoute \n");
//////						}
//////						break;
//////			case '6' : if(testerLien(3,7)==0){
//////						fprintf(f_out,"<a href=\"supprimeremprunteur.html\" style=\"color:black\">Supprimer emprunteur</a> <br>");
//////						ajouterLien(3,7);
//////						printf("\n Le lien a ete bien ajoute \n");
//////						}
//////						else{
//////							printf("\n Ce lien est deja ajoute \n");
//////						}
//////						break;
//////		}
//////	}
//////		fclose(f_out);
//////	}
//////	
	
		printf("Vous voulez presonnaliser les liens de la page supprimer livre o/n'");
	fflush(stdin);
	choix=getchar();
	if(choix=='o'){
		FILE *f_out=fopen("supprimerlivre.html","a");
		if(f_out!=NULL){
		printf("\n Quel lien vous voulez ajouter dans la page supprimer livre /n '");
		printf("1)\n Lien vers page d'acceuil \n");
		printf("2)Lien vers ajouter livre \n");
		printf("3)Lien vers lister livre \n");
		printf("4)Lien vers ajouter emprunteur \n");
		printf("5)Lien vers lister emprunteur \n");
		printf("6)Lien vers supprimer emprunteur \n");



		fflush(stdin);
		choix2=getchar();
		switch(choix2){
			case '1' : if(testerLien(4,0)==0){
						fprintf(f_out,"<a href=\"index.html\" style=\"color:black\">Page d'acceuil</a> <br>");
						ajouterLien(4,0);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '2' : if(testerLien(4,2)==0){
						fprintf(f_out,"<a href=\"ajouterlivre.html\" style=\"color:black\">Ajouter livre</a> <br>");
						ajouterLien(4,2);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '3' : if(testerLien(4,3)==0){
						fprintf(f_out,"<a href=\"listerlivres.html\" style=\"color:black\">Lister livres</a> <br>");
						ajouterLien(4,3);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '4' : if(testerLien(4,5)==0){
						fprintf(f_out,"<a href=\"ajouteremprunteur.html\" style=\"color:black\">Ajouter emprunteur</a> <br>");
						ajouterLien(4,5);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '5' : if(testerLien(4,6)==0){
						fprintf(f_out,"<a href=\"listeremprunteur.html\" style=\"color:black\">Lister emprunteur</a> <br>");
						ajouterLien(4,6);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '6' : if(testerLien(4,7)==0){
						fprintf(f_out,"<a href=\"supprimeremprunteur.html\" style=\"color:black\">Supprimer emprunteur</a> <br>");
						ajouterLien(4,7);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
		}
	}
		fclose(f_out);
	}
	
	
	
	
		printf("Vous voulez presonnaliser les liens de la page ajouter emrunteur o/n'");
	fflush(stdin);
	choix=getchar();
	if(choix=='o'){
		FILE *f_out=fopen("ajouteremprunteur.html","a");
		if(f_out!=NULL){
		printf("\n Quel lien vous voulez ajouter dans la page ajouter emprunteur/n '");
		printf("1)\n Lien vers page d'acceuil \n");
		printf("2)Lien vers ajouter livre \n");
		printf("3)Lien vers lister livre \n");
		printf("4)Lien vers supprimer livre \n");
		printf("5)Lien vers lister emprunteur \n");
		printf("6)Lien vers supprimer emprunteur \n");



		fflush(stdin);
		choix2=getchar();
		switch(choix2){
			case '1' : if(testerLien(5,0)==0){
						fprintf(f_out,"<a href=\"index.html\" style=\"color:black\">Page d'acceuil</a> <br>");
						ajouterLien(5,0);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '2' : if(testerLien(5,2)==0){
						fprintf(f_out,"<a href=\"ajouterlivre.html\" style=\"color:black\">Ajouter livre</a> <br>");
						ajouterLien(5,2);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '3' : if(testerLien(5,3)==0){
						fprintf(f_out,"<a href=\"listerlivres.html\" style=\"color:black\">Lister livres</a> <br>");
						ajouterLien(5,3);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '4' : if(testerLien(5,4)==0){
						fprintf(f_out,"<a href=\"supprimerlivre.html\" style=\"color:black\">Supprimer livre</a> <br>");
						ajouterLien(5,4);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '5' : if(testerLien(5,6)==0){
						fprintf(f_out,"<a href=\"listeremprunteur.html\" style=\"color:black\">Lister emprunteur</a> <br>");
						ajouterLien(5,6);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '6' : if(testerLien(5,7)==0){
						fprintf(f_out,"<a href=\"supprimeremprunteur.html\" style=\"color:black\">Supprimer emprunteur</a> <br>");
						ajouterLien(5,7);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
		}
	}
		fclose(f_out);
	}
	
//////	
//////			printf("Vous voulez presonnaliser les liens de la page lister emrunteurs o/n'");
//////	fflush(stdin);
//////	choix=getchar();
//////	if(choix=='o'){
//////		FILE *f_out=fopen("listeremprunteur.html","a");
//////		if(f_out!=NULL){
//////		printf("\n Quel lien vous voulez ajouter dans la page lister emprunteurs /n '");
//////		printf("1)\n Lien vers page d'acceuil \n");
//////		printf("2)Lien vers ajouter livre \n");
//////		printf("3)Lien vers lister livre \n");
//////		printf("4)Lien vers supprimer livre \n");
//////		printf("5)Lien vers ajouter emprunteur \n");
//////		printf("6)Lien vers supprimer emprunteur \n");
//////
//////
//////
//////		fflush(stdin);
//////		choix2=getchar();
//////		switch(choix2){
//////			case '1' : if(testerLien(6,0)==0){
//////						fprintf(f_out,"<a href=\"index.html\" style=\"color:black\">Page d'acceuil</a> <br>");
//////						ajouterLien(6,0);
//////						printf("\n Le lien a ete bien ajoute \n");
//////						}
//////						else{
//////							printf("\n Ce lien est deja ajoute \n");
//////						}
//////						break;
//////			case '2' : if(testerLien(6,2)==0){
//////						fprintf(f_out,"<a href=\"ajouterlivre.html\" style=\"color:black\">Ajouter livre</a> <br>");
//////						ajouterLien(6,2);
//////						printf("\n Le lien a ete bien ajoute \n");
//////						}
//////						else{
//////							printf("\n Ce lien est deja ajoute \n");
//////						}
//////						break;
//////			case '3' : if(testerLien(6,3)==0){
//////						fprintf(f_out,"<a href=\"listerlivres.html\" style=\"color:black\">Lister livres</a> <br>");
//////						ajouterLien(6,3);
//////						printf("\n Le lien a ete bien ajoute \n");
//////						}
//////						else{
//////							printf("\n Ce lien est deja ajoute \n");
//////						}
//////						break;
//////			case '4' : if(testerLien(6,4)==0){
//////						fprintf(f_out,"<a href=\"supprimerlivre.html\" style=\"color:black\">Supprimer livre</a> <br>");
//////						ajouterLien(6,4);
//////						printf("\n Le lien a ete bien ajoute \n");
//////						}
//////						else{
//////							printf("\n Ce lien est deja ajoute \n");
//////						}
//////						break;
//////			case '5' : if(testerLien(6,5)==0){
//////						fprintf(f_out,"<a href=\"ajouteremprunteur.html\" style=\"color:black\">Ajouter emprunteur</a> <br>");
//////						ajouterLien(6,5);
//////						printf("\n Le lien a ete bien ajoute \n");
//////						}
//////						else{
//////							printf("\n Ce lien est deja ajoute \n");
//////						}
//////						break;
//////			case '6' : if(testerLien(6,7)==0){
//////						fprintf(f_out,"<a href=\"supprimeremprunteur.html\" style=\"color:black\">Supprimer emprunteur</a> <br>");
//////						ajouterLien(6,7);
//////						printf("\n Le lien a ete bien ajoute \n");
//////						}
//////						else{
//////							printf("\n Ce lien est deja ajoute \n");
//////						}
//////						break;
//////		}
//////	}
//////		fclose(f_out);
//////	}
//////	
//////	
				printf("Vous voulez presonnaliser les liens de la page supprimer emrunteur o/n'");
	fflush(stdin);
	choix=getchar();
	if(choix=='o'){
		FILE *f_out=fopen("supprimeremprunteur.html","a");
		if(f_out!=NULL){
		printf("\n Quel lien vous voulez ajouter dans la page supprimer emprunteur /n '");
		printf("1)\n Lien vers page d'acceuil \n");
		printf("2)Lien vers ajouter livre \n");
		printf("3)Lien vers lister livre \n");
		printf("4)Lien vers supprimer livre \n");
		printf("5)Lien vers ajouter emprunteur \n");
		printf("6)Lien vers lister emprunteurs \n");



		fflush(stdin);
		choix2=getchar();
		switch(choix2){
			case '1' : if(testerLien(7,0)==0){
						fprintf(f_out,"<a href=\"index.html\" style=\"color:black\">Page d'acceuil</a> <br>");
						ajouterLien(7,0);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '2' : if(testerLien(7,2)==0){
						fprintf(f_out,"<a href=\"ajouterlivre.html\" style=\"color:black\">Ajouter livre</a> <br>");
						ajouterLien(7,2);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '3' : if(testerLien(7,3)==0){
						fprintf(f_out,"<a href=\"listerlivres.html\" style=\"color:black\">Lister livres</a> <br>");
						ajouterLien(7,3);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '4' : if(testerLien(7,4)==0){
						fprintf(f_out,"<a href=\"supprimerlivre.html\" style=\"color:black\">Supprimer livre</a> <br>");
						ajouterLien(7,4);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '5' : if(testerLien(7,5)==0){
						fprintf(f_out,"<a href=\"ajouteremprunteur.html\" style=\"color:black\">Ajouter emprunteur</a> <br>");
						ajouterLien(7,5);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
			case '6' : if(testerLien(7,6)==0){
						fprintf(f_out,"<a href=\"listeremprunteurs.html\" style=\"color:black\">Lister emprunteurs</a> <br>");
						ajouterLien(7,6);
						printf("\n Le lien a ete bien ajoute \n");
						}
						else{
							printf("\n Ce lien est deja ajoute \n");
						}
						break;
		}
	}
		fclose(f_out);
	}
}




