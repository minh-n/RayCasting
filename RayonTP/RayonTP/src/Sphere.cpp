/*
 * Sphere.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: hnguye5
 */

#include "Sphere.h"

Sphere::~Sphere() {

}

//verifie si l'objet possede un point d'intersection avec la demi-droite represente par un point d'origine et un vecteur directeur
//retourne null si il n'y a pas d'intersection
std::shared_ptr<Position3D> Sphere::intersection(const Position3D& posSource, const Position3D& posDir) const
{
	//creation du vecteur directeur
	Position3D dir = posDir - posSource;

	//initialisation des variables utiles pour les calculs
	double xRayon = posSource.getX();
	double yRayon = posSource.getY();
	double zRayon = posSource.getZ();

	double xDir = dir.getX();
	double yDir = dir.getY();
	double zDir = dir.getZ();

	double xCentre = this->position.getX();
	double yCentre = this->position.getY();
	double zCentre = this->position.getZ();

	//calcul des coefficients de l'equation polynomiale de degre 2
	double a = pow(xDir, 2) + pow(yDir, 2) + pow(zDir, 2);
	double b = 2*(xDir*(xRayon - xCentre) + yDir*(yRayon - yCentre) + zDir*(zRayon - zCentre));
	double c = pow(xRayon-xCentre, 2) + pow(yRayon-yCentre, 2) + pow(zRayon-zCentre, 2) - pow(this->radius, 2);

	//resolution de l'equation polynomiale de degre 2
	double delta = b*b - 4*a*c;
	double r1, r2, t = 0.0;

	if (delta > 0) {
		r1 = (-b - sqrt(delta))/(2*a);
		r2 = (-b + sqrt(delta))/(2*a);

		if(r1 > 0)
		{
			if(r2 > 0) t = (r1 < r2) ? r1 : r2;
		}
		else if(r2 > 0)
		{
			t = r2;
		}
		else {
			return nullptr;
		}
	}
	else if (delta == 0 ) {
		r1 = -b/(2*a);

		if(r1 > 0) {
			t = r1;
		}
		else{
			return nullptr;
		}
	}
	else{
		return nullptr;
	}

	return std::make_shared<Position3D> (xRayon + t*xDir, yRayon + t*yDir, zRayon + t*zDir);
}


//calcul la valeur du cos entre la normale par rapport au point de surface et la position de la source lumineuse
double Sphere::calculCosinusAlpha(const Position3D& surface, const Position3D& sourceLumineuse) const{

	//cas a verifier pour eviter une division par 0
	if(surface == sourceLumineuse) return 1;

	//initialisation des vecteurs
	Position3D vectNormale = surface - this->position;
	Position3D vectSource = sourceLumineuse - this->position;

	//calcul
	double scalaire = Position3D::scalaire(vectNormale, vectSource);

	double normeNormale = Position3D::norme(this->position, surface);
	double normeVectSource = Position3D::norme(surface, sourceLumineuse);

	return (scalaire/(normeNormale*normeVectSource));
}


//renvoie un point present sur la demi droite ayant comme origine le point de surface et comme vecteur directeur le rayon reflechi
Position3D Sphere::calculRayonReflechi(const Position3D& surface, const Position3D& sourceRayon) const{

	//initialisation des vecteurs
	Position3D vectRayon = Position3D::vectUnitaire(sourceRayon, surface);
	Position3D vectNormal = Position3D::vectUnitaire(this->position, surface);

	//calcul du vecteur reflechi
	Position3D vectRefl = vectRayon - vectNormal*Position3D::scalaire(vectRayon, vectNormal)*2;

	return vectRefl + surface;
}
