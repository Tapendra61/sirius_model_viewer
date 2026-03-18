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
    vec3 albedo = vec3(1.0); // fallback if albedo not found
    if (material.has_diffuse)
        albedo = texture(material.diffuse, tex_coord_).rgb;

    vec3 normal = normalize(normal_);
    if (material.has_normal)
    {
        vec3 normal_map = texture(material.normal, tex_coord_).rgb;
        normal_map = normal_map * 2.0 - 1.0;
        normal = normalize(tbn_matrix_ * normal_map);
    }

    vec3 light_direction = normalize(LIGHT_POS - frag_pos_);
    float diff = max(dot(normal, light_direction), 0.0);
    
    vec3 ambient  = 1 * albedo;
    vec3 diffuse  = diff * albedo * 3.0;

    vec3 view_direction = normalize(view_pos_ - frag_pos_);
    vec3 reflect_direction = reflect(-light_direction, normal);
    
    vec3 halfway_direction = normalize(light_direction + view_direction);
    
    float specular_factor = pow(max(dot(normal, halfway_direction), 0.0), 32.0);
    vec3 specular_color = vec3(1.0); // fallback for specular color if no specular texture is found
    if(material.has_specular) {
    	specular_color = texture(material.specular, tex_coord_).rgb;
    }
    
    vec3 specular = specular_factor * specular_color;
    
    frag_color_ = vec4(ambient + diffuse + specular, 1.0);
}