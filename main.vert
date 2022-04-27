#version 450
layout (location = 0) in vec2 aPos;

out vec2 fragCoord;

void main()
{
    fragCoord = aPos;
    gl_Position = vec4(aPos.x, aPos.y, 1.0, 1.0);
}