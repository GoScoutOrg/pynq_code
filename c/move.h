#ifndef ROVERCORE_MOVE_H
#define ROVERCORE_MOVE_H


#define WHEEL_DIAMETER 5        /* inches diameter of the wheel*/
#define TICKSPERREV 96                /*ticks per revolution*/
#define GEAR_RATIO 170


long get_distance(long ticks);
int get_velocity();
uint16_t ticks_to_distance();
// uint16_t calc_circumference();





#endif //ROVERCORE_MOVE_H