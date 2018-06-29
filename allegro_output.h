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

#define NOFCARS 15
#define BLACK (al_map_rgb(0,0,0))
#define WHITE (al_map_rgb(255,255,255))
#define FPS 60
#define CARS_TIMER 0.01
#define NOFLANES 13
#define NOFLAGS 0
#define CARS_MV 1

/********* COORDINATES CONSTANTS ***********/
/*#define ARROW_X
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

#define WIN_SPOT_X1
#define WIN_SPOT_X2
#define WIN_SPOT_X3
#define WIN_SPOT_X4
#define WIN_SPOT_X5*/


#define FROGSTEP_X (0.6*FROG_W) // cambiando (ajustar)
#define FROGSTEP_Y 49

#define INIT_X  350            // donde arranca la rana
#define INIT_Y  START_LANE_Y
#define FROG_X_MAX  691    // borders
#define FROG_X_MIN  9
#define FROG_Y_MAX  START_LANE_Y
#define FROG_Y_MIN  END_LANE_Y

#define START_LANE_Y  718          // lane inferior
#define LANE1_Y (START_LANE_Y - 1*FROGSTEP_Y)                // autos (4 carriles)
#define LANE2_Y (START_LANE_Y - 2*FROGSTEP_Y)
#define LANE3_Y (START_LANE_Y - 3*FROGSTEP_Y)
#define LANE4_Y (START_LANE_Y - 4*FROGSTEP_Y)
#define LANE5_Y (START_LANE_Y - 5*FROGSTEP_Y)
#define BUFFER_LANE_Y (START_LANE_Y - 6*FROGSTEP_Y)          // lane central
#define LANE6_Y (START_LANE_Y - 7*FROGSTEP_Y)               // troncos (5 carriles)
#define LANE7_Y (START_LANE_Y - 8*FROGSTEP_Y)
#define LANE8_Y (START_LANE_Y - 9*FROGSTEP_Y)
#define LANE9_Y (START_LANE_Y - 10*FROGSTEP_Y)
#define LANE10_Y (START_LANE_Y - 11*FROGSTEP_Y)
#define END_LANE_Y  (START_LANE_Y - 12*FROGSTEP_Y)             // lane superior

#define LIVES_Y 765
#define LIVE1_X 28
#define LIVES_OFFSET  28

#define RACECAR_W (al_get_bitmap_width(racecar))//49
#define RACECAR_H (al_get_bitmap_height(racecar))//43

#define TRACTOR_W (al_get_bitmap_width(tractor))//42
#define TRACTOR_H (al_get_bitmap_height(tractor))//36

#define ELECTRICCAR_W (al_get_bitmap_width(electriccar))//46
#define ELECTRICCAR_H (al_get_bitmap_height(electriccar))//30

#define TRUCK_W (al_get_bitmap_width(truck))//82
#define TRUCK_H (al_get_bitmap_height(truck))//30

#define WOOD_W (al_get_bitmap_width(wood))//176
#define WOOD_H (al_get_bitmap_height(wood))//30

#define SHORT_WOOD_W (al_get_bitmap_width(short_wood))//128
#define SHORT_WOOD_H (al_get_bitmap_height(short_wood))//30

#define LONG_WOOD_W (al_get_bitmap_width(long_wood))//274
#define LONG_WOOD_H (al_get_bitmap_height(long_wood))//30

#define FROG_W 44
#define FROG_H 33

#define LIVEFROG_W (al_get_bitmap_width(livefrog))//21
#define LIVEFROG_H (al_get_bitmap_height(livefrog))//21



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct car  //  estructura que contiene datos de los bitmaps asociados a los autos/troncos que se mueven
{
  int16_t x_pos; // coordenadas al CENTRO del carril ( y del bitmap)
  int16_t lane;   // número de carril
  int16_t x_size; // largo del bitmap, para analizar colisiones
  int16_t y_size;
  int16_t type;
} al_car_t;

typedef struct frog
{
  uint16_t x_pos;
  uint16_t lane;
  uint16_t orientation;
  uint16_t x_size;
  uint16_t y_size;
  uint16_t winSpots[5];
}al_frog_t;

typedef struct lane
{
  uint16_t lane;
  uint16_t divider;
  uint16_t dividerMax;
  bool way;
}al_lane_t;

typedef struct lastLane
{

}al_lastLane_t;



enum orientation {LEFT,RIGHT,UP,DOWN};    // enum de direcciones hacia las que se puede mover la rana
enum carType {ELECTRICCAR = 1,RACECAR,TRACTOR,TRUCK,WOOD,LONG_WOOD,SHORT_WOOD,BLOCK};    // enum  de los tipos de bitmap auto

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
void *output_thread(void* pointer);

/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve

// +ej: char lcd_goto (int fil, int col);+


/*******************************************************************************
 ******************************************************************************/

#endif // ALLEGRO_OUTPUT
