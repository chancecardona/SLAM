## Dr. Brenner's SLAM Lectures Implemented in Modern Python. ##
Code heavily inspired and using code from https://github.com/patrick--/SLAM-Exploration/blob/master/
### Installation and Setup ###
<ul>
    <li> git clone --recursive https://github.com/chancecardona/SLAM.git </li>
    <li> cd SLAM/ </li>
    <li> mkdir build </li>
    <li> cd build/ </li>
    <li> cmake .. </li>
    <li> make </li>
    <li> ./UnitA/plot_motor_ticks (or whatever one you want) </li>
</ul>

### Installation Troubleshooting ###
If "file not found", be wary of where you're running the code from! This is only tested running code from "build" currently.  
If there are errors with numpy/arrayobject.h first make sure python3, python3-numpy, and python3-matplotlib are installed on your system.  
If there are errors with matplotlib module not found, you don't have matplotlib installed or it's set to the wrong path. Make sure your system's default is python 3! If it's 2, an easier fix may be to change the CMakeLists.txt file in utils/ to use python2.  

### Unit A ###
<ul>
    <li> plot_motor_ticks.cpp Plots raw motor encoder data </li>
    <li> filter_motor_question.cpp Plots the robot movements in 2D using the motor sensor data and Ackermann motor equations. </li>
</ul>
