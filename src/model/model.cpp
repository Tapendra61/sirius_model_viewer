#include "model/model.h"

#include <string>
#include <vector>
#include <cstdint>

#include "glad/glad.h"
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
	
	for(unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		Mesh processed_mesh = process_mesh(mesh, scene);
		meshes_.push_back({ std::move(processed_mesh), global_transform });
	}
	
	for(unsigned int i = 0; i < node->mNumChildren; i++) {
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

glm::mat4 Model::matrix_to_column_major(const aiMatrix4x4& matrix) const {
	glm::mat4 result;
	result[0][0] = matrix.a1; result[1][0] = matrix.a2;
	result[2][0] = matrix.a3; result[3][0] = matrix.a4;
	
	result[0][1] = matrix.b1; result[1][1] = matrix.b2;
	result[2][1] = matrix.b3; result[3][1] = matrix.b4;
	
	result[0][2] = matrix.c1; result[1][2] = matrix.c2;
	result[2][2] = matrix.c3; result[3][2] = matrix.c4;
	
	result[0][3] = matrix.d1; result[1][3] = matrix.d2;
	result[2][3] = matrix.d3; result[3][3] = matrix.d4;
	
	return result;
}

void Model::draw(const Shader& shader, const glm::mat4& world_model_matrix) const {
	for(auto& entry: meshes_) {
		glm::mat4 final_model_matrix = world_model_matrix * entry.transform;
		shader.set_mat4("model", final_model_matrix);
		
		entry.mesh.draw();
	}
}