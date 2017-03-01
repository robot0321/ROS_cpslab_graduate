#include "stdafx.h"
#include "CCDPmap.h"
#include <iostream>

CCDPmap::CCDPmap(Gmap* ptr_gmap, std::vector<float> x_rng, std::vector<float> y_rng) {
	grid = ptr_gmap->getGrid();	
	CCDPmap::setLocalmap(ptr_gmap, x_rng, y_rng);
}

CCDPmap::~CCDPmap() {
	for (int i = 0; i < local_num_y; i++) {
		delete local_map[i];
	}
	delete local_map;
}

void CCDPmap::grid_resize(int factor) {
	int new_x_num = local_num_x/factor;
	int new_y_num = local_num_y/factor;
	float** new_map_tmp = new float*[new_y_num];

	for (int i = 0; i < new_y_num; i++) {
		new_map_tmp[i] = new float[new_x_num];
		for (int j = 0; j < new_x_num; j++) {
			new_map_tmp[i][j] = local_map[2 * i][2 * j]; //Need to edit the resizing way
		}
	}
	//delete memory of local_map pointer
	for (int i = 0; i < local_num_y; i++) {
		delete local_map[i];
	}
	delete local_map;

	local_map = new_map_tmp;
	grid = grid*factor;
	local_num_x = new_x_num;
	local_num_y = new_y_num;

}

void CCDPmap::setLocalmap(Gmap* ptr_gmap, std::vector<float> x_rng, std::vector<float> y_rng) {
	local_x_rng = x_rng;
	local_y_rng = y_rng;
	local_x_len = local_x_rng[1] - local_x_rng[0];
	local_y_len = local_y_rng[1] - local_y_rng[0];
	local_num_x = local_x_len / grid;
	local_num_y = local_y_len / grid;
	
	float** global_map = ptr_gmap->getGlobalmap();
	std::vector<float> global_Xrng = ptr_gmap->getXrng();
	std::vector<float> global_Yrng = ptr_gmap->getYrng();

	local_map = new float*[local_num_y];
	for (int i = 0; i < local_num_y; i++) {
		local_map[i] = new float[local_num_x];
		for (int j = 0; j < local_num_x; j++) {
			local_map[i][j] = global_map[i + int((local_y_rng[0] - global_Yrng[0]) / grid)][j + int((local_x_rng[0] - global_Xrng[0]) / grid)];
		}
	}
}

float** CCDPmap::getLocalmap() const {return local_map;}

void CCDPmap::printLocalmap() const {
	for (int i = 0; i < local_num_y; i++) {
		for (int j = 0; j < local_num_x; j++) {
			if (i == -int(local_y_rng[0] / grid)) {
				std::cout << "^";
			}
			else if (j == -int(local_x_rng[0] / grid)) {
				std::cout << "<";
			}
			else {
				std::cout << local_map[local_num_y - 1 - i][j];
			}
		}
		std::cout << std::endl;
	}
}


int main() {
	std::vector<float> x = { -10,10 };
	std::vector<float> y = { -10,10 };
	system("PAUSE");
	Gmap* a = new Gmap();
	a->printGlobalmap();
	system("PAUSE");
	CCDPmap* b = new CCDPmap(a, x, y);
	b->printLocalmap();
	system("PAUSE");
	b->grid_resize(2);
	b->printLocalmap();
	system("PAUSE");

	delete b;
	delete a;


	return 0;
}

