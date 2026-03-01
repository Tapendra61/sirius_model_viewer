#include "model/model.h"

#include <string>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "sirius_logger/log.h"
#include "model/mesh.h"

Model::Model(std::string model_path) : model_path_(std::move(model_path)) {
	load_model();
}

void Model::load_model() {
	Assimp::Importer importer;
	const aiScene* ai_scene = importer.ReadFile(model_path_, aiProcess_Triangulate);
	
	if(!ai_scene || ai_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !ai_scene->mRootNode) {
		sr::log_error("Failed to load model! Error: {}", importer.GetErrorString());
		return;
	}
	
	process_node(ai_scene->mRootNode, ai_scene);
}

void Model::process_node(aiNode* node, const aiScene* scene) {
	for(int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes_.push_back(process_mesh(mesh, scene));
	}
	
	for(int i = 0; i < node->mNumChildren; i++) {
		process_node(node->mChildren[i], scene);
	}
}

Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene) {
	
}