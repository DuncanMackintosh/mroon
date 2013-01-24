#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "renderables/QuadMesh.hpp"
#include "renderables/TriMesh.hpp"
#include "fbx_loader/FBXMeshLoader.hpp"
#include "vectors/Vector.hpp"
#include <vector>
#include "vectors/Vector3.hpp"
#include <iostream>
#include <fbxsdk.h>
void DestroySdkObjects(FbxManager* pManager, bool pExitStatus);
void InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene);
bool LoadScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename);
bool loadFBXMeshes(char* file);
// angle of rotation for the camera direction
float angle = 0.0f;

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;

// XZ position of the camera
float x=50.0f, z=50.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

mroon::QuadMesh mesh;
std::vector<mroon::MixedMesh> table;

void changeSize(int w, int h) {

        // Prevent a divide by zero, when window is too short
        // (you can't make a window of zero width).
        if (h == 0)
                h = 1;

        float ratio =  w * 1.0 / h;

        // Use the Projection Matrix
        glMatrixMode(GL_PROJECTION);

        // Reset Matrix
        glLoadIdentity();

        // Set the viewport to be the entire window
        glViewport(0, 0, w, h);

        // Set the correct perspective.
        gluPerspective(45.0f, ratio, 0.1f, 100.0f);

        // Get Back to the Modelview
        glMatrixMode(GL_MODELVIEW);
}



void computePos(float deltaMove) {

        x += deltaMove * lx * 0.1f;
        z += deltaMove * lz * 0.1f;
}

float gridHeights[100][100];

void init(void) {
	std::vector<mroon::Vector3> vertices = std::vector<mroon::Vector3>();
	std::vector<mroon::Colour> colours = std::vector<mroon::Colour>();
	std::vector<int> quads = std::vector<int>();
	for (size_t x = 0; x < 101; x++) {
		for (size_t y = 0; y < 101; y++) {
			float h = (float)rand()/RAND_MAX;
			vertices.push_back(mroon::Vector3((float)x, h, float(y)));
			colours.push_back(mroon::Colour(0.9f, h, 0.9f));
			if(x<100 && y<100) {
				quads.push_back(x*101+y);
				quads.push_back((x+1)*101+y);
				quads.push_back((x+1)*101+y+1);
				quads.push_back(x*101+y+1);
			}
		}
	}
	mesh.setVertices(vertices);
	mesh.setColours(colours);
	mesh.setQuads(quads);
	printf("Made %zd quads\n", quads.size());
	loadFBXMeshes("/pers/table2.fbx");

}

void renderScene(void) {

        if (deltaMove)
                computePos(deltaMove);

        std::vector<mroon::Colour> colours = mesh.getColours();
        std::vector<mroon::Vector3> vertices = mesh.getVertices();
        for(size_t x_foof=0; x_foof<101; x_foof++) {
        	for(size_t y=0; y<101; y++) {
        		float h = vertices[x_foof*101+y].y;
        		h += (((float)rand()/RAND_MAX)-0.5f) * 0.1f;
        		vertices[x_foof*101+y].y = h;
        		colours[x_foof*101+y].g = h;
        	}
        }
//        mesh.setVertices(vertices);
//        mesh.setColours(colours);

        // Clear Color and Depth Buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Reset transformations
        glLoadIdentity();
        // Set the camera
        gluLookAt(      x, 5.0f, z,
                        x+lx, 5.0f,  z+lz,
//        				2.243161f, 0.0f, 2.243161f,
                        0.0f, 1.0f,  0.0f);
//        mesh.render();

        for(size_t i=0; i<table.size(); i++) {
        	table[i].render();
        }

        float h = 0.0f;
        glBegin(GL_LINES);
          for(int x=1; x<100; x++) {
              for(int y=1; y<100; y++) {

                  glColor3f(0.0f, 0.2f, 0.9f);
                  glVertex3f(x-1, h, y-1);
                  glVertex3f(x, h, y-1);
                  glVertex3f(x-1, h, y-1);
                  glVertex3f(x-1, h, y);

              }
          }
        glEnd();




        glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy) {

        if (key == 27)
              exit(0);
}

void pressKey(int key, int xx, int yy) {

       switch (key) {
             case GLUT_KEY_UP : deltaMove = 0.5f; break;
             case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
       }
}

void releaseKey(int key, int x, int y) {

        switch (key) {
             case GLUT_KEY_UP :
             case GLUT_KEY_DOWN : deltaMove = 0;break;
        }
}

void mouseMove(int x, int y) {

         // this will only be true when the left button is down
         if (xOrigin >= 0) {

                // update deltaAngle
                deltaAngle = (x - xOrigin) * 0.01f;

                // update camera's direction
                lx = sin(angle + deltaAngle);
                lz = -cos(angle + deltaAngle);
        }
}

void mouseButton(int button, int state, int x, int y) {

        // only start motion if the left button is pressed
        if (button == GLUT_LEFT_BUTTON) {

                // when the button is released
                if (state == GLUT_UP) {
                        angle += deltaAngle;
                        xOrigin = -1;
                }
                else  {// state = GLUT_DOWN
                        xOrigin = x;
                }
        }
}

