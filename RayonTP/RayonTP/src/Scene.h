/*
 * Scene.h
 *
 *  Created on: Nov 29, 2017
 *      Author: hnguye5
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "Source.h"
#include "Camera.h"
#include "Ecran.h"
#include "Objet.h"
#include <vector>

class Scene {

private:
	Source source;
	Camera camera;
	Ecran ecran;
	std::vector<Objet> nosObjets;




public:
	Scene(Source s, Camera c, Ecran e);
	virtual ~Scene();
};

#endif /* SCENE_H_ */
