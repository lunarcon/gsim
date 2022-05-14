#include <math.h>
#include <string>

class vec3 {
    public:
        double x;
        double y;
        double z;

        vec3() {
            this->x = 0; this->y = 0; this->z = 0;
        }

        vec3(double x, double y, double z) {
            this->x = x; this->y = y; this->z = z;
        }

        double dist_to(vec3 other) {
            return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2) + pow(this->z - other.z, 2));
        }
        
        vec3 operator+(vec3 other) {
            return vec3(this->x + other.x, this->y + other.y, this->z + other.z);
        }

        vec3 operator-(vec3 other) {
            return vec3(this->x - other.x, this->y - other.y, this->z - other.z);
        }

        bool operator==(vec3 other) {
            return this->x==other.x && this->y==other.y && this->z==other.z;
        }

        bool operator!=(vec3 other) {
            return !this->operator==(other);
        }

        vec3 operator/(double other) {
            return vec3(this->x/other, this->y/other, this->z/other);
        }

        vec3 operator*(vec3 other) {
            return vec3(this->y*other.z - this->z*other.y, this->z*other.x - this->x*other.z , this->x*other.y - this->y*other.x);
        }

        vec3 operator*(double other) {
            return vec3(this->x*other, this->y*other, this->z*other);
        }

        vec3 dot(vec3 other) {
            return vec3(this->x*other.x, this->y*other.y, this->z*other.z);
        }

        operator std::string() const { 
            return "(" + std::to_string(this->x/1000) + ", " + std::to_string(this->y/1000) + ", " + std::to_string(this->z/1000) + ")";
        }

};
