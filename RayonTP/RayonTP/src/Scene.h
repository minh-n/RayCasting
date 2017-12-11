/*
 * Scene.h
 *
 *  Created on: Nov 29, 2017
 *      Author: hnguye5
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <boost/variant.hpp>
#include "Objet.h"
#include "Sphere.h"
#include "Ecran.h"



/**
 * CAMERA
 */

class Camera {

private :
	Position pos;

public:

	Camera();
	Camera(Position p);
	virtual ~Camera();

	const Position& getPos() const {
		return pos;
	}

	void setPos(const Position& pos) {
		this->pos = pos;
	}
};





/**
 * SOURCE
 */

class Source {
private:
	Position pos;
	Couleur couleur;

public:
	Source();
	Source(Position p);
	virtual ~Source();

	const Couleur& getCouleur() const {
		return couleur;
	}

	void setCouleur(const Couleur& couleur) {
		this->couleur = couleur;
	}

	void setCouleur(int r, int g, int b) {
		this->couleur.setR(r);
		this->couleur.setG(g);
		this->couleur.setB(b);
	}

	const Position& getPos() const {
		return pos;
	}

	void setPos(const Position& pos) {
		this->pos = pos;
	}
};



/**
 * SCENE
 */

class Scene {

private:
	Source source;
	Camera camera;
	Ecran ecran;
	Couleur bgColor;

	typedef boost::variant<Objet, Sphere> typeObjets;

	std::vector<typeObjets> nosObjets;

public:
	Scene();
	virtual ~Scene();

	void addObjet(typeObjets o)
	{
		nosObjets.push_back(o);
	}

	const Camera& getCamera() const {
		return camera;
	}

	void setCamera(const Camera& camera) {
		this->camera = camera;
	}

	const Ecran& getEcran() const {
		return ecran;
	}

	void setEcran(const Ecran& ecran) {
		this->ecran = ecran;
	}

	const std::vector<typeObjets>& getNosObjets() const {
		return nosObjets;
	}

	void setNosObjets(const std::vector<typeObjets>& nosObjets) {
		this->nosObjets = nosObjets;
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

	std::string getTypeObjets() const {

		return "";
	}
};





#endif /* SCENE_H_ */
