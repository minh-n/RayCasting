/*
 * Scene.h
 *
 *  Created on: Nov 29, 2017
 *      Author: hnguye5
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <fstream>
#include "Objet.h"
#include "Sphere.h"
#include "Ecran.h"

class Camera {
private :
	Position3D pos;

public:
	Camera();
	Camera(Position3D p);

	~Camera();

	const Position3D& getPos() const {
		return pos;
	}
};


class Source {
private:
	Position3D pos;
	Couleur couleur;

public:
	Source();
	Source(Position3D p, Couleur c);

	~Source();

	const Couleur& getCouleur() const {
		return couleur;
	}

	const Position3D& getPos() const {
		return pos;
	}
};


class Scene {

private:
	Source source;
	Camera camera;
	Ecran ecran;
	Couleur bgColor;

	std::vector<std::shared_ptr<Objet>> nosObjets;

public:
	Scene();

	~Scene();

	const Camera& getCamera() const {
		return camera;
	}

	void setCamera(const Camera& camera) {
		this->camera = camera;
	}

	const Ecran& getEcran() const{
		return ecran;
	}

	void setEcran(const Ecran& ecran) {
		this->ecran = ecran;
	}

	const Source& getSource() const {
		return source;
	}

	void setSource(const Source& source) {
		this->source = source;
	}

	const Couleur& getBgColor() const {
		return bgColor;
	}

	void setBgColor(const Couleur& bgColor) {
		this->bgColor = bgColor;
	}

	const std::vector<std::shared_ptr<Objet>>& getNosObjets() const {
		return nosObjets;
	}

	//ajoute un objet dans la scene
	void addObjet(std::shared_ptr<Objet> o) {
		nosObjets.push_back(o);
	}

	void afficher();

	//cree un fichier .ppm correspond aux donnees de la scene
	void creationFichier(const std::string& nomFichier);

	//calcul la couleur avec reflexion de chaque pixel
	void setupEcranAvecReflexion(const unsigned maxIteration);

	//calcul la couleur sans reflexion de chaque pixel
	void setupEcranSansReflexion();

	//renvoie vrai si le point est eclaire directement par la source lumineuse, faux sinon
	bool eclairageDirect(const Position3D& posIncidence, const std::shared_ptr<Objet> objetSource);

	//renvoie une couleur selon la formule avec reflexion
	Couleur eclairageAvecReflexion(const std::shared_ptr<Objet> objet, const Couleur& rayonSpeculaire, const Position3D& posIncidence);

	//renvoie recursivement une couleur selon la formule avec reflexion
	Couleur couleurAvecReflexionRecursive(const std::shared_ptr<Objet> objetSource, const Position3D& sourceRayon, const Position3D& surface, Couleur couleurRayon, unsigned int iteration, const unsigned maxIteration);
};


#endif /* SCENE_H_ */
