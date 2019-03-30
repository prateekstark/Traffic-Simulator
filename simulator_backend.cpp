#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include<fstream>
#include<bits/stdc++.h>
#include <ctype.h>



using namespace std;

int timex = 0;
int* t = &timex;
int my_default_maxspeed = 5;
int* mdmax = &my_default_maxspeed;
int my_default_acc = 1;
int *mdacc = &my_default_acc;
int my_default_length = 2;
int* mdlen = &my_default_length;
int my_default_width = 1;
int* mdwid = &my_default_width;
int my_road_length = 30;
int* mrlen = &my_road_length;
int my_road_width = 7;
int* mrwid = &my_road_width;
int my_signal_position = 15;
int* mspos = &my_signal_position;
int my_road_id = 1;
int* mrid = &my_road_id;
bool traffic_light_status = true;
class vehicle {

public:
	string id;
	string name;
	int lane;
	string color;
	int length = my_default_length;
	int breadth = my_default_width;
	int position;
	int speed;
	int acceleration = my_default_acc;
	int maxspeed = my_default_maxspeed;
	vehicle(int lane, int length, int breadth, string id, int speed, int acc, int max) {
		this->id = id;
		this->lane = lane;
		this->length = length;
		this->breadth = breadth;
		this->position = -1;
		this->speed = speed;
		this->acceleration = acc;
		this->maxspeed = max;
	}
	vehicle(){

	}

	void move_forward() {
		position += this->speed;
	}
	vehicle(string name){
		this->id = name.at(0);
	}

};

void update(vehicle* curr_veh, string** road){
	vehicle temp = *curr_veh;
		int lane = temp.lane;
		int position = temp.position;
		if (lane < 6 && position < 30 && position >= 0) {
			if (road[lane][position].compare(" ") == 0) {
				for (int x = 0; x < temp.length; x++) {
					for (int y = 0; y < temp.breadth; y++) {
						if (position - x > 0) {
							road[lane + y][position - x] = temp.id;
						}
					}
				}

			}
		}
}


string getString(char x){ 
    string s(1, x);  
    return s;    
} 


string removeComments(string line){
	string tempString = "";
	string::iterator it;
	for(it=line.begin();it!=line.end();it++){
		if(*it != '#'){
			tempString = tempString + getString(*it);
		}
		else{
			break;
		}
	}
	return tempString;
}

string removeSpaces(string str){ 
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    str.erase(remove(str.begin(), str.end(), '\t'), str.end()); 
    return str;
} 

void printroad(string** road, int time, vector<vehicle> traffic) {
	int i, j;
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 30; j++) {
			cout << road[i][j];
		}
		cout << endl;
	}
	cout << "Time:" << time << endl;
}

bool isRightClear(string** road, int lane, int position, int speed) {
	bool ans = true;
	int i;
	for (i = 0; i <= speed; i++) {
		if (position < 15) {
			if (position + i < 15) {
				if ((road[lane +2][position + i].compare(" ") != 0))
					ans = false;
				if (position >= 1) {
					if ((road[lane+2][position - 1 + i].compare(" ") != 0))
						ans = false;
				}
			}
			else
				ans = true;
		}
		else
		{
			if (position + i < 15) {
				if ((road[lane +2][position + i].compare(" ") != 0))
					ans = false;
				if (position >= 1) {
					if ((road[lane +2][position - 1 + i].compare(" ") != 0))
						ans = false;
				}
			}
		}
	}
	return ans;
}

bool isLeftClear(string** road, int lane, int position, int speed) {
	bool ans = true;
	int i;
	for (i = 0; i <= speed; i++) {
		if (position < 15) {
			if (position + i < 15) {
				if ((road[lane - 1][position + i].compare(" ") != 0))
					ans = false;
				if (position >= 1) {
					if ((road[lane - 1][position - 1 + i].compare(" ") != 0))
						ans = false;
				}
			}
			else
				ans = true;
		}
		else
		{
			if (position + i < 15) {
				if ((road[lane - 1][position + i].compare(" ") != 0))
					ans = false;
				if (position >= 1) {
					if ((road[lane - 1][position - 1 + i].compare(" ") != 0))
						ans = false;
				}
			}
		}
	}
	return ans;
}

