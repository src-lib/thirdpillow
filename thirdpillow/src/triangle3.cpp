#include "triangle3.h"

triangle3::triangle3() {
    vertices[0] = vector3();
    vertices[1] = vector3();
    vertices[2] = vector3();
}

triangle3::triangle3(vector3 a, vector3 b, vector3 c) {
    vertices[0] = a;
    vertices[1] = b;
    vertices[2] = c;
    calculate_normal();
}

triangle3::triangle3(vector3* vertices) {
    vertices[0] = vertices[0];
    vertices[1] = vertices[1];
    vertices[2] = vertices[2];
    calculate_normal();
}

vector3 triangle3::get_normal() {
    return normal;
}

void triangle3::calculate_normal() {
    vector3 u = vertices[1];
    u.subtract(vertices[0]);
    vector3 v = vertices[2];
    v.subtract(vertices[0]);
    u.cross_product(v);
    u.normalize();
    normal = u;
}

vector3* triangle3::get_vertices() {
    return &vertices[0];
}

vector3 triangle3::get_center() {
    float x = (vertices[0].get_x() + vertices[1].get_x() + vertices[2].get_x()) / 3;
    float y = (vertices[0].get_y() + vertices[1].get_y() + vertices[2].get_y()) / 3;
    float z = (vertices[0].get_z() + vertices[1].get_z() + vertices[2].get_z()) / 3;
    vector3 center(x, y, z);
    return center;
}

triangle2 triangle3::flatten(matrix4 m) {
    vector2 tri2[3];
    for (int i = 0; i < 3; i++) {
        vector4 point(vertices[i]);
        point.multiply_first(m);
        point.set_x(point.get_x() / point.get_w());
        point.set_y(point.get_y() / point.get_w());
        point.set_z(point.get_z() / point.get_w());
        point.set_x(point.get_x() / point.get_z());
        point.set_y(point.get_y() / point.get_z());
        float p_x = ((point.get_x() / (float)2) + (float)0.5) * (float)t_transform::get_camera()->get_render_width();
        float p_y = ((point.get_y() / (float)2) + (float)0.5) * (float)t_transform::get_camera()->get_render_height();
        vector2 v2(p_x, p_y);
        tri2[i] = v2;
    }
    triangle2 result(tri2[0], tri2[1], tri2[2]);
    return result;
}

triangle2 triangle3::flatten_z(matrix4 m, float* z_depth) {
    vector2 tri2[3];
    float z_values[3];
    for (int i = 0; i < 3; i++) {
        vector4 point(vertices[i]);
        point.multiply_first(m);
        point.set_x(point.get_x() / point.get_w());
        point.set_y(point.get_y() / point.get_w());
        point.set_z(point.get_z() / point.get_w());
        z_values[i] = point.get_z();
        point.set_x(point.get_x() / point.get_z());
        point.set_y(point.get_y() / point.get_z());
        float p_x = ((point.get_x() / (float)2) + (float)0.5) * (float)t_transform::get_camera()->get_render_width();
        float p_y = ((point.get_y() / (float)2) + (float)0.5) * (float)t_transform::get_camera()->get_render_height();
        vector2 v2(p_x, p_y);
        tri2[i] = v2;
    }
    triangle2 result(tri2[0], tri2[1], tri2[2]);
    for (int j = 0; j < 3; j++) {
        z_depth[j] = z_values[j];
    }
    return result;
}

triangle3::~triangle3() {

}
