 #include <stdio.h>
#include <string.h>
#include <stdlib.h>

 typedef struct{
 	long ref;
 	char auteur[30];
	char titre[30];
	float prix;	
} livre;



livre saisir(){
	livre v;
	printf("donner la reference de livre");
	scanf("%ld",&v.ref);
	printf("donner le nom de l'auteur");
	scanf("%s",v.auteur);
	printf("donner le titre de livre ");
	scanf("%s",v.titre);
	printf("donner le prix de livre");
	scanf("%f",&v.prix);
	return v;
}

int rechercher(char *nomfich,long reference){
    FILE *fichier=fopen(nomfich,"rb");
    livre v;
    int x=0;
    if(fichier!=NULL){
    	 while(!feof(fichier)){
        if(fread(&v,sizeof(livre),1,fichier)!=0){
    	if(v.ref==reference){
    		printf(" Le livre existe : \n le nom de livre :%s \n le nom de l auteur:%s \n le prix :%lf \n",v.titre,v.auteur,v.prix);
    		x=1;
    		break;
		}
	}
	
}

fclose(fichier);
}
return x;
}

void updatePageListerLivres(char *nomfich){
	FILE *fichier=fopen(nomfich,"rb");
	FILE *f_out=fopen("listerlivres.html","w+");
	livre v;
	fprintf(f_out,"<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.0-beta1/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-0evHe/X+R7YkIZDRvuzKMRqM+OrBnVFBL6DOitfPri4tjfHxaWutUpFmBp4vmVor\" crossorigin=\"anonymous\">");
	fprintf(f_out,"<h2 style=\"text-align:center;margin-top:70px;margin-bottom:30px; \">Les livres de la biliothéque</h2>");
	fprintf(f_out,"<table class=\"table\">");
	fprintf(f_out,"<thead><tr><th scope=\"col\">#</th><th scope=\"col\">Titre</th><th scope=\"col\">Auteur</th><th scope=\"col\">Prix</th></tr></thead>");

	if(fichier!=NULL && f_out!=NULL){
		while(!feof(fichier)){
			if(fread(&v,sizeof(livre),1,fichier)){
				fprintf(f_out,"<tr> <th scope=\"row\"> %ld </th> <td>%s</td> <td> %s</td> <td> %f </td>",v.ref,v.titre,v.auteur,v.prix);
			}	
		}
	}
	fclose(f_out);
	fclose(fichier);
	printf(" \n La page lister livre a ete mis à jour \n");

	}
	

void ajouter(char* nomfich,livre v){
	if(rechercher(nomfich,v.ref)==0){
	
	FILE *fichier=fopen(nomfich,"ab+");
	if(fichier!=NULL){
		fwrite(&v,sizeof(livre),1,fichier);
	}
	fclose(fichier);
	updatePageListerLivres("livres.bin");
}
else {
	printf("Attention ! Reference de livre est unique, ce code de ref existe deja \n");
}
}


void listerlivre(char *nomfich){
	FILE *fichier=fopen(nomfich,"rb");
	livre v;
	if(fichier!=NULL){
		while(!feof(fichier)){
			 if(fread(&v,sizeof(livre),1,fichier)!=0){

			printf("la reference de livre:%ld  \n l auteur:%s  \n le titre:%s  \n le prix:%f  \n",v.ref,v.auteur,v.titre,v.prix);
		}
	 

}
}
	fclose(fichier);

}


void supprimer(char *nomfich, long reference){
	FILE *fichier=fopen(nomfich,"rb");
	FILE *fichier1=fopen("tmp.bin","wb");
	livre v;
	if(fichier!=NULL && fichier1!=NULL){
		while(!feof(fichier)){
			if(fread(&v,sizeof(livre),1,fichier)!=0){
				if(v.ref!=reference){
					fwrite(&v,sizeof(livre),1,fichier1);
		
				}
			}
		}	
	}
	fclose(fichier);
	fclose(fichier1);
	remove(nomfich);
	rename("tmp.bin",nomfich);
	printf("\n la suppression est reussie \n");
	updatePageListerLivres("livres.bin");
}



void creer_page_ajout(){
	if(testerPage(2)==0){
	FILE *f_out=fopen("ajouterlivre.html","w+");
	if(f_out!=NULL){
	fprintf(f_out,"<style>body{background-color: #f7f7f7;}.form{margin: auto;margin-top: 100px;background-color: white;width: 400px;height: 250px;border-radius: 16px;padding: 30px;box-shadow: 5px 5px 5px 5px rgb(147, 149, 147);}");
    fprintf(f_out,"input{border: none;outline: 0;background-color: white;width: 100%;}button{margin: auto;margin-top: 20px;border: none; background-color: rgb(48, 149, 48);padding: 15px;border-radius: 16px;}");
    fprintf(f_out,"</style><body><div class=\"form\"><input type=\"text\" placeholder=\"Reference du livre\"><br> <hr><input type=\"text\" placeholder=\"Titre du livre\"><br> <hr><input type=\"text\" placeholder=\"Auteur du livre\"><br> <hr><input type=\"number\" placeholder=\"Prix du livre\"><br> <hr><center><button>Ajouter</button></center></div></body>");
	printf("Votre page d ajout de livre a ete bien cree \n");
	ajouterPage(2);
	fclose(f_out);
	}
	}
		else {
		printf("\n La page existe deja \n");
	}
}
void creer_page_supp(){
	if(testerPage(4)==0){
	FILE *f_out=fopen("supprimerlivre.html","w+");
	if(f_out!=NULL){
	fprintf(f_out,"<style>body{background-color: #f7f7f7;}.form{margin: auto;margin-top: 100px;background-color: white;width: 400px;height: 250px;border-radius: 16px;padding: 30px;box-shadow: 5px 5px 5px 5px rgb(147, 149, 147);}");
    fprintf(f_out,"input{border: none;outline: 0;background-color: white;width: 100%;}button{margin: auto;margin-top: 20px;border: none; background-color: rgb(48, 149, 48);padding: 15px;border-radius: 16px;}");
    fprintf(f_out,"</style><body><div class=\"form\"><input type=\"text\" placeholder=\"Reference du livre\"><br> <hr><center><button>Supprimer</button></center></div></body>");
	printf("Votre page de suppresion de livre a ete bien cree \n");
	ajouterPage(4);
	fclose(f_out);
	}
	}
		else {
		printf("\n La page existe deja \n");
	}
}



