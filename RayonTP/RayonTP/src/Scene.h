/*
 * Scene.h
 *
 *  Created on: Nov 29, 2017
 *      Author: hnguye5
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include "Vecteur.h"
#include "Sphere.h"

/**
 * OBJET
 */

class Objet {

private :

	Position pos;
	int reflection;

public:

	Objet();
	Objet(Position p, int ref);

	virtual ~Objet();

};



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
};



/**
 * ECRAN
 */

class Ecran {

private:

	Position tlc;
	Position trc;
	Position blc;
	int resolution;

public:
	Ecran(int res);
	Ecran();

	virtual ~Ecran();

	const Position& getBlc() const {
		return blc;
	}

	void setBlc(const Position& blc) {
		this->blc = blc;
	}

	int getResolution() const {
		return resolution;
	}

	void setResolution(int resolution) {
		this->resolution = resolution;
	}

	const Position& getTlc() const {
		return tlc;
	}

	void setTlc(const Position& tlc) {
		this->tlc = tlc;
	}

	const Position& getTrc() const {
		return trc;
	}

	void setTrc(const Position& trc) {
		this->trc = trc;
	}
};



/**
 * SOURCE
 */

class Source {
private :
	Position pos;

public:
	Source();
	Source(Position p);
	virtual ~Source();
};



/**
 * SCENE
 */

class Scene {

private:
	Source source;
	Camera camera;
	Ecran ecran;

	std::vector<Objet> nosObjets;

public:
	Scene(Source s, Camera c, Ecran e);
	virtual ~Scene();

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

	const std::vector<Objet>& getNosObjets() const {
		return nosObjets;
	}

	void setNosObjets(const std::vector<Objet>& nosObjets) {
		this->nosObjets = nosObjets;
	}

	const Source& getSource() const {
		return source;
	}

	void setSource(const Source& source) {
		this->source = source;
	}
};





#endif /* SCENE_H_ */
