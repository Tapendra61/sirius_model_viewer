#version 330 core

in vec3 normal_;
in vec3 frag_pos_;
in vec2 tex_coord_;
in mat3 tbn_matrix_;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
    bool has_diffuse;
    bool has_specular;
    bool has_normal;
};

uniform Material material;

uniform vec3 view_pos_;

const vec3 LIGHT_POS = vec3(-1.0, 3.0, 4.0);

out vec4 frag_color_;

void main()
{
    vec3 albedo = vec3(0.85);           // fallback
    if (material.has_diffuse)
        albedo = texture(material.diffuse, tex_coord_).rgb;

    vec3 normal = normalize(normal_);
    if (material.has_normal)
    {
        vec3 normal_map = texture(material.normal, tex_coord_).rgb;
        normal_map = normal_map * 2.0 - 1.0;
        normal = normalize(tbn_matrix_ * normal_map);
    }

    vec3 light_dir = normalize(LIGHT_POS - frag_pos_);
    float diff = max(dot(normal, light_dir), 0.0);

    vec3 ambient  = 0.4 * albedo;
    vec3 diffuse  = diff * albedo * 2.0;   // your original scaling

    frag_color_ = vec4(ambient + diffuse, 1.0);
}