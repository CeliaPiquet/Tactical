#include "../Headers/editor.h"

//void loadSound(){
//    //creation of the system object
//    FMOD_SYSTEM *system;
//    FMOD_System_Create(&system);
//    FMOD_System_Init(system, 2, FMOD_INIT_NORMAL, NULL); //2 = maximal number of sounds that can be played at the same time
//
//    //creation of the sound
//    FMOD_SOUND *click = NULL;
//    FMOD_System_CreateSound(system, "../sounds/smrpg_click.wav", FMOD_CREATESAMPLE, 0, &click); //the third parameter is a pointer to a FMOD_CREATESOUNDEXINFO which lets the user provide extended information while playing the sound
//
//    //play the sound
//    // the function take first the system object, then the channel where we wanna play the sound
//    FMOD_System_PlaySound(system, click,0, NULL, 1);
//
//
//    //free the system object and the sound
//    FMOD_Sound_Release(click);
//    FMOD_System_Close(system);
//    FMOD_System_Release(system);
//}


