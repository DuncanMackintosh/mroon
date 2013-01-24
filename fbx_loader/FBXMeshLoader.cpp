#include "FBXMeshLoader.hpp"
#include <vector>
mroon::MixedMesh LoadFBXMesh(FbxMesh* pMesh) {
	int i, j;
	int lPolygonCount = pMesh->GetPolygonCount();
	int lControlPointsCount = pMesh->GetControlPointsCount();
	std::vector<mroon::Vector3> points;
	std::vector<mroon::Colour> colours;
	std::vector<int> refs;
	std::vector<int> sizes;

	FbxVector4* lControlPoints = pMesh->GetControlPoints();

	for (i = 0; i < lControlPointsCount; i++) {
		points.push_back(
				mroon::Vector3(lControlPoints[i][0], lControlPoints[i][1],
						lControlPoints[i][2]));
		colours.push_back(mroon::Colour(1.0f, 0.5f, 0.9f));
	}

	for (i = 0; i < lPolygonCount; i++) {
		int lPolygonSize = pMesh->GetPolygonSize(i);
		// Only accept tri polys
		if (lPolygonSize == 3 || lPolygonSize == 4) {
			sizes.push_back(lPolygonSize);
		} else {
			printf("Polygon %d contains %d points\n", i, lPolygonSize);
			continue;
		}

		for (j = 0; j < lPolygonSize; j++) {
			int lControlPointIndex = pMesh->GetPolygonVertex(i, j);
			refs.push_back(lControlPointIndex);
		}
	}

	mroon::MixedMesh mesh;
	mesh.setVertices(points);
	mesh.setColours(colours);
	mesh.setPolys(refs, sizes);
	printf("Loaded a mesh containing %zd vertices and %zd polys\n", points.size(), sizes.size());
	return mesh;
}
