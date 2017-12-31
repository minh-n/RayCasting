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
		Position3D vectAC = pointC - pointA;
		Position3D vectAB = pointB - pointA;
		Position3D vectAP = *p - pointA;

		//calcul de norme
		double dotAC_AC = Position3D::scalaire(vectAC, vectAC);
		double dotAC_AB = Position3D::scalaire(vectAC, vectAB);
		double dotAC_AP = Position3D::scalaire(vectAC, vectAP);
		double dotAB_AB = Position3D::scalaire(vectAB, vectAB);
		double dotAB_AP = Position3D::scalaire(vectAB, vectAP);

		//calcul des coordonnees barycentriques
		double inv = 1/(dotAC_AC * dotAB_AB - dotAC_AB * dotAC_AB);
		double u = (dotAB_AB * dotAC_AP - dotAC_AB * dotAB_AP) * inv;
		double v = (dotAC_AC * dotAB_AP - dotAC_AB * dotAC_AP) * inv;

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
	Position3D vectNormal = Triangle::vectNormal(surface, sourceLumineuse);
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
	Position3D vectNormal = Triangle::vectNormal(surface, sourceRayon);

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

	//calcul d'un vecteur normal au plan ABC
	Position3D vectNorm = Position3D::produitVectoriel(vectAB, vectAC);

	//calcul de la constante de l'equation cartesienne du plan ABC
	double d = -vectNorm.getX()*pointA.getX() - vectNorm.getY()*pointA.getY() - vectNorm.getZ()*pointA.getZ();

	//calcul du coefficient t de la representation parametrique de la droite
	double t = (-(vectNorm.getX()*posSource.getX()) - (vectNorm.getY()*posSource.getY()) - (vectNorm.getZ()*posSource.getZ()) - d)/
			((vectNorm.getX()*vectDir.getX()) + (vectNorm.getY()*vectDir.getY())+ (vectNorm.getZ()*vectDir.getZ()));

	//calcul point d'intersection
	double x = posSource.getX() + vectDir.getX()*t;
	double y = posSource.getY() + vectDir.getY()*t;
	double z = posSource.getZ() + vectDir.getZ()*t;

	return std::make_shared<Position3D>(x, y, z);
}


//renvoie un vecteur normal au plan ABC et passant par le point surface
Position3D Triangle::vectNormal(const Position3D& surface, const Position3D& posSource) const{

	//Initialisation des vecteurs du plan ABC
	Position3D vectAB = Position3D::vectUnitaire(pointA, pointB);
	Position3D vectAC = Position3D::vectUnitaire(pointA, pointC);

	//calcul d'un vecteur normal au plan
	Position3D vectNorm = Position3D::produitVectoriel(vectAB, vectAC);

	//calcul du sens de la normal au point de surface
	Position3D sens1 = vectNorm - surface;
	Position3D sens2 = vectNorm + surface;

	double normeSens1 = Position3D::norme(posSource, sens1);
	double normeSens2 = Position3D::norme(posSource, sens2);

	if(normeSens1 > normeSens2)
	{
		return sens1;
	}
	else
	{
		return sens2;
	}
}
