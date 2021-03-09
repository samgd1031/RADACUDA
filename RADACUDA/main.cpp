// the main solving loop
//figure it out later

#include "ray.h"
#include "primitives.h"
#include "utility.h"
#include "vec3.h"

int main() {
	
	// RIGHT NOW THE MAIN FUNCTION BUILDS A RECTANGLE AND CHECKS IF A FEW RAYS HIT IT
	// 	   NO FANCY CALCULATIONS AT THE MOMENT
	// rectangle setup
	point3 r_or = point3(-1.0, -1.0, 1.0);
	double dim1 = 2;
	double dim2 = 2;
	vec3 S1 = vec3(1.0, 0.0, 0.0);
	vec3 S2 = vec3(0.0, 1.0, 0.0);

	rectangle rect = rectangle(r_or, S1, S2, dim1, dim2);

	// ray setup
	ray R1 = ray(point3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0));

	ray R2 = ray(point3(0.2869, -0.7362, 0.5573), vec3(-0.2295, 0.6767, 0.6996));

	ray R3 = ray(point3(-0.7049, -0.6884, 0.2164), vec3(0.7458, 0.5867, -0.3154));


	hit_record rec;

	bool hit1 = rect.hit(R1, 0, infinity, rec);
	std::cout << "Ray 1: " << hit1 << '\n';
	bool hit2 = rect.hit(R2, 0, infinity, rec);
	std::cout << "Ray 2: " << hit2 << '\n';
	bool hit3 = rect.hit(R3, 0, infinity, rec);
	std::cout << "Ray 3: " << hit3 << '\n';

}