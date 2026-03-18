#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "assimp/scene.h"
#include "glm/glm.hpp"

#include "model/mesh.h"
#include "renderer/shader.h"
#include "renderer/material.h"
#include "renderer/texture.h"
#include "components/transform.h"


class Model {
	private:
		struct MeshEntry {
			Mesh mesh;
			glm::mat4 transform;
			Material material;
		};
		std::string model_path_;
		std::string directory_path_ = "";
		std::vector<MeshEntry> meshes_;
		Transform transform_;
		
		std::unordered_map<std::string, std::shared_ptr<Texture>> texture_cache_;
		
	public:
		Model(std::string model_path, bool flip_uvs);
		Model(const Model&)=delete;
		Model& operator=(const Model&)=delete;
		Model(Model&& other)=default;
		Model& operator=(Model&& other)=default;
		
		Transform& transform() { return transform_; }
		void draw(const Shader& shader) const;
		
	private:
		void load_model(bool flip_uvs);
		void process_node(aiNode* node, const aiScene* scene, const glm::mat4& parent_transform);
		Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
		Material process_material(aiMaterial* ai_material);
		std::shared_ptr<Texture> load_texture_cached(const std::string& path, bool gamma_corrected = false);
		
		glm::mat4 matrix_to_column_major(const aiMatrix4x4& matrix) const;
};