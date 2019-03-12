#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class vehicle{
	public:
		string id;
		int lane;
		int length;
		int breadth;
		int position;
		vehicle(int lane, int length, int breadth, string id){
			this->id = id;
			this->lane = lane;
			this->length = length;
			this->breadth = breadth;
			this->position = 0;
		}
		void move_forward(){
			position++;
		}
};

void printroad(string road[7][30], int time, vector<vehicle> traffic){
	int i,j;
	int x,y;
	int num_vehicles = traffic.size();
	string empty_string = " ";
	int lane, position;
	for(i=0;i<num_vehicles;i++){
		vehicle temp = traffic.at(i);
		lane = temp.lane;
		position = temp.position;
		if(lane<6 && position <30){
			if(road[lane][position].compare(empty_string) == 0){
				for(x=0;x<temp.length;x++){
					for(y=0;y<temp.breadth;y++){
						if(position-x>0){
							road[lane+y][position-x] = temp.id;	
						}
					}
				}

			}
		}
	}
	

	for(i=0;i<7;i++){
		for(j=0;j<30;j++){
			cout<<road[i][j];
		}
		cout<<endl;
	}
	cout<<"Time:"<<time<<endl;
}



vector<vehicle> traffic_move_forward(vector<vehicle> traffic, string road[7][30], int* time){
	int num_vehicles = traffic.size();	
	int i,j,k;
	int y,position;
	string empty_string = " ";
	bool front_clear = true;
	for(i=0;i<num_vehicles;i++){
		front_clear = true;
		vehicle temp = traffic.at(i);
		position = temp.position;
		y = temp.lane;


		for(j=0;j<temp.breadth;j++){
				if(y+j<6 && (position+1<30)){
				char q = road[y+j][position+1].at(0);
				if(road[y+j][position+1].compare(empty_string) != 0){
					front_clear = false;
				}
			}
		}



		if(front_clear){
			for(j=0; j<temp.breadth && position >= 1;j++){
				road[y+j][position-1] = " ";
			}
			traffic.at(i).move_forward();
		}
	}
	*time = *time + 1;
	return traffic;
}

void traffic_light(string road[7][30], bool status){
	int i,j;
	if(status){
		for(i=1;i<6;i++){
			road[i][15] = "|";
		}
	}
	if(!status){
		for(i=1;i<6;i++){
			road[i][15] = " ";
		}	
	}
}


int main(){
	int i, j;
	string road[7][30];
	int time = 0;
	vector<vehicle> traffic;
	for(i=0;i<7;i++){
		for(j=0;j<30;j++){
			road[i][j] = " ";
		}
	}
	for(i=0;i<30;i++){
		road[0][i] = "-";
		road[6][i] = "-";
	}

	int new_lane = rand()%4 +1;
	vehicle car1(new_lane,2,2,"c");
	traffic.push_back(car1);
	cout<<traffic.at(0).position<<"888"<<endl;
	
	traffic_light(road,true);

	traffic = traffic_move_forward(traffic, road,&time);
	printroad(road,time,traffic);
	
	traffic = traffic_move_forward(traffic, road,&time);
	printroad(road,time,traffic);
	
	new_lane = rand()%4 +1;
	vehicle car2(new_lane,2,2,"a");
	traffic.push_back(car2);

	while(time < 60){
		traffic = traffic_move_forward(traffic, road,&time);
		printroad(road, time, traffic);
		if(time == 32){
			traffic_light(road,false);
		}
	// printroad(road, time, traffic);
	}

}