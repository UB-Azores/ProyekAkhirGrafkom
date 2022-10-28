#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

// Texture samplers
uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);

    // Ambient
    //float ambientStrength = 0.1;
    //vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    //vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(lightPos - FragPos);
    //float diff = max(dot(norm, lightDir), 0.0);    
    //vec3 diffuse = diff * lightColor * diffuseCoeff;                

    // Specular
    //float specularStrength = 0.5;
    //vec3 viewDir = normalize (viewPos - FragPos);
    //vec3 reflectDir = reflect(-lightDir , norm);
    //int n = 32;
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);    
    //vec3 specular = specularStrength * spec * lightColor;              

    //vec3 result = (ambient + specular + diffuse) * objectColor;    
    //FragColor = vec4(result, 1.0);
}