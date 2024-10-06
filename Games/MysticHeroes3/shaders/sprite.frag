#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D spriteImage;

void main()
{
	vec4 texColor = texture(spriteImage, TexCoord);

    if (texColor.a < 0.1)
    {
        discard;
    }

    FragColor = texColor;
}