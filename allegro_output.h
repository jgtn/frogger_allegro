/***************************************************************************//**
  @file     allegro_output
  @brief    m
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

#ifndef ALLEGRO_OUTPUT
#define ALLEGRO_OUTPUT

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "eventQueue.h"
#include "gameStructs.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define DWIDTH  480
#define DHEIGHT 600
#define NOFCARS 10
#define BLACK (al_map_rgb(0,0,0))
#define WHITE (al_map_rgb(255,255,255))
#define FPS 60
#define CARS_TIMER 1
#define NOFLANES 15

/********* COORDINATES CONSTANTS ***********/

#define START_PLAY_X // coordenadas de los strings para colocar el arroe pointer
#define START_PLAY_Y
#define START_SCOREBOARD_X
#define START_SCOREBOARD_Y
#define START_QUIT_X
#define START_QUIT_Y
#define PAUSE_RESTART_ID_X
#define PAUSE_RESTART_ID_Y
#define PAUSE_RESUME_ID_X
#define PAUSE_RESUME_ID_Y

#define FROGSTEP_X
#define FROGSTEP_Y

#define INIT_X                // donde arranca la rana
#define INIT_Y
#define FROG_X_MAX  (DWIDTH-1)    // borders
#define FROG_X_MIN  0
#define FROG_Y_MAX  (DHEIGHT-1)
#define FROG_Y_MIN  0

#define START_LANE_Y           // lane inferior
#define LANE1_Y
#define LANE2_Y
#define LANE3_Y
#define LANE4_Y
#define LANE5_Y
#define LANE6_Y
#define BUFFER_LANE_Y           // lane central
#define LANE7_Y
#define LANE8_Y
#define LANE9_Y
#define LANE10_Y
#define LANE11_Y
#define LANE12_Y
#define END_LANE_Y              // lane superior

#define LIVES_Y
#define LIVE1_X
#define LIVE2_X
#define LIVE3_X
#define LIVE4_X
#define LIVE5_X




/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct car  //  estructura que contiene datos de los bitmaps asociados a los autos/troncos que se mueven
{
  uint8_t x_pos; // coordenadas al CENTRO del carril ( y del bitmap)
  uint8_t lane;   // número de carril
  uint8_t x_size; // largo del bitmap, para analizar colisiones
  uint8_t type
} al_car_t;

typedef struct frog
{
  uint8_t x_pos;
  uint8_t lane;
  uint8_t orientation;
  uint8_t x_size;
  uint8_t y_size;
}al_frog_t;

typedef struct lane
{
  uint8_t number;
  uint8_t divider;
  uint8_t dividerMax;
  bool way;
}al_lane_t;



enum orientation {LEFT,RIGHT,UP,DOWN};    // enum de direcciones hacia las que se puede mover la rana
enum carType {CAR1,CAR2,TRUCK,WOOD};    // enum  de los tipos de bitmap auto

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
void *output_thread(void* pointer);
int checkBitmapcollision(void *Cpointer, void *Fpointer, int NofCars);
void carsRoutine(void *Cpointer, void *Fpointer, void *Lpointer, int NofCars);
void moveCars(void *Cpointer, void *Fpointer,int way, int NofCars, int lane);
int getLaneWay(void *Cpointer, int lane, int NofCars);
void moveFrog(uint8_t where,frog_t *frogCoords);

/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve

// +ej: char lcd_goto (int fil, int col);+


/*******************************************************************************
 ******************************************************************************/

#endif // ALLEGRO_OUTPUT
