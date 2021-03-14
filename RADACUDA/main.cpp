// the main solving loop
//figure it out later

#include "ray.h"
#include "primitives.h"
#include "utility.h"
#include "vec3.h"

#include <sciplot/sciplot.hpp>
using namespace sciplot;

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
	ray R1 = ray(point3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0)); // this ray should hit
	ray R2 = ray(point3(0.2869, -0.7362, 0.5573), vec3(-0.2295, 0.6767, 0.6996)); // this should also hit
	ray R3 = ray(point3(-0.7049, -0.6884, 0.2164), vec3(0.7458, 0.5867, -0.3154)); // this ray should miss


	hit_record rec;

	bool hit1 = rect.hit(R1, 0, infinity, rec);
	std::cout << "Ray 1: " << hit1 << '\n';
	bool hit2 = rect.hit(R2, 0, infinity, rec);
	std::cout << "Ray 2: " << hit2 << '\n';
	bool hit3 = rect.hit(R3, 0, infinity, rec);
	std::cout << "Ray 3: " << hit3 << '\n';

	// sciplot test
	// Create a vector with x-axis values
	std::vector<int> x = { 0, 1, 2, 3 };

	// Create a vector with y values
	std::vector<float> y = { -4, 2, 5, -3 };

	// Create a Plot object
	Plot plot;

	// Set the legend
	plot.legend().hide();

	// Set the x and y labels
	plot.xlabel("x");
	plot.ylabel("y");

	// Set the y range
	plot.yrange(-5, 5);

	// Add values to plot
	plot.drawBoxes(x, y)
		.fillSolid()
		.fillColor("green")
		.fillIntensity(0.5);

	// Adjust the relative width of the boxes
	plot.boxWidthRelative(0.75);

	// Show the plot in a pop-up window
	plot.show();

}