/*
 * Scene.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: hnguye5
 */

#include "Scene.h"








/**
 * CAMERA
 */


Camera::Camera() {
	// TODO Auto-generated constructor stub
}

Camera::Camera(Position p) {
	// TODO Auto-generated constructor stub
	pos = p;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

















/**
 * ECRAN
 */


Ecran::Ecran() {
	resolution = 0;


	// TODO Auto-generated constructor stub
}

Ecran::Ecran(int res) {
	resolution = res;
	// TODO Auto-generated constructor stub
}

Ecran::~Ecran() {
	// TODO Auto-generated destructor stub
}








/**
 * SOURCE
 */

Source::Source(){

}
Source::Source(Position p) : pos(p) {

}

Source::~Source() {
	// TODO Auto-generated destructor stub
}











/**
 * SCENE
 */

Scene::Scene() {


}
//ptet faire avec des &s &c &e


Scene::~Scene() {
	// TODO Auto-generated destructor stub
}


