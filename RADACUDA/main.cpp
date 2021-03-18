// the main solving loop
//figure it out later

#include "ray.h"
#include "primitives.h"
#include "utility.h"
#include "vec3.h"

#include "gnuplot.h"

#include <cstdlib>
#include <vector>
#include <string>
#include <chrono>


int main() {
	
	// RIGHT NOW THE MAIN FUNCTION BUILDS A RECTANGLE AND CHECKS IF A FEW RAYS HIT IT
	// 	   NO FANCY CALCULATIONS AT THE MOMENT
 
	// start timer
	auto tstart = std::chrono::high_resolution_clock::now();

	// origin rectangle setup
	point3 r_or = point3(0.0, 0.0, 0.0);
	double dim1 = 1;
	double dim2 = 1;
	vec3 S1 = vec3(1.0, 0.0, 0.0);
	vec3 S2 = vec3(0.0, 1.0, 0.0);

	rectangle orig_rect = rectangle(r_or, S1, S2, dim1, dim2, 1, 1);

	// target rectangle setup
    r_or = point3(0.0, 0.0, 1.0);
	dim1 = 1;
	dim2 = 1;
	S1 = vec3(1.0, 0.0, 0.0);
	S2 = vec3(0.0, 1.0, 0.0);

	rectangle tgt_rect = rectangle(r_or, S1, S2, dim1, dim2, 1, 1);

	// plot the rectangles
	GnuplotPipe gp;
	gp.sendLine("set hidden3d");
	gp.sendLine("set view equal xyz");
	gp.sendLine("set key off");
	gp.sendLine("set xrange [0:1]");
	gp.sendLine("set yrange [0:1]");
	gp.sendLine("set zrange [0:1]");
	gp.sendLine("set cbrange [0:1]");
	gp.sendLine("unset colorbox");
	gp.sendLine("set parametric");
	gp.sendLine("splot " + orig_rect.gnuplot_repr() + " with pm3d fs solid fc '#A00000FF'");
	gp.sendLine("replot " + tgt_rect.gnuplot_repr() + " with pm3d fs solid fc '#A0FF0000'");



	// ray setup
	int N_rays = 100; // number of rays to shoot from target
	
	point3 ray_origin = orig_rect.node_list[0].location;
	std::vector<ray> ray_list;
	std::vector<hit_record> hit_rec_list;
	int hit_count = 0;

	ray_list.reserve(N_rays);
	hit_rec_list.reserve(N_rays);

	// shoot the rays
	for (int ii = 0; ii < N_rays; ++ii) {
		vec3 ray_dir = unit_vector(random_in_hemisphere(orig_rect.normal));

		ray_list.push_back(ray(ray_origin, ray_dir));
		hit_rec_list.push_back(hit_record());
		bool ray_hits = tgt_rect.hit(ray_list[ii], 0.0, infinity, hit_rec_list[ii]);
		

		// if ray hits, it is absorbed (for now assuming totally black surface)
		if (ray_hits) {
			hit_count++;
			gp.sendLine("replot " + ray_list[ii].gnuplot_repr(0,1) + "linecolor 'green'");
			std::cout << "Ray " + std::to_string(ii) << ": hit\n";
		}
		else {
			gp.sendLine("replot " + ray_list[ii].gnuplot_repr(0, 1) + "linecolor 'red'");
		}
	}

	// calculate final view factor (hits / rays
	double view_factor = hit_count / (double)N_rays;
	std::cout.precision(3);
	std::cout << "Estimated View Factor:\t" << std::fixed << view_factor << "(" << hit_count <<
		"/" << N_rays << ")\n";

	// stop timer
	auto tend = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> ms_double = tend - tstart;
	std::cout << "Elapsed Time:\t" << std::fixed << ms_double.count() / 1000.0 << " seconds\n";
	
	// finalize the plot
	gp.sendLine("set mouse");
	gp.sendLine("set autoscale");
	gp.sendLine("pause mouse close");
	
	return 0;

}