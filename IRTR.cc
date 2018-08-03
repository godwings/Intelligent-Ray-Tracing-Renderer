//Make : g++ IRTR.cc -o IRTR -O3 -fopenmp

#include <cmath>
#include <cstdio>
#include <cstdlib>

struct Vector {
  double x, y, z;
  Vector(const double &_x = 0., const double &_y = 0., const double &_z = 0.) {
    x = _x;
    y = _y;
    z = _z;
  }
  Vector operator+(const Vector &rhs) const {
    return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
  }
  Vector operator-(const Vector &rhs) const {
    return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
  }
  Vector operator*(const double &rhs) const {
    return Vector(x * rhs, y * rhs, z * rhs);
  }
  Vector operator*(const Vector &rhs) const { // cross
    return Vector(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
  }
  double operator/(const Vector &rhs) const { // dot
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }
  Vector &normalize() {
    *this = *this * (1. / sqrt(x * x + y * y + z * z));
    return *this;
  }
};

struct Ray {
  Vector ori, dir;
  Ray(const Vector &_ori, const Vector &_dir) {
    ori = _ori;
    dir = _dir;
  }
};

enum ReflectionType {
  Specular, Glass, Diffuse
};
struct Sphere {
  double r;
  Vector p, e, c;
  ReflectionType t;
  static constexpr double eps = 1e-5;
  Sphere(const double &_radius, const Vector &_position,
         const Vector &_emission, const Vector &_colour,
         const ReflectionType &_refl_type) {
    r = _radius;
    p = _position;
    e = _emission;
    c = _colour;
    t = _refl_type;
  }
  double Intersect(const Ray &ray) { // returns distance, -1 if nohit
    const Vector o_minus_p = ray.ori - p;
    const double a = ray.dir / ray.dir;
    const double b = ray.dir / o_minus_p * 2;
    const double c = o_minus_p / o_minus_p - r;
    double delta = b * b - a * c * 4;
    if (delta < 0)
      return -1;
    delta = sqrt(delta);
    const double t_1 = (- b - delta) / (a * 2);
    const double t_2 = (- b + delta) / (a * 2);
    if (t_1 > eps)
      return t_1;
    if (t_2 > eps)
      return t_2;
    return -1;
  }
};

// Scene Settings
const Sphere spheres[] = {
  Sphere(1e5, Vector(1e5 + 1, 40.8, 81.6), Vector(),
         Vector(.75, .25, .25), Specular)
};
const Ray camera(Vector(50, 52, 295.6),
                 Vector(0, -0.042612, -1).normalize());
//

Vector Radiance(const Ray &r, int depth, unsigned short *Xi) {

}

int main(int argc, char *argv[]) {
  int w = 1024, h = 768;
  double lens = .5135;
  int samp_num = 10;
  double f = 5.6;
  for (int i = 1; i < argc; i++) {
    switch (argv[i][1]) {
      case 's': {
        w = atoi(argv[++i]);
        h = atoi(argv[++i]);
        break;
      }
      case 'l': {
        lens = atof(argv[++i]);
        break;
      }
      case 'n': {
        samp_num = atoi(argv[++i]) / 4;
        break;
      }
      case 'f': {
        f = atof(argv[++i]);
        break;
      }
    }
  }
  
  return 0;
}