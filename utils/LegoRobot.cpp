//TODO: Implement all cases. Note: probably need to change from appending 
//a tuple to rather appending a vector of ints since size is uncertain. 
//Make a new 2 int tuple of X Y coords.

#include <fstream>
#include <iostream>

#include "LegoRobot.h"
//#include "string_utility.h";

// Initialization list for constructor
LegoRobot::LegoRobot() : motor_ticks_raw_(), motor_ticks_() {}

void LegoRobot::read(const string &file) {

  std::ifstream input(file);

  if (!input.is_open()) {
    exit(1);
  }

  string line;
  auto prev_values = tuple<int, int>();

  while (getline(input, line)) {

    auto message_type = line[0];
    auto raw_sensor_fields = utility::string_split(line, ' ');

    switch (message_type) {

    //case 'P': //Reference positions
    //    reference_positions_.push_back( 
    //        tuple(std::stoi(raw_sensor_fields[2]), std::stoi(raw_sensor_fields[3])) );
    //    break;

    //case 'S': //Scan data
    //    //s_record_has_count ??
    //    int temp[raw_sensor_fields.size()];
    //    for (int i = 2; i < raw_sensor_fields.size(), i++){
    //        temp[i-2] = std::stoi(raw_sensor_fields[i]);
    //    }
    //    scan_data_.push_back(tuple(temp))
    //    break;

    //case 'I':
    //    int temp[raw_sensor_fields.size()];
    //    for (int i = 2; i < raw_sensor_fields.size(), i++){
    //        temp[i-2] = std::stoi(raw_sensor_fields[i]);
    //    }
    //    pole_indices_.push_back(tuple(temp))
    //    break;

    case 'M': //Motor ticks
        auto lmotor_curr = std::stoi(raw_sensor_fields[2]);
        auto rmotor_curr = std::stoi(raw_sensor_fields[6]);
        // We store diff rather than absolute value, so first pass diffs on self
        if (motor_ticks_.size() == 0) {
            prev_values = tuple(lmotor_curr, rmotor_curr);
        }

        auto [lmotor_prev, rmotor_prev] = prev_values;
        motor_ticks_.push_back(
              tuple(lmotor_curr - lmotor_prev, rmotor_curr - rmotor_prev));
        prev_values = std::tuple(lmotor_curr, rmotor_curr);
        break;
    
    //case 'F': //Filtered trajectory
    //    int temp[raw_sensor_fields.size()];
    //    for (int i = 1; i < raw_sensor_fields.size(), i++){
    //        temp[i-1] = std::stoi(raw_sensor_fields[i]);
    //    }
    //    filtered_positions_.push_back(tuple(temp));
    //    break;

    //case 'L': //Landmark
    //    if (raw_sensor_fields[1] == 'C'){
    //        int temp[raw_sensor_fields.size()+1];
    //        temp[0] = 'C';
    //        for (int i = 2; i < raw_sensor_fields.size(), i++){
    //            temp[i-1] = std::stoi(raw_sensor_fields[i]);
    //        }
    //        landmarks_.push_back(tuple(temp));
    //    break;

    //case 'D': //Detected Landmark
    //    if (raw_sensor_fields[1] == 'C'){
    //        float cyl[raw_sensor_fields.size()];
    //        for (int i = 2; i < raw_sensor_fields.size(), i++){
    //            cyl[i-2] = std::stof(raw_sensor_fields[i]);
    //        }
    //        for (int i = 0; i < cyl.size()/2; i++){
    //            landmarks_.push_back(tuple(cyl[2*i], cyl[2*i+1]));
    //        }
    //    break;

    }
  }
}

vector<MotorTickRecord> LegoRobot::getMotorTicks() const {
  return motor_ticks_;
}
