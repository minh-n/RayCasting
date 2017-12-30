//============================================================================
// Name        : RayonTP.cpp
// Author      : Adrien & Minh
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Parser.h"

using namespace std;

void testTriangle(string path, string nom){
	Ecran ecran = Ecran();
	Scene scene = Scene();
	Parser p = Parser();

	if(p.lecture(scene, ecran, path) == 0)
	{
		scene.afficher();
		scene.setupEcranSansReflexion();
		scene.creationFichier(nom);
	}
}

void lancerRayon(string path, string nom, int nbIteration, bool verbose){
	Ecran ecran = Ecran();
	Scene scene = Scene();
	Parser p = Parser();

	if(p.lecture(scene, ecran, path) == 0)
	{
		if(verbose) scene.afficher();
		scene.setupEcranAvecReflexion(nbIteration);
		scene.creationFichier(nom);
	}
}

void lancerRayonSansReflexion(string path, string nom, bool verbose){
	Ecran ecran = Ecran();
	Scene scene = Scene();
	Parser p = Parser();

	if(p.lecture(scene, ecran, path) == 0)
	{
		if(verbose) scene.afficher();
		scene.setupEcranSansReflexion();
		scene.creationFichier(nom);
	}
}

int main() {

	testTriangle("TestTriangle.txt", "triangle");

//	int selection = 0;
//	bool sortie = false;
//	bool mauvaisInput = false;
//	int nbIteration = 0;
//
//	string path;
//	string nom;
//
//	cout << string(2, '\n' ) << endl;
//	cout<<"#############################################################"<<endl;
//	cout<<"#                                                           #"<<endl;
//	cout<<"#                                                           #"<<endl;
//	cout<<"#                                                           #"<<endl;
//	cout<<"#     R      A     Y     T    R   A  C  I N G  1.0          #"<<endl;
//	cout<<"#                                                           #"<<endl;
//	cout<<"#                                                           #"<<endl;
//	cout<<"#                                                           #"<<endl;
//	cout<<"#############################################################"<<endl;
//
//	cout << string(2, '\n' ) << endl;
//	cout<<" Bienvenue dans le programme de lancer de rayon.";
//
//	while(sortie == false)
//	{
//		cout<<"\n Entrez 1 pour lancer la batterie de tests.\n Celle-ci comprend les tests unitaires pour l'intersection, ainsi que plusieurs scenes predefinies, avec ou sans reflexion.\n" << endl;
//		cout<<" Entrez 2 pour realiser le rendu de votre propre fichier.\n" << endl;
//		cout<<" Entrez 3 pour sortir du programme.\n" << endl;
//
//		do
//		{
//			cout<<" Quel est votre choix ?\n" << endl;
//			cin>>selection; //lecture de l'entree de l'utilisateur
//			mauvaisInput = cin.fail();
//			if(mauvaisInput)
//			{
//				cout<<" Veuillez recommencer.\n" << endl;
//			}
//			cin.clear();
//			cin.ignore(10, '\n');
//		}while(mauvaisInput);
//
//		switch(selection)
//		{
//		case 1 :
//		{   //lancement des tests
//			path = "./scenes/SphereSurCamera.txt";
//			nom = "SphereSurCamera";
//			lancerRayon(path, nom, 1, false);
//
//			path = "./scenes/SphereEntreCamEtEcran.txt";
//			nom = "SphereEntreCamEtEcran";
//			lancerRayon(path, nom, 1, false);
//
//			path = "./scenes/SphereDerriereCam.txt";
//			nom = "SphereDerriereCam";
//			lancerRayon(path, nom, 1, false);
//
//			path = "./scenes/ScenePlusieurs.txt";
//			nom = "ScenePlusieurs";
//			lancerRayon(path, nom, 2, false);
//
//			path = "./scenes/ScenePlusieurs.txt";
//			nom = "ScenePlusieursSansReflexion";
//			lancerRayonSansReflexion(path, nom, false);
//
//			path = "./scenes/SceneOriginale.txt";
//			nom = "SceneOriginale";
//			lancerRayon(path, nom, 1, false);
//
//			path = "./scenes/SceneOriginale.txt";
//			nom = "SceneOriginaleSansReflexion";
//			lancerRayonSansReflexion(path, nom, false);
//			break;
//		}
//
//		case 2:
//		{
//			cout<<"\n Entrez le nom du fichier de scene personnalise.\nCelui ci doit être de la forme SceneInput.txt (fichier donne en exemple dans la racine du programme) ou ./SceneInput.txt :\n" << endl;
//			cin>>path;
//
//			cout<<"\n Entrez le nombre d'iteration de reflexion :\n" << endl;
//			cin>>nbIteration;
//
//			nom = "ScenePersonnalisee";
//			lancerRayon(path, nom, nbIteration, true);
//			break;
//		}
//
//		case 3:
//		{
//			cout<<"\n Fin du programme.\n" << endl;
//			sortie = true;
//			break;
//		}
//		default :
//			break;
//		}
//		cout<<"\n";
//	}
	return 0;
}

