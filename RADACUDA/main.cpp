// the main solving loop
//figure it out later

#include "ray.h"
#include "primitives.h"
#include "utility.h"
#include "vec3.h"

#include "gnuplot.h"


int main() {
	
	// RIGHT NOW THE MAIN FUNCTION BUILDS A RECTANGLE AND CHECKS IF A FEW RAYS HIT IT
	// 	   NO FANCY CALCULATIONS AT THE MOMENT
	// rectangle setup
	point3 r_or = point3(-1.0, -1.0, 1.0);
	double dim1 = 2;
	double dim2 = 2;
	vec3 S1 = vec3(1.0, 0.0, 0.5);
	vec3 S2 = vec3(0.0, 1.0, 0.0);

	rectangle rect = rectangle(r_or, S1, S2, dim1, dim2, 1, 1);

	// ray setup
	ray R1 = ray(point3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0)); // this ray should hit
	ray R2 = ray(point3(0.2869, -0.7362, 0.5573), vec3(-0.2295, 0.6767, 0.6996)); // this should also hit
	ray R3 = ray(point3(-0.7049, -0.6884, 0.2164), vec3(0.7458, 0.5867, -0.3154)); // this ray should miss


	hit_record rec1, rec2, rec3;

	bool hit1 = rect.hit(R1, 0, infinity, rec1);
	std::cout << "Ray 1: " << hit1 << '\n';
	bool hit2 = rect.hit(R2, 0, infinity, rec2);
	std::cout << "Ray 2: " << hit2 << '\n';
	bool hit3 = rect.hit(R3, 0, infinity, rec3);
	std::cout << "Ray 3: " << hit3 << '\n';

	std::cout << R2.gnuplot_repr(0, (hit2) ? rec2.t : 1) << '\n';

	GnuplotPipe gp;
	gp.sendLine("set hidden3d");
	gp.sendLine("set view equal xyz");
	gp.sendLine("set key off");
	gp.sendLine("set xrange [-1:1]");
	gp.sendLine("set yrange [-1:1]");
	gp.sendLine("unset colorbox");
	gp.sendLine("set parametric");
	gp.sendLine("splot " + R1.gnuplot_repr(0,1));
	
	gp.sendLine("replot " + R2.gnuplot_repr(0,1));
	gp.sendLine("replot " + R3.gnuplot_repr(0,0.1));	
	gp.sendLine("replot " + rect.gnuplot_repr());
	gp.sendLine("set mouse");
	gp.sendLine("set autoscale");
	gp.sendLine("pause mouse close");
	
	return 0;

}