bool loadFBXMeshes(char* file) {
    FbxManager* lSdkManager = NULL;
    FbxScene* lScene = NULL;
    bool lResult;

    // Prepare the FBX SDK.
    InitializeSdkObjects(lSdkManager, lScene);
    // Load the scene.

    // The example can take a FBX file as an argument.
	lResult = LoadScene(lSdkManager, lScene, file);
	if (lResult) {
		FbxNode* lNode = lScene->GetRootNode();

		if (lNode) {
			for (int i = 0; i < lNode->GetChildCount(); i++) {
				FbxNodeAttribute::EType lAttributeType;
				if (lNode->GetChild(i)->GetNodeAttribute() == NULL) {
					printf("NULL Node Attribute\n\n");
				} else {
					lAttributeType =
							(lNode->GetChild(i)->GetNodeAttribute()->GetAttributeType());

					if (lAttributeType != FbxNodeAttribute::eMesh) {
						continue;
					}
					FbxMesh* fbxMesh = (FbxMesh *) lNode->GetChild(i)->GetNodeAttribute();
					mroon::MixedMesh mesh = LoadFBXMesh(fbxMesh);
					table.push_back(mesh);
					mesh.dbgBounds();
				}

			}
		} else {
			printf("No root node in scene\n");
		}
	} else {
		printf("Failed to load scene\n");
	}
	printf("Loading %zd meshes for table\n", table.size());
	return true;
}

int main(int argc, char **argv) {
	Vector3 v;
	v = Vector3(1.0f, 2.0f, 3.0f);
	std::cout << v.stringRep();
	std::cout <<"\n";
	std::cout << v.length();
	std::cout <<"\n";

  init();
        // init GLUT and create window
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowPosition(100,100);
        glutInitWindowSize(320,320);
        glutCreateWindow("Lighthouse3D - GLUT Tutorial");

        // register callbacks
        glutDisplayFunc(renderScene);
        glutReshapeFunc(changeSize);
        glutIdleFunc(renderScene);

        glutIgnoreKeyRepeat(1);
        glutKeyboardFunc(processNormalKeys);
        glutSpecialFunc(pressKey);
        glutSpecialUpFunc(releaseKey);

        // here are the two new functions
        glutMouseFunc(mouseButton);
        glutMotionFunc(mouseMove);

        // OpenGL init
        glEnable(GL_DEPTH_TEST);

        // enter GLUT event processing cycle
        glutMainLoop();

        return 1;
}
bool LoadScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename)
{
    int lFileMajor, lFileMinor, lFileRevision;
    int lSDKMajor,  lSDKMinor,  lSDKRevision;
    bool lStatus;

    // Get the file version number generate by the FBX SDK.
    FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

    // Create an importer.
    FbxImporter* lImporter = FbxImporter::Create(pManager,"");

    // Initialize the importer by providing a filename.
    const bool lImportStatus = lImporter->Initialize(pFilename, -1, pManager->GetIOSettings());
    lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

    if( !lImportStatus )
    {
//        FBXSDK_printf("Call to FbxImporter::Initialize() failed.\n");
//        FBXSDK_printf("Error returned: %s\n\n", lImporter->GetLastErrorString());
//
//        if (lImporter->GetLastErrorID() == FbxIOBase::eFileVersionNotSupportedYet ||
//            lImporter->GetLastErrorID() == FbxIOBase::eFileVersionNotSupportedAnymore)
//        {
//            FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);
//            FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);
//        }

        return false;
    }


    // Import the scene.
    lStatus = lImporter->Import(pScene);
    // Destroy the importer.
    lImporter->Destroy();
    return lStatus;
}

void InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene)
{
    //The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
    pManager = FbxManager::Create();
    if( !pManager )
    {
        FBXSDK_printf("Error: Unable to create FBX Manager!\n");
        exit(1);
    }
	else FBXSDK_printf("Autodesk FBX SDK version %s\n", pManager->GetVersion());

	//Create an IOSettings object. This object holds all import/export settings.
	FbxIOSettings* ios = FbxIOSettings::Create(pManager, IOSROOT);
	pManager->SetIOSettings(ios);

	//Load plugins from the executable directory (optional)
	FbxString lPath = FbxGetApplicationDirectory();
	pManager->LoadPluginsDirectory(lPath.Buffer());

    //Create an FBX scene. This object holds most objects imported/exported from/to files.
    pScene = FbxScene::Create(pManager, "My Scene");
	if( !pScene )
    {
        FBXSDK_printf("Error: Unable to create FBX scene!\n");
        exit(1);
    }
}

void DestroySdkObjects(FbxManager* pManager, bool pExitStatus)
{
    //Delete the FBX Manager. All the objects that have been allocated using the FBX Manager and that haven't been explicitly destroyed are also automatically destroyed.
    if( pManager ) pManager->Destroy();
	if( pExitStatus ) FBXSDK_printf("Program Success!\n");
}
