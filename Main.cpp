#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Gestion des pages.cpp"
#include "Gestion des livres.cpp"
#include "Gestion des emprunteurs.cpp"



char *crypter(char *password){
	char pass_crypte[30];
	int i;
	for(i=0;i<strlen(password);i++){
		if(i % 2==0){
		pass_crypte[i]=password[i]+5;
	}
	else {
		pass_crypte[i]=password[i]+2;
	}
}
  	pass_crypte[i]='\0';
	return pass_crypte;
}

char menu(){
	printf("******** BIENVENUE DANS L'ESPACE ADMINISTRATIF ******** \n") ;
	printf(" 1)Gestion des Livres \n");
	printf(" 2)Gestion des emprunteurs \n");
	printf(" 3)Importer un fichier html  \n");
	printf(" 4)Creer la page d authentification de votre site \n") ;
	printf(" 5)Creer la page d accueil \n") ;
	printf(" 6)Gestion des liens entre les pages web \n") ;
	printf(" q)Quitter q\n") ;
	printf("Saisir votre choix :") ;
	fflush(stdin);
	return getchar();
}

char menu_gerer_livres(){
	char choix;
	long ref;
		do{fflush(stdin);
		printf(" \n 1)Ajouter livre\n") ;
		printf(" 2)Lister livres \n") ;
		printf(" 3)Supprimer livre \n") ;
		printf(" 4)Chercher livre \n") ;
		printf(" 5)Creer page d ajout de livre \n") ;
		printf(" 6)Creer page suppresion de livre\n") ;
		printf(" q) Quitter \n") ;
		choix=getchar();
		 switch(choix){
					  	case '1':ajouter("livres.bin",saisir());
					  			 break;
					  	case '2':listerlivre("livres.bin");
					  			 break;
					  	case '3':printf("\n Saisir la ref du livre que vous voulez supprimer\n");
					  			 scanf("%ld",&ref);
						  		 supprimer("livres.bin",ref);
					  			 break;
					  	case '4':printf("\n Saisir la ref du livre que vous voulez chercher\n");
					  			 scanf("%ld",&ref);
						  		 if(rechercher("livres.bin",ref)==0){
						  		 	printf("Ce livre n existe pas");
								   };
					  			 break;
					  	case '5': creer_page_ajout();
								  break;		
						case '6': creer_page_supp();
								  break;
					  }
				}while(choix!='q');
}





char menu_gerer_emprunteurs(){
		int id;
		char choix;
		do{fflush(stdin);
		printf(" \n 1)Ajouter emprunteur \n") ;
		printf(" 2)Lister emprunteur \n") ;
		printf(" 3)Supprimer emprunteur \n") ;
		printf(" 4)Chercher emprunteur \n") ;
		printf(" 5)modifier emprunteur \n") ;
		printf(" 6)Ajouter page d ajout d'emprunteur' \n") ;
		printf(" 7)Ajouter page de suprresion d un emprunteur' \n") ;
		printf(" q) Quitter \n") ;
		choix=getchar();
		 switch(choix){fflush(stdin);
					  	case '1':ajouterEmprunteur("emprunteurs.bin",saisirEmprunteur());
					  			 break;
					  	case '2':listeremprunteur("emprunteurs.bin");
					  			 break;
					  	case '3':printf("\n Saisir l identifiant de l'emprunteur que vous voulez supprimer\n");
					  			fflush(stdin);
					  			 scanf("%d",&id);
					  			 fflush(stdin);
						  		 supprimerEmprunteur("emprunteurs.bin",id);
					  			 break;
					  	case '4':printf("\n Saisir l identifiant de l'emprunteur que vous voulez chercher\n");
					  			 scanf("%d",&id);
						  		 chercherEmprunteur("emprunteurs.bin",id);
					  			 break;
					 	case '5':printf("\n Saisir l identifiant de l'emprunteur que vous voulez modifier\n");
					  			 scanf("%d",&id);
						  		 modifierEmprunteur("emprunteurs.bin",id);
					  			 break;
					  	case '6':creer_page_ajout_emp();
					  			 break;
					  	case '7':creer_page_supp_emp();
					  			 break;
					  }
		}while(choix!='q');
	}	
	