void shiftCar(string** road, int lane, int position, string id, bool overtake_correct) {
	if (overtake_correct) {
		road[lane][position] = " ";
		road[lane][position - 1] = " ";
		road[lane + 2][position] = id;
		road[lane + 2][position - 1] = id;
	}
	else
	{
		road[lane + 1][position] = " ";
		road[lane + 1][position - 1] = " ";
		road[lane - 1][position] = id;
		road[lane - 1][position - 1] = id;
	}
}

bool checkClear(string** road, int lane, int position, int breadth, int speed) {
	int j, k;
	for (j = 0; j < breadth; j++) {
		if (lane + j < 6) {
			for (k = 1; k <= speed; k++) {
				if (position < 15) {
					if (position + k < 15) {
						//if(timex ==15 || timex==16) cout << "Gauri machaxx " << position << " " << lane << " " << road[lane+j][position+k] << position + k << " " << endl;
						if (road[lane + j][position + k].compare(" ") != 0) {
							return false;
						}
					}
					else {
						// if (timex == 15 || timex == 16) cout << "phutgaye" << endl;
						return true;
					}
				}
				else
				{
					if (position + k < 30) {
						if (road[lane + j][position + k].compare(" ") != 0) {
							return false;
						}
					}
				}

			}
		}
	}
	return true;
}

