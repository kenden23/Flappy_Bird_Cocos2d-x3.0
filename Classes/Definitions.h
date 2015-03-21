#ifndef _DEFINITION_H_
#define _DEFINITION_H_

#define DISPLAY_TIME_SPLASH_SCENE 1
#define TRANSITION_TIME 0.3
#define PIPE_SPAWN_FREQUENCY 0.005
#define PIPE_GAP 3.8
#define UPPER_SCREEN_PIPE_THRESHOLD 0.85
#define LOWER_SCREEN_PIPE_THRESHOLD 0.35

#define PIPE_MOVEMENT_SPEED 0.01
#define BIRD_COLLISION_BITMASK 0x000001
#define OBSTACLE_COLLISION_BITMASK 0x000002
#define POINT_COLLISION_BITMASK 0x000003

#define BIRD_FALLING_SPEED 0.0045
#define BIRD_FLYING_SPEED 0.00375
#define BIRD_FLY_DURATION 0.2

#define SCORE_FONT_SIZE 0.1

#define HIGHEST_SCORE_FILE "HIGHEST_SCORE_FILE"

#define CENTER_POSITION_OF_GAME_SCREEN visibleSize.width/2.0f+origin.x, visibleSize.height/2.0f+origin.y

namespace MyUtils
{

template<typename T1, typename T2>
inline bool equ(T1 a, T2 b) { return (T1)a == (T1)b; }



}

#endif	//_DEFINITION_H_