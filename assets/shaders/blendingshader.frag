#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{             
    if(texture(texture1, TexCoords).a < 0.1)
        discard;

    FragColor = vec4(texture(texture1, TexCoords));
}