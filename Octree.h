#ifndef OCTREE_H
#define OCTREE_H

#include "Classes.h"

class Octree
{
	public:
	
     Octree();
	
	~Octree();
	
	// This sets the initial width, height and depth for the whole scene
    void GetSceneDimensions(triangle *pVertices, int numberOfTriangles);
};

#endif