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
#define DWIDTH  700
#define DHEIGHT 800

#define NOFCARS 10
#define BLACK (al_map_rgb(0,0,0))
#define WHITE (al_map_rgb(255,255,255))
#define FPS 60
#define CARS_TIMER 1
#define NOFLANES 15
#define NOFLAGS 0

/********* COORDINATES CONSTANTS ***********/
#define ARROW_X
#define START_PLAY_X // coordenadas de los strings para colocar el arrow pointer
#define START_PLAY_Y
#define START_SCOREBOARD_X
#define START_SCOREBOARD_Y
#define START_QUIT_X
#define START_QUIT_Y
#define PAUSE_RESTART_ID_X
#define PAUSE_RESTART_ID_Y
#define PAUSE_RESUME_ID_X
#define PAUSE_RESUME_ID_Y

#define FROGSTEP_X FROG_W
#define FROGSTEP_Y 49

#define INIT_X  350            // donde arranca la rana
#define INIT_Y  START_LANE_Y
#define FROG_X_MAX  691    // borders
#define FROG_X_MIN  9
#define FROG_Y_MAX  START_LANE_Y
#define FROG_Y_MIN  END_LANE_Y

#define START_LANE_Y  718          // lane inferior
#define LANE1_Y (START_LANE - 1*FROGSTEP_X)                // autos (4 carriles)
#define LANE2_Y (START_LANE - 2*FROGSTEP_X)
#define LANE3_Y (START_LANE - 3*FROGSTEP_X)
#define LANE4_Y (START_LANE - 4*FROGSTEP_X)
#define LANE5_Y (START_LANE - 5*FROGSTEP_X)
#define BUFFER_LANE_Y (START_LANE - 6*FROGSTEP_X)          // lane central
#define LANE6_Y (START_LANE - 7*FROGSTEP_X)               // troncos (5 carriles)
#define LANE7_Y (START_LANE - 8*FROGSTEP_X)
#define LANE8_Y (START_LANE - 9*FROGSTEP_X)
#define LANE9_Y (START_LANE - 10*FROGSTEP_X)
#define LANE10_Y (START_LANE - 11*FROGSTEP_X)
#define END_LANE_Y  (START_LANE - 12*FROGSTEP_X)             // lane superior

#define LIVES_Y 765
#define LIVE1_X 28
#define LIVES_OFFSET  28

#define RACECAR_W 49
#define RACECAR_H 43

#define TRACTOR_W 42
#define TRACTOR_H 36

#define ELECTRICCAR_W 46
#define ELECTRICCAR_H 30

#define TRUCK_W 82
#define TRUCK_H 30

#define WOOD_W 176
#define WOOD_H 30

#define SHORTWOOD_W 128
#define SHORTWOOD_H 30

#define LONGWOOD_W 274
#define LONGWOOD_H 30

#define FROG_W 44
#define FROG_H 33

#define LIVEFROG_W 21
#define LIVEFROG_H 21



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct car  //  estructura que contiene datos de los bitmaps asociados a los autos/troncos que se mueven
{
  uint8_t x_pos; // coordenadas al CENTRO del carril ( y del bitmap)
  uint8_t lane;   // número de carril
  uint8_t x_size; // largo del bitmap, para analizar colisiones
  uint8_t type;
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
enum carType {ELECTRICCAR,RACECAR,TRACTOR,TRUCK,WOOD,LONG_WOOD,SHORT_WOOD};    // enum  de los tipos de bitmap auto

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
