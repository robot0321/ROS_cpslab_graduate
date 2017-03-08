#pragma once
#include <vector>
#include "Gmap.h"

#ifndef PI
	#define PI 3.141593
#endif // !


class CCDPmap { //get Local CCDP map
private:
	std::vector<float> local_x_rng;
	std::vector<float> local_y_rng;
	float local_x_len;
	float local_y_len;
	int local_num_x;
	int local_num_y;
	float grid;
	int ndir;
	int nvis;
	int H_step;
	float threshold_track;
	std::vector<float> sensor_dir;
	

	float** local_map;
	float** Cost_visual;
	float** Cost_avoid;
	float*** Cost_track;
	float*** Cost_const; // avoid + const

public:
	CCDPmap(Gmap* ptr_gmap, std::vector<float> x_rng, std::vector<float> y_rng, float epsilon = 0.3);
	~CCDPmap();


	void grid_resize(int factor);

	void setLocalmap(Gmap* ptr_gmap, std::vector<float> x_rng, std::vector<float> y_rng);
	float** getLocalmap() const;
	void printLocalmap() const;

	float** getCost_visual() const;
	float** getCost_avoid() const;
	float** getCost_track(int ndir) const;
	float** getCost_const(int ndir) const;

	void CCDPmap::initCostfunc();
};