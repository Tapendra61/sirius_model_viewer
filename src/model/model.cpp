#include "model/model.h"

#include <string>
#include <vector>
#include <cstdint>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "glm/glm.hpp"

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
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	
	for(int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex{};
		
		vertex.position = glm::vec3(
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z			
		);
		
		if(mesh->HasNormals()) {
			vertex.normal = glm::vec3(
				mesh->mNormals[i].x,
				mesh->mNormals[i].y,
				mesh->mNormals[i].z
			);
		}
		
		if(mesh->mTextureCoords[0]) {
			vertex.tex_coords = glm::vec2(
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y
			);
		}
		else {
			vertex.tex_coords = glm::vec2(0.0f);
		}
		
		vertices.push_back(vertex);
	}
	
	for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for(unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}
	
	return Mesh(vertices, indices);
}