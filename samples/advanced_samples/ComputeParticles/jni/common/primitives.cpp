/* Copyright (c) 2014-2017, ARM Limited and Contributors
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "primitives.h"

Mesh gen_normal_plane()
{
    const float hs = 1.0f;

    // All faces are oriented counter-clockwise outwards
    float vertices[] = {
        -hs, 0.0f, -hs, 0.0f, 1.0f, 0.0f,
         hs, 0.0f, -hs, 0.0f, 1.0f, 0.0f,
         hs, 0.0f,  hs, 0.0f, 1.0f, 0.0f,
        -hs, 0.0f,  hs, 0.0f, 1.0f, 0.0f
    };

    uint32 indices[] = { 0, 1, 2, 2, 3, 0 };

    Mesh mesh;
    mesh.vertex_buffer = gen_buffer(GL_ARRAY_BUFFER, sizeof(vertices), vertices);
    mesh.index_buffer = gen_buffer(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices);
    mesh.num_indices = 6;
    mesh.num_vertices = 4;
    return mesh;
}

Mesh gen_tex_quad()
{
    const float hs = 1.0f;

    // All faces are oriented counter-clockwise outwards
    float vertices[] = {
        -hs, -hs, 0.0f, 0.0f, 0.0f,
         hs, -hs, 0.0f, 1.0f, 0.0f,
         hs,  hs, 0.0f, 1.0f, 1.0f,
        -hs,  hs, 0.0f, 0.0f, 1.0f
    };

    uint32 indices[] = { 0, 1, 2, 2, 3, 0 };

    Mesh mesh;
    mesh.vertex_buffer = gen_buffer(GL_ARRAY_BUFFER, sizeof(vertices), vertices);
    mesh.index_buffer = gen_buffer(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices);
    mesh.num_indices = 6;
    mesh.num_vertices = 4;
    return mesh;
}

Mesh gen_unit_sphere(int t_samples, int s_samples)
{
    vec3 *vertices = new vec3[t_samples * s_samples * 4];
    uint32 *indices = new uint32[t_samples * s_samples * 6];

    uint32 vertex_index = 0;
    uint32 index_index = 0;
    float dtheta = 2.0f * PI / float(t_samples);
    float dphi = PI / float(s_samples);
    for (int t = 0; t < t_samples; ++t)
    {
        for (int s = 0; s < s_samples; ++s)
        {
            float theta = t * dtheta;
            float phi = s * dphi;

            float r0 = sin(phi);
            float r1 = sin(phi + dphi);

            vec3 v00(r0 * cos(theta), cos(phi), r0 * sin(theta));
            vec3 v10(r0 * cos(theta + dtheta), cos(phi), r0 * sin(theta + dtheta));
            vec3 v01(r1 * cos(theta), cos(phi + dphi), r1 * sin(theta));
            vec3 v11(r1 * cos(theta + dtheta), cos(phi + dphi), r1 * sin(theta + dtheta));

            vertices[vertex_index + 0] = v00;
            vertices[vertex_index + 1] = v01;
            vertices[vertex_index + 2] = v11;
            vertices[vertex_index + 3] = v10;

            indices[index_index + 0] = vertex_index + 0;
            indices[index_index + 1] = vertex_index + 1;
            indices[index_index + 2] = vertex_index + 2;
            indices[index_index + 3] = vertex_index + 2;
            indices[index_index + 4] = vertex_index + 3;
            indices[index_index + 5] = vertex_index + 0;

            vertex_index += 4;
            index_index += 6;
        }
    }   

    Mesh mesh;
    mesh.vertex_buffer = gen_buffer(GL_ARRAY_BUFFER, t_samples * s_samples * 4 * sizeof(vec3), vertices);
    mesh.index_buffer = gen_buffer(GL_ELEMENT_ARRAY_BUFFER, t_samples * s_samples * 6 * sizeof(uint32), indices);
    mesh.num_indices = index_index;
    mesh.num_vertices = vertex_index;
    return mesh;
}

void Mesh::dispose()
{
    del_buffer(vertex_buffer);
    del_buffer(index_buffer);
}

void Mesh::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
}