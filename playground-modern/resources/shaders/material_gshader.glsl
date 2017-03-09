#version 330 core

layout(triangles) in;
layout(points, max_verticss = 6) out;

void main()
{
  gl_Position = gl_in[0].gl_Position + vec3(0.05);
  EmitVertex();
  gl_Position = gl_in[1].gl_Position + vec3(0.05);
  EmitVertex();
  gl_Position = gl_in[2].gl_Position + vec3(0.05);
  EmitVertex();
  EndPrimitive();
  
  gl_Position = gl_in[0].gl_Position;
  EmitVertex();
  gl_Position = gl_in[1].gl_Position;
  EmitVertex();
  gl_Position = gl_in[2].gl_Position;
  EmitVertex();
  EndPrimitive();
}
