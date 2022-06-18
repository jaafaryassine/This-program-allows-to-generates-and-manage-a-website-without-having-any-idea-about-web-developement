#include<stdio.h>
#include<stdlib.h>
typedef struct{
	int identif;
	char date_retour[20];
	char nom[30];
	int avertissement;
	long ref_liv;
	char date_emprunt[20];
	
	
}emprunteur;



emprunteur saisirEmprunteur(){
		emprunteur e;
			printf("donner l'identificateur d'emrunteur");
	scanf("%d",&e.identif);
	fflush(stdin);
	printf("donner le nom complet d'emrunteur");
	scanf("%s",e.nom);
		fflush(stdin);
	printf("donner la reference de  livre emprunter");
	scanf("%ld",&e.ref_liv);
		fflush(stdin);
	printf("donner le nombre d'avertissement d'emprunteur ");
	scanf("%d",&e.avertissement);
		fflush(stdin);
	printf("donner la date d'emprunte");
	scanf("%s",e.date_emprunt);
		fflush(stdin);
	printf("donner la date de retour");
	scanf("%s",e.date_retour);
		fflush(stdin);
	return e;
}

emprunteur chercherEmprunteur(char *nom_fich,int id){
    FILE *f_in=fopen(nom_fich,"rb");
    emprunteur e;
    if(f_in!=NULL){
        while(!feof(f_in)){
        if(fread(&e,sizeof(emprunteur),1,f_in)!=0){
        if(e.identif==id){
        printf("l'emprunteur \n identificateur:%d \n nom complet:%s \n reference de livre emprunter:%ld \n nom d'avertissement:%d  \n date d emprt :%s date de retour:%s ",e.identif,e.nom,e.ref_liv,e.avertissement,e.date_emprunt,e.date_retour);
            fclose(f_in);
            return e;
        }
        }
        }
    }
    fclose(f_in);
}


void updatePageListerEmp(char *nomfich){
	FILE *fichier=fopen(nomfich,"rb");
	FILE *f_out=fopen("listeremprunteur.html","w+");
	emprunteur e;
	fprintf(f_out,"<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.0-beta1/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-0evHe/X+R7YkIZDRvuzKMRqM+OrBnVFBL6DOitfPri4tjfHxaWutUpFmBp4vmVor\" crossorigin=\"anonymous\">");
	fprintf(f_out,"<h2 style=\"text-align:center;margin-top:70px;margin-bottom:30px; \">Les Emprunteurs</h2>");
	fprintf(f_out,"<table class=\"table\">");
	fprintf(f_out,"<thead><tr><th scope=\"col\">Id</th><th scope=\"col\">Nom</th><th scope=\"col\">Date_emprunt</th><th scope=\"col\">Date_retour</th><th scope=\"col\">Ref du livre emprunté</th><th scope=\"col\">Avertissement</th></tr></thead>");

	if(fichier!=NULL && f_out!=NULL){
		while(!feof(fichier)){
			if(fread(&e,sizeof(emprunteur),1,fichier)){
				fprintf(f_out,"<tr> <th scope=\"row\"> %d </th> <td>%s</td> <td> %s</td> <td> %s </td> <td> %ld </td> <td> %d </td>",e.identif,e.nom,e.date_emprunt,e.date_retour,e.ref_liv,e.avertissement);
			}	
		}
	}
	fclose(f_out);
	fclose(fichier);
	printf(" \n La page lister emprunteur a ete mis à jour \n");
	}
	

void ajouterEmprunteur(char* nomfich,emprunteur e){
	FILE *fichier=fopen(nomfich,"ab+");
	emprunteur emp;
	emp=chercherEmprunteur(nomfich,e.identif);
	if(emp.identif!=e.identif){
	if(fichier!=NULL){
		fwrite(&e,sizeof(emprunteur),1,fichier);
	}
}
	else{
		printf("\n Ce compte existe deja ! Attention l'idenitifiant de l'emprunteur est unique /n");
	}
	fclose(fichier);
	updatePageListerEmp(nomfich);
}
void listeremprunteur(char *nomfich){
	FILE *fichier=fopen(nomfich,"rb");
	emprunteur e;
	if(fichier!=NULL){
		while(!feof(fichier)){
			 if(fread(&e,sizeof(emprunteur),1,fichier)!=0){

			printf("l'emprunteur \n identificateur:%d \n nom complet:%s \n reference de livre emprunter:%ld \n nom d'avertissement:%d  \n date d emprt :%s date de retour:%s ",e.identif,e.nom,e.ref_liv,e.avertissement,e.date_emprunt,e.date_retour);
		}
}
}
	fclose(fichier);

}

