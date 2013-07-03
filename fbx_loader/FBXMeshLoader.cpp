#include "FBXMeshLoader.hpp"
#include <vector>
#include <math.h>
mroon::MixedMesh LoadFBXMesh(FbxMesh* pMesh, float scale) {
	int i, j;
	int lPolygonCount = pMesh->GetPolygonCount();
	int lControlPointsCount = pMesh->GetControlPointsCount();
	std::vector<mroon::Vector3> points;
	std::vector<mroon::Vector3> normals;
	std::vector<mroon::Colour> colours;
	std::vector<int> refs;
	std::vector<int> sizes;
	float r, g, b;

	FbxVector4* lControlPoints = pMesh->GetControlPoints();

	for (i = 0; i < lControlPointsCount; i++) {
		points.push_back(
				mroon::Vector3(lControlPoints[i][0], lControlPoints[i][1],
						lControlPoints[i][2]) * scale);

		colours.push_back(mroon::Colour(fmod(r+=0.1f, 1.0f), fmod(g+=0.8f, 1.0f), fmod(b+=0.17f, 1.0f)));
//		Need this code for models where normals are assigned by control point
		// TODO: store these in a temp lookup table, fill in the real normals list later
//        for (int j = 0; j < pMesh->GetElementNormalCount(); j++)
//        {
//            FbxGeometryElementNormal* leNormals = pMesh->GetElementNormal( j);
//			if (leNormals->GetMappingMode() == FbxGeometryElement::eByControlPoint)
//			{
//
//				if (leNormals->GetReferenceMode() == FbxGeometryElement::eDirect) {
//					fbxsdk_2013_3::FbxVector4 nml =
//							leNormals->GetDirectArray().GetAt(i);
//					normals.push_back(
//							mroon::Vector3(nml[0],
//									nml[1],
//									nml[2]));
//					// Take the first normal
//					break;
//				}
//			}
//        }
	}
	int vertexId = 0;
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
			mroon::Vector3 normal(0, 1, 0);
			for (int l = 0; l < pMesh->GetElementNormalCount(); ++l) {
				FbxGeometryElementNormal* leNormal = pMesh->GetElementNormal(l);
				if (leNormal->GetMappingMode()
						== FbxGeometryElement::eByPolygonVertex) {


					switch (leNormal->GetReferenceMode()) {
					case FbxGeometryElement::eDirect: {
						fbxsdk_2013_3::FbxVector4 fbxNormal = leNormal->GetDirectArray().GetAt(vertexId);
						normal = mroon::Vector3(fbxNormal[0], fbxNormal[1], fbxNormal[2]);
						break;
					}
					case FbxGeometryElement::eIndexToDirect: {
						int id = leNormal->GetIndexArray().GetAt(vertexId);

						fbxsdk_2013_3::FbxVector4 fbxNormal = leNormal->GetDirectArray().GetAt(id);
						normal = mroon::Vector3(fbxNormal[0], fbxNormal[1], fbxNormal[2]);
						break;
					}
					default:
						break; // other reference modes not shown here!
					}
					break;
				}

			}
			normals.push_back(normal);
			vertexId++;
		}
	}

	mroon::MixedMesh mesh;
	mesh.setVertices(points);
	mesh.setColours(colours);
	mesh.setNormals(normals);
	mesh.setPolys(refs, sizes);
	return mesh;
}
