#version 450

#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

in vec3 VertexPosition;
in vec3 VertexColor;

out vec4 Color;
//! [0]
void main()
{
    Color = vec4(1.0, 0.0, 0.0, 1.0);
    gl_Position = vec4(VertexPosition, 1.0);
}
//! [0]