void supprimerEmprunteur(char * nomfich,int identif){
	FILE *fichier=fopen(nomfich,"rb");
		FILE *fichier1=fopen("emprunt.bin","wb");
		emprunteur e;
	if(fichier!=NULL && fichier1!=NULL){
		while(!feof(fichier)){
			if(fread(&e,sizeof(emprunteur),1,fichier)!=0){
			if(e.identif!=identif){
				fwrite(&e,sizeof(emprunteur),1,fichier1);
			}
			
		}
		}	
	}
	fclose(fichier);
	fclose(fichier1);
	remove(nomfich);
    rename("emprunt.bin",nomfich);
    updatePageListerEmp(nomfich);

}



//void modifier(char*nomfich,int identif){
//		supprimer(nomfich,identif);
//         ajouter(nomfich,saisir());
//
//
// 
//	printf("Modfication ok!!");
//}



emprunteur modifierEmprunteur(char *nom_fich,int id){
    emprunteur emp;
    char choix;
    emp=chercherEmprunteur(nom_fich,id);
    if(emp.identif==id){
    supprimerEmprunteur(nom_fich,id);
    fflush(stdin);
    printf("\n Vous voulez modifier le nom o|n \n");
    choix=getchar();
    if(choix=='o'){
        scanf("%s",emp.nom);
    }
    fflush(stdin);
    printf("\n Vous voulez modifier le  nb d avertissement o|n \n");
    choix=getchar();
    if(choix=='o'){
        scanf("%d",&emp.avertissement);
    }
    fflush(stdin);
    printf("\n Vous voulez modifier le ref_livre emprunte o|n \n");
    choix=getchar();
    if(choix=='o'){
        scanf("%ld",&emp.ref_liv);
    }
     fflush(stdin);
    printf("\n Vous voulez modifier date de pret o|n \n");
    choix=getchar();
    if(choix=='o'){
        scanf("%s",emp.date_emprunt);
    }
     fflush(stdin);
    printf("\n Vous voulez modifier la date de retour o|n \n");
    choix=getchar();
    if(choix=='o'){
        scanf("%s",emp.date_retour);
    }
    ajouterEmprunteur(nom_fich,emp);
}
else{
	printf("Compte inexistant \n");
}
}


void creer_page_ajout_emp(){
	if(testerPage(5)==0){
	FILE *f_out=fopen("ajouteremprunteur.html","w+");
	if(f_out!=NULL){
	fprintf(f_out,"<style>body{background-color: #f7f7f7;}.form{margin: auto;margin-top: 100px;background-color: white;width: 400px;height: 250px;border-radius: 16px;padding: 30px;box-shadow: 5px 5px 5px 5px rgb(147, 149, 147);}");
    fprintf(f_out,"input{border: none;outline: 0;background-color: white;width: 100%;}button{margin: auto;margin-top: 20px;border: none; background-color: rgb(48, 149, 48);padding: 15px;border-radius: 16px;}");
    fprintf(f_out,"</style><body><div class=\"form\"><input type=\"text\" placeholder=\"Identifiant de l'emprunteur \"><br> <hr><input type=\"text\" placeholder=\"Nom\"><br> <hr><input type=\"date\" placeholder=\"Date de l'emprunt\"><br> <hr><input type=\"date\" placeholder=\"Date de retour de l'emprunt\"><br> <hr><input type=\"number\" placeholder=\"Référence de livre emprunté\"><br> <hr><center><button>Ajouter</button></center></div></body>");
	printf("Votre page d ajout d'empruteur' a ete bien cree \n");
	ajouterPage(5);
	fclose(f_out);
	}
	}
		else {
		printf("\n La page existe deja \n");
	}
		
}

void creer_page_supp_emp(){
	if(testerPage(7)==0){
	FILE *f_out=fopen("supprimeremprunteur.html","w+");
	if(f_out!=NULL){
	fprintf(f_out,"<style>body{background-color: #f7f7f7;}.form{margin: auto;margin-top: 100px;background-color: white;width: 400px;height: 250px;border-radius: 16px;padding: 30px;box-shadow: 5px 5px 5px 5px rgb(147, 149, 147);}");
    fprintf(f_out,"input{border: none;outline: 0;background-color: white;width: 100%;}button{margin: auto;margin-top: 20px;border: none; background-color: rgb(48, 149, 48);padding: 15px;border-radius: 16px;}");
    fprintf(f_out,"</style><body><div class=\"form\"><input type=\"text\" placeholder=\"Identifiant de l'emprunteur'\"><br> <hr><center><button>Supprimer</button></center></div></body>");
	printf("Votre page de suppresion de livre a ete bien cree \n");
	ajouterPage(7);
	fclose(f_out);
	}
	}
		else {
		printf("\n La page existe deja \n");
	}
}


//int main(){
//int identif;
//emprunteur newe;
//
////	ajouter("emprunteurs.bin",saisir(); 
////	ajouter("emprunteurs.bin",saisir());
////	ajouter("emprunteurs.bin",saisir());
//	listeremprunteur("emprunteurs.bin");
////	modifier("emprunteurs.bin",3);
//
//
//
//
//}
