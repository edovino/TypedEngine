#shader vertex

#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texcoord;

uniform sampler2D uTexture;
uniform mat4 uMvpMatrix;

out vec2 vTexcoord;

void main() {
  gl_Position = uMvpMatrix * vec4(position * textureSize(uTexture, 0), 0.0f, 1.0f);
  vTexcoord = texcoord;
};

#endshader vertex
#shader fragment

#version 330 core

layout(location = 0) out vec4 color;

in vec2 vTexcoord;

uniform sampler2D uTexture;

void main() {
  color = texture(uTexture, vTexcoord);
};

#endshader fragment
