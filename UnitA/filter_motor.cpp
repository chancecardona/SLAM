#include "utility.h"
#include "LegoRobot.h"

const auto pi =  3.141592653589;

void print_pose(Pose2D, ostream&);
Pose2D filter_step(Pose2D, MotorTickRecord, double, double, double);

int main(){
    
    namespace plt = matplotlibcpp;

    const auto ticks_to_mm = 0.349;
    const auto robot_width = 173.0; //mm
    const auto scanner_displacement = 30.0; //mm

    LegoRobot l;
    l.read("../UnitA/robot4_motors.txt");
    auto motor_tick_diffs = l.getMotorTicks();

    vector<double> x_coords;
    vector<double> y_coords;
    Pose2D pose = {0.0, 0.0, 0.0};
    
    ofstream f;
    f.open("../UnitA/poses_from_ticks.txt");
    for (const auto& tick : motor_tick_diffs){
        pose = filter_step(pose, tick, ticks_to_mm, robot_width, scanner_displacement);
        print_pose(pose, f);
        x_coords.push_back(get<0>(pose));
        y_coords.push_back(get<1>(pose));
    }
    f.close();

    plt::plot(x_coords, y_coords, "bo");
    plt::show();
}

//Output is either cout or a file
void print_pose(Pose2D pose, ostream& output) {
    const auto [x, y, theta] = pose;
    output << "(" << x << "," << y << "," << theta << ")" << std::endl;
}

//Change vectors to ROS::Pose2D.
Pose2D filter_step(Pose2D old_pose, MotorTickRecord motor_tick, double ticks_to_mm,
        double robot_width, double scanner_displacement){
    //Uses Ackermann Transition Function from center of robot.
    //Also must keep track of scanner displacement from
    //robot center since measurements are from scanner, not center. 


    auto [left_tick, right_tick] = motor_tick;
    auto [old_x, old_y, old_theta] = old_pose;

    // No Turning
    if (left_tick == right_tick){
        double new_theta = old_theta;
        double new_x = old_x + (left_tick * ticks_to_mm) * cos(new_theta);
        double new_y = old_y + (left_tick * ticks_to_mm) * sin(new_theta);   
        return {new_x, new_y, new_theta};
    }
    // Turning
    else {
       double alpha = ticks_to_mm * (right_tick - left_tick) / robot_width;
       double R = ticks_to_mm * left_tick / alpha;
       //Get old_x in terms of center of robot
       old_x = old_x - scanner_displacement * cos(old_theta);
       old_y = old_y - scanner_displacement * sin(old_theta);
       double center_x = old_x - (R + robot_width/2) * sin(old_theta);
       double center_y = old_y - (R + robot_width/2) * -1 *cos(old_theta);
       double new_theta = fmod((old_theta + alpha), (2*pi));
       double new_x = center_x + (R + robot_width/2) * sin(new_theta);
       double new_y = center_y + (R + robot_width/2) * -1 *cos(new_theta);
       //Get new_x back in terms of sensor
       new_x = new_x + scanner_displacement * cos(new_theta);
       new_y = new_y + scanner_displacement * sin(new_theta);
       return {new_x, new_y, new_theta};
    }

}
