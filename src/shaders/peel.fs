#version 410 core

in  vec4 pos_fs_in;
out vec4 color;

void main()
{
    // Set color to screen position to show something
    color = vec4(vec3(1,1,1) * pos_fs_in.xyz, 1);
}