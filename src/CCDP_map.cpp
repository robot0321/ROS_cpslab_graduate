#include "stdafx.h"

#include <vector>
#include <iostream>

class CCDP_map{
private:
	float grid;
	float glen;
	std::vector<float> x_rng;
	std::vector<float> y_rng;
	float x_len;
	float y_len;
	int num_yaxis;
	int num_xaxis;
	std::vector<std::vector<float>> list_object; //object: [x, y, xlen, ylen, degree]
	float** global_map;
	float** local_map;

public:
	CCDP_map();
	CCDP_map(int map_number);
	~CCDP_map();
	
	void load_map(int num_map);
	void make_global_map();
	int obj_collision(float y, float x);
	void getObjects();
	void setObjects(float x, float y, float xlen, float ylen, float degree);
	float** getGlobalmap();
	void getLocalmap();
};


CCDP_map::CCDP_map(){
	CCDP_map::load_map(1);
	CCDP_map::make_global_map();
}

CCDP_map::CCDP_map(int map_number){
	CCDP_map::load_map(map_number);
	CCDP_map::make_global_map();
}

CCDP_map::~CCDP_map(){
	int num_list = list_object.size();
	if(num_list>0){
		for(int i=0; i<num_list; i++){
			list_object[num_list -1 - i].clear();
		}
		list_object.clear();
	}

	for(int i=0; i<num_yaxis; i++){
		delete global_map[i];
	}
	delete global_map;
}


void CCDP_map::getObjects(){
	int num_list = list_object.size();
	int loop_count=0;
	if(num_list>0){
		for(int i=0; i<num_list; i++){
			list_object[i];
		}
	}else{
		std::cout << "# of object list is " << num_list << std::endl;
	}
}

void CCDP_map::setObjects(float x, float y, float xlen, float ylen, float degree){
	int num_list = list_object.size();

	list_object.push_back(std::vector<float>());

	list_object[num_list].push_back(x);
	list_object[num_list].push_back(y);
	list_object[num_list].push_back(xlen);
	list_object[num_list].push_back(ylen);
	list_object[num_list].push_back(degree);
	
}

void CCDP_map::load_map(int num_map){
	switch(num_map){
	case 1:
		grid = 0.5;
		glen = 1;
		int a[2] = { 1,2 };
		x_rng = {-10, 10};
		y_rng = {-10, 10};
		x_len = x_rng[1] - x_rng[0];
		y_len = y_rng[1] - y_rng[0];

		CCDP_map::setObjects(2, 2, 2, 3, 0); //box1
		CCDP_map::setObjects(-4.5, -4.5, 4, 4, 0); //box2
		CCDP_map::setObjects(-3.5, 4, 3, 3, 0); //box3
		CCDP_map::setObjects(3, -7, 3, 3, 0); //box4
		CCDP_map::setObjects(7, 5.5, 2, 2, 0); //box5
		break;
	
	}
}

void CCDP_map::make_global_map(){
	num_yaxis = (y_rng[1] - y_rng[0])/grid;
	num_xaxis = (x_rng[1] - x_rng[0])/grid;
	
	global_map = new float*[num_yaxis]; //global_map[y][x]
	for(int i=0; i<num_yaxis; i++){
		global_map[i] = new float[num_xaxis];
		for(int j=0; j<num_xaxis; j++){
			global_map[i][j] = obj_collision(i*grid - y_len/2.0, j*grid - x_len/2.0);
		}
	}


}

int CCDP_map::obj_collision(float y, float x){
	int obj=0;
	for(int k=0;k<list_object.size();k++){
		obj = (int)(list_object[k][0]-list_object[k][2]/2.0 <= x && list_object[k][0]+list_object[k][2]/2.0>x && list_object[k][1]-list_object[k][3]/2.0<=y && list_object[k][1]+list_object[k][3]/2.0>y);
		if(obj==1) break;
	}

	return obj;
}

float** CCDP_map::getGlobalmap(){
	for(int i=0; i<num_yaxis; i++){
		for(int j=0; j<num_xaxis; j++){
			if (i == num_yaxis/2.0) {
				std::cout << "^";
			}
			else if (j == num_xaxis / 2.0) {
				std::cout << "<";
			}
			else {
				std::cout << global_map[num_yaxis-1-i][j];// << " ";
			}
		}
		std::cout<<std::endl;
	}
	return global_map;
}

void CCDP_map::getLocalmap(){

}


int main() {
	system("PAUSE");
	CCDP_map* a = new CCDP_map();
	a->getGlobalmap();
	system("PAUSE");
	delete a;


	return 0;
}