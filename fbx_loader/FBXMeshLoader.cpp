#include "FBXMeshLoader.hpp"
#include <vector>
#include <math.h>
#define POLY_SIZE_COUNT 2
#define POLY_SIZE_IDX(size) ((size)==3 ? 0 : 1)

using namespace std;
using namespace mroon;
using namespace fbxsdk_2013_3;

MixedMesh LoadFBXMesh(FbxMesh* pMesh, float scale) {
	int i, j;
	int lPolygonCount = pMesh->GetPolygonCount();
	int lControlPointsCount = pMesh->GetControlPointsCount();
	// Points are shared between 3 and 4 (and more) vertex polys
	vector<Vector3> points;

	// We sort the references so we do all our triangles, then all our quads
	vector<int> refs[POLY_SIZE_COUNT];
	// So we need to keep multiple arrays of everything else that's assigned
	// by vertex, not by control point. Currently these are
	vector<Colour> colours[POLY_SIZE_COUNT];
	vector<Vector3> normals[POLY_SIZE_COUNT];
	vector<int> sizes[POLY_SIZE_COUNT];
	float r, g, b;

	FbxVector4* lControlPoints = pMesh->GetControlPoints();

	for (i = 0; i < lControlPointsCount; i++) {
		points.push_back(
				Vector3(lControlPoints[i][0], lControlPoints[i][1],
						lControlPoints[i][2]) * scale);


//		Need this code for models where normals are assigned by control point
		// TODO: store these in a temp lookup table, fill in the real normals list later
//        for (int j = 0; j < pMesh->GetElementNormalCount(); j++)
//        {
//            FbxGeometryElementNormal* leNormals = pMesh->GetElementNormal( j);
//			if (leNormals->GetMappingMode() == FbxGeometryElement::eByControlPoint)
//			{
//
//				if (leNormals->GetReferenceMode() == FbxGeometryElement::eDirect) {
//					FbxVector4 nml =
//							leNormals->GetDirectArray().GetAt(i);
//					normals.push_back(
//							Vector3(nml[0],
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
		int pSize = pMesh->GetPolygonSize(i);
		int pIdx = POLY_SIZE_IDX(pSize);

		// Only accept tri or quad polys for now
		// TODO: Accept all size polys, add something to MixedMesh::render
		if (pSize == 3 || pSize == 4) {
			sizes[pIdx].push_back(pSize);
		} else {
			printf("Polygon %d contains %d points\n", i, pSize);
			continue;
		}

		for (j = 0; j < pSize; j++) {
			// Which point is this vertex?
			int lControlPointIndex = pMesh->GetPolygonVertex(i, j);
			refs[pIdx].push_back(lControlPointIndex);
			// What's its colour? (TODO: Actually load colour, also UV etc)
			colours[pIdx].push_back(Colour(fmod(r+=0.1f, 1.0f), fmod(g+=0.8f, 1.0f), fmod(b+=0.17f, 1.0f)));
			Vector3 normal(0, 1, 0);
			for (int l = 0; l < pMesh->GetElementNormalCount(); ++l) {
				FbxGeometryElementNormal* leNormal = pMesh->GetElementNormal(l);
				if (leNormal->GetMappingMode()
						== FbxGeometryElement::eByPolygonVertex) {


					switch (leNormal->GetReferenceMode()) {
					case FbxGeometryElement::eDirect: {
						FbxVector4 fbxNormal = leNormal->GetDirectArray().GetAt(vertexId);
						normal = Vector3(fbxNormal[0], fbxNormal[1], fbxNormal[2]);
						break;
					}
					case FbxGeometryElement::eIndexToDirect: {
						int id = leNormal->GetIndexArray().GetAt(vertexId);

						FbxVector4 fbxNormal = leNormal->GetDirectArray().GetAt(id);
						normal = Vector3(fbxNormal[0], fbxNormal[1], fbxNormal[2]);
						break;
					}
					default:
						break; // other reference modes not shown here!
					}
					break;
				}

			}
			normals[pIdx].push_back(normal);
			vertexId++;
		}
	}

	MixedMesh mesh;
	mesh.setPoints(points);
	// Sort out our vertices in order
	for(int i=0; i<POLY_SIZE_COUNT; i++) {
		colours[0].insert(colours[0].end(), colours[i].begin(), colours[i].end());
		normals[0].insert(normals[0].end(), normals[i].begin(), normals[i].end());
		refs[0].insert(refs[0].end(), refs[i].begin(), refs[i].end());
		sizes[0].insert(sizes[0].end(), sizes[i].begin(), sizes[i].end());
	}
	mesh.setColours(colours[0]);
	mesh.setNormals(normals[0]);
	mesh.setPolys(refs[0], sizes[0]);
	printf(" [Loaded mesh. %d control points, %d refs, %d colours, %d normals] ", points.size(), refs[0].size(), colours[0].size(), normals[0].size());
	return mesh;
}
