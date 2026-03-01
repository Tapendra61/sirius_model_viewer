#include "model/model.h"

#include <string>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "sirius_logger/log.h"

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
}

void Model::process_node(aiNode* node) {
	
}