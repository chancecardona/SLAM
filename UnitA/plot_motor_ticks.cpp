#include <fstream>
#include "utility.h"

using namespace std;

int main(){
    namespace plt = matplotlibcpp;

    //open motor file
    ifstream motor_file;
    motor_file.open("../UnitA/robot4_motors.txt");
    if(!motor_file.is_open()){
        cout << "Unable to open file." << endl;
        return 1;
    }
    
    vector<int> left_motor_ticks;
    vector<int> right_motor_ticks;
    string line;
    while(getline(motor_file, line)){
        auto raw_fields = utility::string_split(line, ' ');
        left_motor_ticks.push_back(stoi(raw_fields[2]));
        right_motor_ticks.push_back(stoi(raw_fields[6]));
    }
    
    plt::plot(left_motor_ticks);
    plt::plot(right_motor_ticks);
    plt::title("Absolute Motor Ticks");
    plt::show();

    return 0;
}
