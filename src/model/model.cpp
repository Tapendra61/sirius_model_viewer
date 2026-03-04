#include "model/model.h"

#include <string>
#include <vector>
#include <cstdint>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "glm/glm.hpp"

#include "renderer/shader.h"
#include "sirius_logger/log.h"
#include "model/mesh.h"

Model::Model(std::string model_path) : model_path_(std::move(model_path)) {
	load_model();
}

void Model::load_model() {
	Assimp::Importer importer;
	const aiScene* ai_scene = importer.ReadFile(model_path_, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);
	
	if(!ai_scene || ai_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !ai_scene->mRootNode) {
		sr::log_error("Failed to load model! Error: {}", importer.GetErrorString());
		return;
	}
	
	process_node(ai_scene->mRootNode, ai_scene, glm::mat4(1.0f));
}

void Model::process_node(aiNode* node, const aiScene* scene, const glm::mat4& parent_transform) {
	glm::mat4 node_transform = matrix_to_column_major(node->mTransformation);
	glm::mat4 global_transform = parent_transform * node_transform;
	
	for(int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		Mesh processed_mesh = process_mesh(mesh, scene);
		meshes_.push_back({ std::move(processed_mesh), global_transform });
	}
	
	for(int i = 0; i < node->mNumChildren; i++) {
		process_node(node->mChildren[i], scene, global_transform);
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

glm::mat4 matrix_to_column_major(const aiMatrix4x4& matrix) const {
	glm::mat4 result;
	result[0][0] = matix.a1; result[1][0] = matix.a2;
	result[2][0] = matix.a3; result[3][0] = matix.a4;
	
	result[0][1] = matix.b1; result[1][1] = matix.b2;
	result[2][1] = matix.b3; result[3][1] = matix.b4;
	
	result[0][2] = matix.c1; result[1][2] = matix.c2;
	result[2][2] = matix.c3; result[3][2] = matix.c4;
	
	result[0][3] = matix.d1; result[1][3] = matix.d2;
	result[2][3] = matix.d3; result[3][3] = matix.d4;
	
	return result;
}

void Model::draw() const {
	for(auto& mesh: meshes_) {
		mesh.draw();
	}
}