void traffic_move_forward(vehicle* traffic, string** road, int* time) {
	int i, j, k;
	string empty_string = " ";
	int position = (*traffic).position;
	int y = (*traffic).lane;
	int breadth = (*traffic).breadth;
	int speed = (*traffic).speed;
	//cout << road[y][14] << "polish" << " " << (*traffic).id << " " << y << endl;
	bool front_clear = checkClear(road, y, position, breadth, speed);
	if (front_clear) {
		//cout << "Rishi" << endl;
		for (j = 0; j < (*traffic).breadth; j++) {
			if (position >= 1 && y <= 4 && position <= 30) {
				for (k = 0; k < (*traffic).length; k++) {
					if (position - k >= 0)
						road[y + j][position - k] = " ";
				}
			}
		}
		if (timex < 32) {
			if (position < 15) {
				if (position + speed < 15)
					(*traffic).move_forward();
				else
					(*traffic).position = 14;
			}
			else
				(*traffic).move_forward();
		}
		else
			(*traffic).move_forward();
	}
	else
	{
		if (position == 12) {
			if (y <= 3 && isRightClear(road, y, position, speed) && isRightClear(road, y, position+1, speed)) {
				(*traffic).lane += 1;
				shiftCar(road, y, position, (*traffic).id, true);
				y += 1;
				if (checkClear(road, y, position, breadth, speed)) {
					for (j = 0; j < (*traffic).breadth; j++) {
						if (position >= 1 && y <= 4 && position <= 30) {
							for (k = 0; k < (*traffic).length; k++) {
								if (position - k >= 0)
									road[y + j][position - k] = " ";
							}
						}
					}
					if (timex < 32) {
						if (position < 15) {
							if (position + speed < 15)
								(*traffic).move_forward();
							else
								(*traffic).position = 14;
						}
						else
							(*traffic).move_forward();
					}
					else
						(*traffic).move_forward();
				}
			}
			else {
				if (y >= 2 && isLeftClear(road, y, position, speed) && isLeftClear(road, y, position + 1, speed)) {
					(*traffic).lane -= 1;
					shiftCar(road, y, position, (*traffic).id, false);
					y -= 1;
					if (checkClear(road, y, position, breadth, speed)) {
						for (j = 0; j < (*traffic).breadth; j++) {
							if (position >= 1 && y <= 4 && position <= 30) {
								for (k = 0; k < (*traffic).length; k++) {
									if (position - k >= 0)
										road[y + j][position - k] = " ";
								}
							}
						}
						if (timex < 32) {
							if (position < 15) {
								if (position + speed < 15)
									(*traffic).move_forward();
								else
									(*traffic).position = 14;
							}
							else
								(*traffic).move_forward();
						}
						else
							(*traffic).move_forward();

					}
				}
			}
		}
		else
		{
			if (y <= 3 && isRightClear(road, y, position, speed) && position != 14 && position <= 29 && isRightClear(road, y, position + 1, speed)) {

				(*traffic).lane += 1;
				shiftCar(road, y, position, (*traffic).id, true);
				y += 1;
				if (checkClear(road, y, position, breadth, speed)) {
					for (j = 0; j < (*traffic).breadth; j++) {
						if (position >= 1 && y <= 4 && position <= 30) {
							for (k = 0; k < (*traffic).length; k++) {
								if (position - k >= 0)
									road[y + j][position - k] = " ";
							}
						}
					}
					if (timex < 32) {
						if (position < 15) {
							if (position + speed < 15)
								(*traffic).move_forward();
							else
								(*traffic).position = 14;
						}
						else
							(*traffic).move_forward();
					}
					else
						(*traffic).move_forward();
				}
			}
			else {
				if (y >= 2 && isLeftClear(road, y, position, speed) && position != 14 && position <= 29 && isRightClear(road, y, position + 1, speed)) {

					(*traffic).lane -= 1;
					shiftCar(road, y, position, (*traffic).id, false);
					y -= 1;
					if (checkClear(road, y, position, breadth, speed)) {
						for (j = 0; j < (*traffic).breadth; j++) {
							if (position >= 1 && y <= 4 && position <= 30) {
								for (k = 0; k < (*traffic).length; k++) {
									if (position - k >= 0)
										road[y + j][position - k] = " ";
								}
							}
						}
						if (timex < 32) {
							if (position < 15) {
								if (position + speed < 15)
									(*traffic).move_forward();
								else
									(*traffic).position = 14;
							}
							else
								(*traffic).move_forward();
						}
						else
							(*traffic).move_forward();

					}
				}
			}
		}
	}
	if ((*traffic).speed + (*traffic).acceleration <= (*traffic).maxspeed)
		(*traffic).speed += (*traffic).acceleration;
	else
		(*traffic).speed = (*traffic).maxspeed;
	//cout << traffic.at(i).speed << "huahua" << endl;
	*time = *time + 1;
	update(traffic,road);
	//return road;
}

void traffic_light(string** road, bool status) {
	int i, j;
	if (status) {
		for (i = 1; i < 6; i++) {
			road[i][15] = "|";
		}
	}
	else {
		for (i = 1; i < 6; i++) {
			road[i][15] = " ";
		}
	}
}



int main() {
	int i, j, z;
	string** road;
	vector<vector<vehicle> > pos_print;
	int new_lane = rand() % 4 + 1;
	road = new string*[7];	
	for (z = 0; z < 7; z++) {
		road[z] = new string[30];
	}
	vector<vehicle> traffic;
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 30; j++) {
			road[i][j] = " ";
		}
	}
	for (i = 0; i < 30; i++) {
		road[0][i] = "-";
		road[6][i] = "-";
	}
