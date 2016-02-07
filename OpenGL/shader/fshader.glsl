#version 450

#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;

in vec4 Color;
in vec2 v_texcoord;
out vec4 FragColor;
//! [0]
void main()
{
    // Set fragment color from texture
    // FragColor = texture2D(texture, v_texcoord);
    FragColor = Color;
}
//! [0]

