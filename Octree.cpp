#include "Octree.h"

Octree::Octree()
{
}


Octree::~Octree()
{
}

void Octree::GetSceneDimensions(triangle *pTriangles, int numberOfTriangles)
{
/*	// We pass in the list of vertices and the vertex count to get the
	// center point and width of the whole scene.  We use this information
	// to subdivide our octree.  Eventually, in the next tutorial it won't
	// just be a list of vertices, but another structure that holds all the
	// normals and texture information.  It's easy to do once you understand vertices.

	// Initialize some temporary variables to hold the max dimensions found
	float maxWidth = 0, maxHeight = 0, maxDepth = 0;

	// Return from this function if we passed in bad data
	if(!pTriangles || numberOfTriangles <= 0) return;

	// Below we calculate the center point of the scene.  To do this, all you
	// need to do is add up ALL the vertices, then divide that total by the
	// number of vertices added up.  So all the X's get added up together, then Y's, etc..
	// This doesn't mean in a single number, but 3 separate floats (totalX, totalY, totalZ).
	// Notice that we are adding 2 vectors together.  If you look in the CVector3 class
	// I overloaded the + and - operator to handle it correctly.  It cuts down on code
	// instead of added the x, then the y, then the z separately.  If you don't want
	// to use operator overloading just make a function called CVector AddVector(), etc...

	// Go through all of the vertices and add them up to eventually find the center
	for(int i = 0; i < numberOfTriangles; i++)
	{

		for(int j=0;j<3;j++)
            m_vCenter = m_vCenter + pTriangles[i].vert[j];
	}

	// Divide the total by the number of vertices to get the center point.
	// We could have overloaded the / symbol but I chose not to because we rarely use it.
	m_vCenter.x /= numberOfTriangles*3;
	m_vCenter.y /= numberOfTriangles*3;	
	m_vCenter.z /= numberOfTriangles*3;

	// Now that we have the center point, we want to find the farthest distance from
	// our center point.  That will tell us how big the width of the first node is.
	// Once we get the farthest height, width and depth, we then check them against each
	// other.  Which ever one is higher, we then use that value for the cube width.

	// Go through all of the vertices and find the max dimensions
	for(int i = 0; i < numberOfTriangles; i++)
	{
		for(int j=0;j<3;j++)
		{
			// Get the current dimensions for this vertex.  We use the fabsf() function
			// to get the floating point absolute value because it might return a negative number.
            float currentWidth  = fabsf(pTriangles[i].vert[j].x - m_vCenter.x);
            float currentHeight = fabsf(pTriangles[i].vert[j].y - m_vCenter.y);
            float currentDepth  = fabsf(pTriangles[i].vert[j].z - m_vCenter.z);

			// Check if the current width value is greater than the max width stored.
			if(currentWidth  > maxWidth)	maxWidth  = currentWidth;

			// Check if the current height value is greater than the max height stored.
			if(currentHeight > maxHeight)	maxHeight = currentHeight;

			// Check if the current depth value is greater than the max depth stored.
			if(currentDepth > maxDepth)		maxDepth  = currentDepth;
		}
	}

	// Set the member variable dimensions to the max ones found.
	// We multiply the max dimensions by 2 because this will give us the
	// full width, height and depth.  Otherwise, we just have half the size
	// because we are calculating from the center of the scene.
	maxWidth *= 2;		maxHeight *= 2;		maxDepth *= 2;

	// Check if the width is the highest value and assign that for the cube dimension
	if(maxWidth > maxHeight && maxWidth > maxDepth)
		m_Width = maxWidth;

	// Check if the height is the heighest value and assign that for the cube dimension
	else if(maxHeight > maxWidth && maxHeight > maxDepth)
		m_Width = maxHeight;

	// Else it must be the depth or it's the same value as some of the other ones
	else
		m_Width = maxDepth;*/

}