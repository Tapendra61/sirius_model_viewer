#include "model/model.h"

#include <string>
#include <vector>
#include <cstdint>
#include <memory>
#include <filesystem>

#include "glad/glad.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "glm/glm.hpp"

#include "renderer/shader.h"
#include "renderer/texture.h"
#include "renderer/material.h"
#include "sirius_logger/log.h"
#include "model/mesh.h"

Model::Model(std::string model_path) : model_path_(std::move(model_path)) {
	load_model();
}

void Model::load_model() {
	Assimp::Importer importer;
	const aiScene* ai_scene = importer.ReadFile(model_path_, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);
	
	if(!ai_scene || ai_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !ai_scene->mRootNode) {
		sr::log_error("Failed to load model! Error: {}", importer.GetErrorString());
		return;
	}
	
	directory_path_ = std::filesystem::path(model_path_).parent_path().string();;
	process_node(ai_scene->mRootNode, ai_scene, glm::mat4(1.0f));
}

void Model::process_node(aiNode* node, const aiScene* scene, const glm::mat4& parent_transform) {
	glm::mat4 node_transform = matrix_to_column_major(node->mTransformation);
	glm::mat4 global_transform = parent_transform * node_transform;
	
	for(unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		Mesh processed_mesh = process_mesh(mesh, scene);
		Material processed_material = process_material(scene->mMaterials[mesh->mMaterialIndex]);
		
		meshes_.push_back({ std::move(processed_mesh), global_transform, std::move(processed_material) });
	}
	
	for(unsigned int i = 0; i < node->mNumChildren; i++) {
		process_node(node->mChildren[i], scene, global_transform);
	}
}

Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	
	for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
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
		
		if(mesh->HasTangentsAndBitangents()) {
			vertex.tangent = glm::vec3 {
				mesh->mTangents[i].x,
				mesh->mTangents[i].y,
				mesh->mTangents[i].z,
			};
			
			vertex.bitangent = glm::vec3 {
				mesh->mBitangents[i].x,
				mesh->mBitangents[i].y,
				mesh->mBitangents[i].z,
			};
		}else {
			vertex.tangent = glm::vec3(0.0f);
			vertex.bitangent = glm::vec3(0.0f);
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

Material Model::process_material(aiMaterial* ai_material) {
	Material material;
	
	if(ai_material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
		aiString str;
		ai_material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
		
		std::filesystem::path texture_path = str.C_Str();
		std::filesystem::path full_path = std::filesystem::path(directory_path_) / texture_path;
		
		material.set_diffuse(std::make_shared<Texture>(full_path.string(), true));
	}
	
	if(ai_material->GetTextureCount(aiTextureType_SPECULAR) > 0) {
		aiString str;
		ai_material->GetTexture(aiTextureType_SPECULAR, 0, &str);
		std::string full_path = directory_path_ + "/" + str.C_Str();
		
		material.set_specular(std::make_shared<Texture>(full_path));
	}
	
	if(ai_material->GetTextureCount(aiTextureType_NORMALS) > 0) {
		aiString str;
		ai_material->GetTexture(aiTextureType_NORMALS, 0, &str);
		std::string full_path = directory_path_ + "/" + str.C_Str();
		
		material.set_normal(std::make_shared<Texture>(full_path));
	}
	else if(ai_material->GetTextureCount(aiTextureType_HEIGHT) > 0) {
		aiString str;
		ai_material->GetTexture(aiTextureType_HEIGHT, 0, &str);
		std::string full_path = directory_path_ + "/" + str.C_Str();
		
		material.set_normal(std::make_shared<Texture>(full_path));
	}
	
	return material;
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

void Model::draw(const Shader& shader) const {
	for(const auto& entry: meshes_) {
		glm::mat4 final_model_matrix = transform_.matrix() * entry.transform;
		shader.set_mat4("model", final_model_matrix);
		entry.material.bind(shader);
		
		entry.mesh.draw();
	}
}