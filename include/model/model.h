#pragma once

#include <string>
#include <vector>

#include "assimp/scene.h"

#include "model/mesh.h"


class Model {
	private:
		std::string model_path_;
		std::vector<Mesh> meshes_;
		
	public:
		Model(std::string model_path);
		Model(const Model&)=delete;
		Model& operator=(const Model&)=delete;
		Model(Model&& other)=default;
		Model& operator=(Model&& other)=default;
		
		void draw() const;
		
	private:
		void load_model();
		void process_node(aiNode* node, const aiScene* scene);
};