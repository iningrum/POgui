# Base
A simple application for a simple meteorological station.

## MO
Upon first launch short program that sets up resolution and reads all sensors that are plugged in should be run.

Then preloader loads elements determined in CSV into corresponding CBases.

After that GUI is being run. Graphs should display readings automatically, command window allows for adding/removing sensors, switching between bases, displaying base stats, setting triggers for recording or starting/ending/simulating recording.

We def need multithreading but idk how for now.
## features

1. Determine resolution
2. Record - start/stop on trigger (time,value,etc)
3. Replay/Simulate recording
4. Multithreading with support for dynamic (de)allocation of sensors
5. It's supposed to run as a server so runtime support for hardware changes is required

## csv output

Assumed output for csv is:
	",".join([measure(s) for s in sensors])
First line is timestamp for each measurement

so exemplary file is:
```csv
time,21:00:20,21:00:40,21:01:00
temperature1,20,13,14,15
humidity2_460,14,56,45,76
```

Python script to convert into more excel-like will be provided