void creer_page_auth(){
	if(testerPage(1)==0){
	FILE *f_out=fopen("connexion.html","w+");
	if(f_out!=NULL){
	fprintf(f_out,"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta http-equiv= \"X-UA-Compatible\" content=\"IE=edge\"><meta name= \"viewport \" content=\"width=device-width, initial-scale=1.0\"><link rel=\"stylesheet\" href=\"style_auth.css\"> <title>Connexion</title></head><body><form method=\"post\"><h3>Connecter-vous !</h3><input type=\"text\" name=\"username\" placeholder=\"Saisir votre identifiant\" required=\"\"> <br><input type=\"password\" name=\"password\" placeholder=\"Saisir votre mot de passe\" required=\"\"> <br><button hre=\"#\" type=\"submit\">Se connecter</button></form></body></html>");
	printf("Votre page d authentification a ete bien cree \n");
	ajouterPage(1);
	fclose(f_out);
	}
	}
		else {
		printf("\n La page existe deja \n");
	}
}
void modifier_page_home(char choix_theme){
	FILE *f_out=fopen("index.html","w");
	char couleur1[10],couleur2[10];
	char black[6]="black",white[6]="white",yellow[7]="yellow";
	 switch(choix_theme){
					  	case '1':strcpy(couleur1,black);
					  			 strcpy(couleur2,white);
					  			 break;
					  	case '2':strcpy(couleur1,white);
					  			 strcpy(couleur2,black);
					  			 break;
					  	case '3':strcpy(couleur1,black);
					  			 strcpy(couleur2,yellow);
					  			 break;
					  }
					   fprintf(f_out,"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta http-equiv= \"X-UA-Compatible\" content=\"IE=edge\"><meta name= \"viewport \" content=\"width=device-width, initial-scale=1.0\">    <link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC\" crossorigin=\"anonymous\"><link rel=\"stylesheet\" href=\"style.css\"> <title>MyBook</title></head><nav class=\"navbar navbar-expand-lg navbar-light bg-light \" style=\"background-color: %s !important;\"><div class=\"container-fluid\"><a class=\"navbar-brand\" href=\"#\" style=\"color: %s;\">MyBook</a><div style=\"float: right;\"><button class=\"navbar-toggler\" type=\"button\" data-bs-toggle=\"collapse\" data-bs-target=\"#navbarNavAltMarkup\" aria-controls=\"navbarNavAltMarkup\" aria-expanded=\"false\" aria-label=\"Toggle navigation\"><span class=\"navbar-toggler-icon\"></span></button><div class=\"collapse navbar-collapse\" id=\"navbarNavAltMarkup\"><div class=\"navbar-nav\"><a class=\"nav-link active\" aria-current=\"page\" href=\"#\" style=\"color: %s;\">Acceuil</a><a class=\"nav-link\" href=\"connexion.html\" style=\"color: %s;\">Connexion</a><a class=\"nav-link\" href=\"#\" style=\"color: %s;\">Creer-compte</a></div></div></div></div></nav><div class=\"lien\">",couleur1,couleur2,couleur2,couleur2,couleur2);

					   fclose(f_out);
}
void creer_page_home(){
	char choix_theme,c;
	char black[6]="black",white[6]="white",yellow[7]="yellow";
		fflush(stdin);
	if(testerPage(0)==1){
		printf("Votre page est deja cree, Voulez-vous la modifier ?  Mais attention si vous modifiez le theme, vous allez perdre la personalisation des liens si vous l'avez deja o/n \n");
		c=getchar();
		switch(c){
			case 'o': printf("Vous n'avez pas aime la page, ne vous en faites pas choisissez le theme que vous voulez'");
					  printf("\n 1)******Arriere plan : Noir && Couleur: Blanche***** \n");
					  printf("\n 2)******Arriere plan : Blanc && Couleur: Noir***** \n");
					  printf("\n 3)******Arriere plan : Noir && Couleur: jaune***** \n");
					  fflush(stdin);
					  choix_theme=getchar();
					 modifier_page_home(choix_theme);
		}
	}
	else{
	FILE *f_out=fopen("index.html","w+");
	if(f_out!=NULL){
	fprintf(f_out,"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta http-equiv= \"X-UA-Compatible\" content=\"IE=edge\"><meta name= \"viewport \" content=\"width=device-width, initial-scale=1.0\">    <link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC\" crossorigin=\"anonymous\"><link rel=\"stylesheet\" href=\"style.css\"> <title>MyBook</title></head><nav class=\"navbar navbar-expand-lg navbar-light bg-light\"><div class=\"container-fluid\"><a class=\"navbar-brand\" href=\"#\">MyBook</a><div style=\"float: right;\"><button class=\"navbar-toggler\" type=\"button\" data-bs-toggle=\"collapse\" data-bs-target=\"#navbarNavAltMarkup\" aria-controls=\"navbarNavAltMarkup\" aria-expanded=\"false\" aria-label=\"Toggle navigation\"><span class=\"navbar-toggler-icon\"></span></button><div class=\"collapse navbar-collapse\" id=\"navbarNavAltMarkup\"><div class=\"navbar-nav\"><a class=\"nav-link active\" aria-current=\"page\" href=\"#\">Acceuil</a><a class=\"nav-link\" href=\"connexion.html\">Connexion</a><a class=\"nav-link\" href=\"#\">Creer-compte</a></div></div></div></div></nav><div class=\"lien\">");
	printf("Votre page d acceuil a ete bien cree \n");
	ajouterPage(0);
	}
	fclose(f_out);
	}
}





int main(){
	int tentatives=0;
	char login[30],password[30],vrai_login[30],vrai_pass[30],choix,pass_crypte[30],chemin[255];
	FILE *admin_file;
	admin_file=fopen("admin.txt","r+");
	if(admin_file!=NULL){
		fscanf(admin_file,"%s",vrai_login);
		fscanf(admin_file,"%s",vrai_pass);	
	}
	do{
	printf("Login : ");
	scanf("%s",login);
	printf("Password : ");
	scanf("%s",password);
	strcpy(pass_crypte,crypter(password));
	if(strcmp(vrai_login,login)==0 && strcmp(vrai_pass,pass_crypte)==0){
		do{
		choix=menu();
		switch(choix){fflush(stdin);
			case '1': menu_gerer_livres();
						break;
			case '2': menu_gerer_emprunteurs();
						break;
			case '3': printf("Saisir le chemin du fichier \n");
					  scanf("%s",chemin);
					  importation(chemin);
					  break;	
			case '4': creer_page_auth();
						break;
			case '5': creer_page_home();
						break;
			case '6': gererLien();
						break;
		}
	}while(choix!='q');
	}
	else{
		printf("Les donnees ne sont pas valides \n");
		tentatives++;
		if(tentatives==3){
		printf("Connexion echoue ! Vous n\'avez que 3 tentatives \n Reessayez plus tard \n");
		}
	}
}while(tentatives<3);
}
