# Indian Road Traffic Simulator

This is the basic traffic simulator, describing the motion of variables on Indian Roads. The simulator is written in C++ and is powered by OpenGL.

## Installation

Use the run_simulator.sh file to run the simulator.

```bash
bash run_simulator.sh
```

## Configuration File
The config.ini file contains the description of vehicles we are using in the simulator and also the description of the traffic.
The description of config.ini is:


1) Defining Road Parameters
```
# Comment starts with #
Road_Id = 1			# Unique Id for the simulation 
Road_Length = 30
Road_Width = 5
Road_Signal = 15
```

2) Define default params for all vehicle types
```
Default_MaxSpeed = 1 		# Max Speed per second
Default_Acceleration = 1	# Increase in speed per second
```

3) Define params for specific vehicle types
```
Vehicle_Type = Car		# A new vehicle class will start with a type field
Vehicle_Length = 2
Vehicle_Width = 2
Vehicle_MaxSpeed = 1
Vehicle_Acceleration = 1

Vehicle_Type = bike		# The first character will be used as the symbol for printing
Vehicle_Length = 2
Vehicle_Width = 1

Vehicle_Type = Bus
Vehicle_Length = 3
Vehicle_Width = 2

Vehicle_Type = Truck
Vehicle_Length = 4
Vehicle_Width = 2

# Definitions over
```

4) Start the simulation
```
START
Signal RED			# Make the signal RED

```
Send vehicles with given types on the road (one per second)

```
Car GREEN
bike BLUE
bike GREEN
Bus BLUE

Pass 15				# Let the simulation keep running for 15 seconds
```
Now below vehicles enter the road
```
Car GREEN
bike BLUE
Truck GREEN
Bus BLUE

Turn the signal green
Signal GREEN
```
Ending Simulation
```
END			# If signal is GREEN, end should wait till road is clear

```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

Main Authors - Prateek Garg, Rushil Gupta

## License
[MIT](https://choosealicense.com/licenses/mit/)