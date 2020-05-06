#include <fstream>
#include "utility.h"

using namespace std;

int main(){
    namespace plt = matplotlibcpp;

    //open motor file
    ifstream motors_file;
    motors_file.open("robot4_motors.txt");
    if(!motors_file.is_open()){
        cout << "Unable to open file." << endl;
        return;
    }
    
    vector<int> left_motor_ticks;
    vector<int> right_motor_ticks;
    string line;
    while(getline(motors_file, line)){
        auto raw_fields = utility::string_split(line, ' ');
        left_motor_ticks.push_back(stoi(raw_fields[2]));
        right_motor_ticks.push_back(stoi(raw_fields[6]));
    }
    motors_file.close();
    
    plt::plot(left_motor_ticks);
    plt::plot(right_motor_ticks);
    plt::title("Absolute Motor Ticks");
    plt::show();

    return 0;
}
