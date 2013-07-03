#ifndef _FBX_MESH_LOADER_H
#define _FBX_MESH_LOADER_H

#include "fbxsdk.h"
#include "../renderables/MixedMesh.hpp"

mroon::MixedMesh LoadFBXMesh(FbxMesh* mesh, float scale);
#endif
