/*
 * Triangle.cpp
 *
 *  Created on: 30 déc. 2017
 *      Author: Adrien
 */

#include "Triangle.h"
#include <vector>

Triangle::~Triangle() {

}

//verifie si l'objet possede un point d'intersection avec la demi-droite represente par un point d'origine et un vecteur directeur
//retourne null si il n'y a pas d'intersection
std::shared_ptr<Position3D> Triangle::intersection(const Position3D& posSource, const Position3D& posDir) const{

	//Point d'intersection avec le plan ABC
	std::shared_ptr<Position3D> p = intersectionPlan(posSource, posDir);

	if(p != nullptr)
	{
		//vecteurs utiles
		Position3D vectAB = pointB - pointA;
		Position3D vectAC = pointC - pointA;
		Position3D vectAP = *p - pointA;

		//calcul de norme
		double dotAB_AB = Position3D::scalaire(vectAB, vectAB);
		double dotAB_AC = Position3D::scalaire(vectAB, vectAC);
		double dotAB_AP = Position3D::scalaire(vectAB, vectAP);
		double dotAC_AC = Position3D::scalaire(vectAC, vectAC);
		double dotAC_AP = Position3D::scalaire(vectAC, vectAP);

		//calcul des coordonnees barycentriques
		double inv = 1/(dotAB_AB * dotAC_AC - dotAB_AC * dotAB_AC);
		double u = (dotAC_AC * dotAB_AP - dotAB_AC * dotAC_AP) * inv;
		double v = (dotAB_AB * dotAC_AP - dotAB_AC * dotAB_AP) * inv;

		//Verifie que le point est dans le triangle ABC
		if((u >= 0) && (v >= 0) && (u + v <1))
		{
			return p;
		}
	}

	return nullptr;
}


//calcul la valeur du cos entre la normale par rapport au point de surface et la position de la source lumineuse
double Triangle::calculCosinusAlpha(const Position3D& surface, const Position3D& sourceLumineuse) const{

	//cas a verifier pour eviter une division par 0
	if(surface == sourceLumineuse) return 1;

	//initialisation des vecteurs
	Position3D vectNormal = Triangle::vectNormal(surface);
	Position3D vectSource = sourceLumineuse - surface;

	//calcul
	double scalaire = Position3D::scalaire(vectNormal, vectSource);

	double normeNormale = Position3D::norme(surface, vectNormal);
	double normeVectSource = Position3D::norme(surface, sourceLumineuse);

	return (scalaire/(normeNormale*normeVectSource));
}


//renvoie un point present sur la demi droite ayant comme origine le point de surface et comme vecteur directeur le rayon reflechi
Position3D Triangle::calculRayonReflechi(const Position3D& surface, const Position3D& sourceRayon) const{

	//initialisation des vecteurs
	Position3D vectRayon = Position3D::vectUnitaire(sourceRayon, surface);
	Position3D vectNormal = Triangle::vectNormal(surface);

	//calcul du vecteur reflechi
	Position3D vectRefl = vectRayon - vectNormal*Position3D::scalaire(vectRayon, vectNormal)*2;

	return vectRefl + surface;
}

//renvoie un point d'intersection entre la droite posSource-posDir et le plan ABC
//retourne null sinon
std::shared_ptr<Position3D> Triangle::intersectionPlan(const Position3D& posSource, const Position3D& posDir) const{

	//Initialisation des vecteurs
	Position3D vectDir = posDir - posSource;
	Position3D vectAB = pointB - pointA;
	Position3D vectAC = pointC - pointA;

	//initialisation de la matrice
	std::vector<std::vector<double>> matrice;

	matrice.resize(3);
	for (int i = 0; i < 4; ++i)
	{
		matrice[i].resize(4);
	}

	matrice[0][0] = vectDir.getX();
	matrice[0][1] = -vectAB.getX();
	matrice[0][2] = -vectAC.getX();
	matrice[0][3] = pointA.getX() - posSource.getX();

	matrice[1][0] = vectDir.getY();
	matrice[1][1] = -vectAB.getY();
	matrice[1][2] = -vectAC.getY();
	matrice[1][3] = pointA.getY() - posSource.getY();

	matrice[2][0] = vectDir.getZ();
	matrice[2][1] = -vectAB.getZ();
	matrice[2][2] = -vectAC.getZ();
	matrice[2][3] = pointA.getZ() - posSource.getZ();

	//resolution par le pivot de Gauss
	if(matrice[0][0] == 0) return nullptr;

	double coef = (-1*matrice[1][0]/matrice[0][0]);
	for(int i = 0; i < 4; i++)
	{
		matrice[1][i]=(coef*matrice[0][i])+matrice[1][i];
	}

	coef = (-1*matrice[2][0]/matrice[0][0]);
	for(int i = 0; i < 4; i++)
	{
		matrice[2][i]=(coef*matrice[0][i])+matrice[2][i];
	}

	if(matrice[1][1] == 0) return nullptr;

	coef = (-1*matrice[2][1]/matrice[1][1]);
	for(int i = 0; i < 4; i++)
	{
		matrice[2][i]=(coef*matrice[1][i])+matrice[2][i];
	}

	if(matrice[2][2] == 0) return nullptr;

	double z = matrice[2][3]/matrice[2][2];
	double y = (matrice[1][3]-(matrice[1][2]*z))/matrice[1][1];
	double x = (matrice[0][3]-((matrice[0][1]*y)+(matrice[0][2]*z)))/matrice[0][0];

	return std::make_shared<Position3D>(x, y, z);
}

//renvoie un vecteur normal au plan ABC et passant par le point posSource
Position3D Triangle::vectNormal(const Position3D& posSource) const{

	//Calcul du repere orthonorme avec pointA comme origine
	Position3D vectAB = Position3D::vectUnitaire(pointA, pointB);
	Position3D vectAC = Position3D::vectUnitaire(pointA, pointC);

//	Position3D vectOrtho = vectAC - vectAB*(Position3D::scalaire(vectAC, vectAB));
//	vectOrtho = Position3D::vectUnitaire(pointA, vectOrtho);

	//calcul d'un vecteur normal au plan
	Position3D vectNorm = Position3D::produitVectoriel(vectAB, vectAC);

	return vectNorm + posSource;
}
