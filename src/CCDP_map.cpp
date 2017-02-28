#include <vector>
#include <iostream>

class CCDP_map{
private:
	float grid;
	float glen;
	float x_rng[2];
	float y_rng[2];
	float x_len;
	float y_len;
	std::vector<std::vector<float*>> list_object //object: [x, y, xlen, ylen, degree]
	float** global_map;
	float** local_map;

public:
	CCDP_map();
	CCDP_map(int map_number, float res=0.1);
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
			list_object[num_list - i].clear();
		}
		list_object.clear();
	}

	for(int i=0; i<num_yaxis; i++){
		delete global_map[i];
	}
	delete global_map;
}


void CCDP::getObjects(){
	int num_list = list_object.size();
	int loop_count=0;
	if(num_list>0){
		for(int i=0; i<num_list; i++){
			list_object[i]
		}
	}else{
		cout << "# of object list is " << num_list << endl;
	}
}

void CCDP::setObjects(float x, float y, float xlen, float ylen, float degree){
	int num_list = list_object.size();

	list_object.push_back(std::vector<float*>());

	list_object[num_list].push_back(x);
	list_object[num_list].push_back(y);
	list_object[num_list].push_back(xlen);
	list_object[num_list].push_back(ylen);
	list_object[num_list].push_back(degree);
	
}

void CCDP::load_map(int num_map){
	switch(num_map){
	case 1:
		grid = 0.5;
		glen = 1;
		x_rng = {-10, 10};
		y_rng = {-10, 10};
		xlen = x_rng[1] - x_rng[0];
		ylen = y_rng[1] - y_rng[0];

		CCDP::setObjects(2, 2, 2, 3, 0); //box1
		CCDP::setObjects(-4.5, -4.5, 4, 4, 0); //box2
		CCDP::setObjects(-3.5, 4, 3, 3, 0); //box3
		CCDP::setObjects(3, -7, 3, 3, 0); //box4
		CCDP::setObjects(7, 5.5, 2, 2, 0); //box5
		break;
	
	}
}

void CCDP_map::make_global_map(){
	int num_yaxis = (y_rng[1] - y_rng[0])/grid;
	int num_xaxis = (x_rng[1] - x_rng[0])/grid;
	
	global_map = new float*[num_yaxis]; //global_map[y][x]
	for(int i=0; i<num_yaxis; i++){
		global_map[i] = new float[num_xaxis];
		for(int j=0; j<num_xaxis; j++){
			global_map[i][j] = obj_collision(i*grid, j*grid);
		}
	}


}

int obj_collision(float y, float x){
	int obj=0;
	for(k=0;k<list_object.size();k++){
		obj = (int)(list_object[k][0]-list_object[k][2]/2.0=<x && list_object[k][0]+list_object[k][2]/2.0>x && list_object[k][1]-list_object[k][3]/2.0=<y && list_object[k][1]+list_object[k][3]/2.0>y);
		if(obj==1) break;
	}

	return obj
}

float** CCDP_map::getGlobalmap()[
	for(int i=0; i<num_yaxis; i++){
		for(int j=0; j<num_xaxis; j++){
			cout << global[i][j] << " ";
		}
		cout<<endl;
	}
	return global_map;
}

void CCDP_map::getLocalmap(){

}
