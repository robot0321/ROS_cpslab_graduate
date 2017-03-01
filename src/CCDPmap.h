#pragma once
#include <vector>
#include "Gmap.h"

class CCDPmap { //get Local CCDP map
private:
	std::vector<float> local_x_rng;
	std::vector<float> local_y_rng;
	float local_x_len;
	float local_y_len;
	int local_num_x;
	int local_num_y;
	float grid;
	float** local_map;


public:
	CCDPmap(Gmap* ptr_gmap, std::vector<float> x_rng, std::vector<float> y_rng);
	~CCDPmap();


	void grid_resize(int factor);

	void setLocalmap(Gmap* ptr_gmap, std::vector<float> x_rng, std::vector<float> y_rng);
	float** getLocalmap() const;
	void printLocalmap() const;
};