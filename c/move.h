#ifndef ROVERCORE_MOVE_H
#define ROVERCORE_MOVE_H


#define WHEEL_DIAMETER 124     /* mm diameter of the wheel*/

/*this is for the 6 wheel motors*/
#define TICKS_PER_REV_6 40                /*ticks per revolution*/
#define GEAR_RATIO 116

/*this is for the 4 rotating motors*/
#define TICKS_PER_REV_4 40                /*ticks per revolution*/
#define GEAR_RATIO 172

//6 wheel motors 116 gear ratio  numbers abover 
// 4 motors for corners 40 ticks per rev, gear ratio 172:1 but for turning this is angular. 
//these four motors will take an angle in degrees with 1 decimal point in range( +- 90). 
//research how to go from degrees to ticks 20degrees/172*40ticks




//give a distance comand in mm in range(1, 1024) no fraction 
int distance_to_ticks(int distance);

float degrees_to_ticks(float degrees);


long get_distance(long ticks);
int get_velocity();
//uint16_t ticks_to_distance();
// uint16_t calc_circumference();





#endif //ROVERCORE_MOVE_H