/*--------------------------------------------------------------------------------------*/
	string line, tempString;
	vector<vehicle> core_traffic;
	int num_temp_time;
	// int i,j;
	size_t found, found1, found2, found3, found4;
	int lane_id, road_length, road_width, num_traffic, index, index1;
	int road_signal, default_speed, default_acc;
	string vehicle_name, vehicle_identity;
	int vehicle_acc, vehicle_maxspeed, vehicle_length, vehicle_width;
	vector<vehicle>::iterator it, it1;
	vehicle* temp = new vehicle();
	ifstream configFile("config.ini");
	if(configFile.is_open()){
		while(getline(configFile,line)){

			line = removeComments(line);
			if(line.empty()){
				continue;
			}
			// cout<<line<<endl;

			found = line.find("Road_Id");
			if(found != string::npos){
				index = line.find("=");
				tempString = line.substr(index+2);
				my_road_id = atoi(tempString.c_str());

				continue;
			}

			found = line.find("Road_Length");
			if(found != string::npos){
				index = line.find("=");
				tempString = line.substr(index+2);
				my_road_length = atoi(tempString.c_str());
				
				continue;
			}

			found = line.find("Road_Width");
			if(found != string::npos){
				index = line.find("=");
				tempString = line.substr(index+2);
				my_road_width = atoi(tempString.c_str());
				
				continue;
			}

			found = line.find("Road_Signal");
			if(found != string::npos){
				index = line.find("=");
				tempString = line.substr(index+2);
				// cout<<tempString<<endl;
				my_signal_position = atoi(tempString.c_str());
				// for(i = 0; i < 7; i++){
				// 	for (j = 0; j < 30; j++) {
				// 		road[i][j] = " ";
				// 	}
				// }
				// for(i = 0; i < 30; i++){
				// 	road[0][i] = "-";
				// 	road[6][i] = "-";
				// }
				continue;
			}


			found = line.find("Default_MaxSpeed");
			if(found != string::npos){
				index = line.find("=");
				tempString = line.substr(index+2);
				my_default_maxspeed = atoi(tempString.c_str());

				continue;
			}

			found = line.find("Default_Acceleration");
			if(found != string::npos){
				index = line.find("=");
				tempString = line.substr(index+2);
				// cout<<tempString<<endl;

				my_default_acc = atoi(tempString.c_str());
				
				continue;
			}


			found = line.find("Vehicle_Type");
			if(found != string::npos){
				// cout<<line<<endl;
				vehicle* temp_vehicle = new vehicle();
				index = line.find("=");
				tempString = line.substr(index+2);
				tempString = removeSpaces(tempString);
				// tempString = tempString.erase(remove(tempString.begin(), tempString.end(), ' '), tempString.end());
				// cout<<tempString<<"maangna"<<endl;
				temp_vehicle->name = tempString;
				core_traffic.push_back(*temp_vehicle);
				continue;
			}
			

			found = line.find("Vehicle_Length");
			if(found != string::npos){
				index = line.find("=");
				tempString = line.substr(index+2);
				vehicle_length = atoi(tempString.c_str());
				num_traffic = core_traffic.size();
				// cout<<"num_traffic"<<core_traffic.size()<<endl;
				core_traffic.at(num_traffic-1).length = vehicle_length;
				continue;
			}

			found = line.find("Vehicle_Width");
			if(found != string::npos){
				index = line.find("=");
				tempString = line.substr(index+2);
				vehicle_width = atoi(tempString.c_str());
				num_traffic = core_traffic.size();
				core_traffic[num_traffic - 1].breadth = vehicle_width;
				continue;
			}
			

			found = line.find("Vehicle_MaxSpeed");
			if(found != string::npos){
				index = line.find("=");
				tempString = line.substr(index+2);
				vehicle_maxspeed = atoi(tempString.c_str());
				num_traffic = core_traffic.size();
				core_traffic[num_traffic - 1].maxspeed = vehicle_maxspeed;
				continue;
			}


			found = line.find("Vehicle_Acceleration");
			if(found != string::npos){
				index = line.find("=");
				tempString = line.substr(index+2);
				// cout<<tempString<<endl;
				vehicle_acc = atoi(tempString.c_str());
				num_traffic = core_traffic.size();
				// cout<<num_traffic-1;
				core_traffic[num_traffic - 1].acceleration = vehicle_acc;
				continue;
			}
			// cout<<line;
			// return 0;
			found = line.find("START");
			if(found != string::npos){
				continue;
			}

			// return 0;


			found = line.find("Signal");
			if(found != string::npos){
				index = line.find(" ");
				tempString = line.substr(index+1);
				// cout<<tempString<<endl;
				if(tempString.compare("GREEN")){
					traffic_light(road,false);
				}
				if(tempString.compare("RED")){
					traffic_light(road,true);
				}
				continue;
			}

			// for(int v = 0;v<core_traffic.size();v++){
			// 		cout<<core_traffic.at(v).name<<endl;
			// }


			for(int f = 0;f<core_traffic.size(); f++){
				vehicle *iter_vehicle;
				*iter_vehicle = core_traffic.at(f);
				found = line.find(iter_vehicle->name);
				if(found != string::npos){
					index = line.find(" ");
					// cout<<line<<endl;
					tempString = line.substr(index+1);
					// cout<<tempString<<endl;
					tempString = removeSpaces(tempString);
					iter_vehicle->color = tempString;
					// cout<<iter_vehicle->name<<"bhosda"<<endl;
					// cout<<iter_vehicle->length<<"bhosda"<<endl;
					// cout<<iter_vehicle->breadth<<"bhosda"<<endl;
					// cout<<iter_vehicle->maxspeed<<"bhosda"<<endl;

					traffic.push_back(*iter_vehicle);
					cout<<traffic.size()<<endl;

					// if(traffic.size() >0){
					// 	cout<<"maa ki chot";
					// 	cout<<traffic.at(1).name;
					// }
					
					for(int p=0;p<traffic.size();p++){
						traffic_move_forward(&traffic.at(p),road,t);
					}
					break;
				}
			}
			// for(int v = 0; v<traffic.size();v++){
			// 	cout<<traffic.at(v).name<<endl;
			// }



			found = line.find("Pass");
			if(found != string::npos){
				index = line.find(" ");
				tempString = line.substr(index+2);
				int p1 = atoi(tempString.c_str());
				for(int p2=0;p2<p1;p2++){
					for (int p = 0; p < traffic.size(); p++) {
						traffic_move_forward(&traffic.at(p), road, t);	
					}
					// printroad(road,timex,traffic);
				}
				continue;
			}


			found = line.find("END");
			if(found != string::npos){
				break;
			}

			// cout<<line<<endl;
		}
		// return 0;
		configFile.close();

	}
	else{
		cerr<<"Unable to open file"<<endl;
	}

	// for(i=0;i<core_traffic.size();i++){
	// 	cout<<"hello";
	// 	cout<<core_traffic.at(i).id<<endl;
	// }





	// vehicle car1(new_lane, 2, 2, "c", 0, 1, 5);
	// traffic.push_back(car1);

	// int x, y;
	// traffic_light(road, true);
	// for (int p = 0; p < traffic.size(); p++) {
	// 	traffic_move_forward(&traffic.at(p), road, t);	
	// }
	// printroad(road, timex, traffic);
	//int i, j;
	// for(int p = 0; p < traffic.size(); p++){
		// traffic_move_forward(&traffic.at(p), road, t);
		// update(&traffic.at(p),road);
	// }
	// printroad(road, timex, traffic);

	// vehicle car2(new_lane, 2, 2, "a", 0, 1, 3);
	// traffic.push_back(car2);

	// while (timex < 60) {
		// for (int p = 0; p < traffic.size(); p++) {
		// 	traffic_move_forward(&traffic.at(p), road, t);
		// 	// update(&traffic.at(p),road);
		// }
		// printroad(road, timex, traffic);

		// vector<vehicle> data;
		// for (i = 0; i < traffic.size(); i++) {
		// 	data.push_back(traffic.at(i));
		// }
		// pos_print.push_back(data);
		// if (timex == 32) {
		// 	traffic_light(road, false);
		// }

	// }

}