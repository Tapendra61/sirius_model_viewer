#version 330 core

in vec3 normal_;
in vec3 frag_pos_;
in vec2 tex_coord_;
in mat3 tbn_matrix_;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
};

uniform Material material;

const vec3 LIGHT_POS = vec3(-1.0, 3.0, 4.0);

out vec4 frag_color_;

void main() {
    vec4 result;
    vec4 ambient = vec4(0.4, 0.4, 0.4, 1.0);

    vec3 texture_color = texture(material.diffuse, tex_coord_).rgb;

    // --- NORMAL MAP ---
    vec3 normal_map = texture(material.normal, tex_coord_).rgb;

    // Convert from [0,1] → [-1,1]
    normal_map = normal_map * 2.0 - 1.0;

    // Transform from tangent space → world space
    vec3 normal = normalize(tbn_matrix_ * normal_map);

    vec3 light_direction = normalize(LIGHT_POS - frag_pos_);

    float diffuse_factor = max(dot(light_direction, normal), 0.0);

    result = diffuse_factor * vec4(texture_color, 1.0);

    frag_color_ = result;
}