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

	void setPos(const Position3D& pos) {
		this->pos = pos;
	}
};


class Source {
private:
	Position3D pos;
	Couleur couleur;

public:
	Source();
	Source(Position3D p);

	~Source();

	const Couleur& getCouleur() const {
		return couleur;
	}

	void setCouleur(const Couleur& couleur) {
		this->couleur = couleur;
	}

	const Position3D& getPos() const {
		return pos;
	}

	void setPos(const Position3D& pos) {
		this->pos = pos;
	}
};


class Scene {

private:
	Source source;
	Camera camera;
	Ecran ecran;
	Couleur bgColor;

	std::vector<std::shared_ptr<Objet>> nosObjets;
//	std::vector<Objet*> nosObjets;

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

	void setNosObjets(const std::vector<std::shared_ptr<Objet>>& nosObjets) {
		this->nosObjets = nosObjets;
	}


	void addObjet(std::shared_ptr<Objet> o) {
		nosObjets.push_back(o);
	}

	void afficher();
	void creationFichier(const std::string& nomFichier);
	void setupEcran(const unsigned maxIteration);
	void setupEcranSansReflexion();
	bool eclairageDirect(const Position3D& posIncidence, const std::shared_ptr<Objet> objetSource);
	Couleur eclairageAvecReflexion(const std::shared_ptr<Objet> objet, const Couleur& rayonSpeculaire, const Position3D& posIncidence);
	Couleur recursive(const std::shared_ptr<Objet> objetSource, const Position3D& sourceRayon, const Position3D& surface, Couleur couleurRayon, unsigned int iteration, const unsigned maxIteration);

};


#endif /* SCENE_H_ */
