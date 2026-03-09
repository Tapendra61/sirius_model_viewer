#pragma once

#include <string>
#include <vector>

#include "assimp/scene.h"
#include "glm/glm.hpp"

#include "model/mesh.h"
#include "renderer/shader.h"
#include "renderer/material.h"

class Model {
	private:
		struct MeshEntry {
			Mesh mesh;
			glm::mat4 transform;
			Material material;
		};
		std::string model_path_;
		std::vector<MeshEntry> meshes_;
		
	public:
		Model(std::string model_path);
		Model(const Model&)=delete;
		Model& operator=(const Model&)=delete;
		Model(Model&& other)=default;
		Model& operator=(Model&& other)=default;
		
		void draw(const Shader& shader, const glm::mat4& world_model_matrix) const;
		
	private:
		void load_model();
		void process_node(aiNode* node, const aiScene* scene, const glm::mat4& parent_transform);
		Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
		Material process_material(aiMaterial* ai_material);
		
		glm::mat4 matrix_to_column_major(const aiMatrix4x4& matrix) const;
};