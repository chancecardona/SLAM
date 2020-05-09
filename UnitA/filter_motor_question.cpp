#include "utility.h"
#include "LegoRobot.h"

const auto pi =  3.141592653589;

//TODO: Change vectors to ROS::Pose2D.
Pose2D filter_step(Pose2D old_pose, MotorTickRecord motor_tick, double ticks_to_mm,
        double robot_width){
    
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
       double center_x = old_x - (R + robot_width/2) * sin(old_theta);
       double center_y = old_y - (R + robot_width/2) * -1 *cos(old_theta);
       double new_theta = fmod((old_theta + alpha), (2*pi));
       double new_x = center_x - (R + robot_width/2) * sin(new_theta);
       double new_y = center_y - (R + robot_width/2) * -1 *cos(new_theta);
       return {new_x, new_y, new_theta};
    }

}

int main(){
    
    namespace plt = matplotlibcpp;

    const auto ticks_to_mm = 0.349;
    const auto robot_width = 150.0;

    LegoRobot l;
    l.read("../UnitA/robot4_motors.txt");
    auto motor_tick_diffs = l.getMotorTicks();

    vector<double> x_coords;
    vector<double> y_coords;
    Pose2D pose = {0.0, 0.0, 0.0};
    
    for (const auto& tick : motor_tick_diffs){
        pose = filter_step(pose, tick, ticks_to_mm, robot_width);
        x_coords.push_back(get<0>(pose));
        y_coords.push_back(get<1>(pose));
    }


    plt::plot(x_coords, y_coords, "bo");
    plt::show();
}
