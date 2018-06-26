#include "allegro_output.h"

/*****************************************************************
Thread output_thread() (Allegro)

Recibe:
+ Puntero a gameData (estructura con toda la información del juego)

Devuelve:
+ Nada

******************************************************************/


void *output_thread(void* pointer)
{
  gameData_t *pGameData = pointer; // obtengo puntero a estrucura fundamental del juego
  bool carsTimer = false, dispTimer = false;
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_EVENT_QUEUE *output_queue = NULL;
  ALLEGRO_TIMER *al_display_timer = NULL, *al_cars_timer = NULL;
  ALLEGRO_EVENT event;

  /******************INICIALIZACIÓN/CONFIGURACION DE ALLEGRO********************/

/*if(!al_init())  // HACE FALTA? al main
{
  fprintf(stderr,"Failed to initialize Allegro\n");
  return true;
}*/

  if( !(output_queue = al_create_event_queue()) )
  {
    fprintf(stderr, "Failed to initialize event queue\n");
    exit(-1);
  }

  else if(!(al_display_timer = al_create_timer(1.0 / FPS)))
  {
    fprintf(stderr,"Failed to initialize display timer\n");
    al_destroy_event_queue(output_queue);
    exit(-1);
  }

  else if(!(al_cars_timer = al_create_timer(al_cars_timer)))
  {
    fprintf(stderr,"Failed to initialize cars timer\n");
    al_destroy_event_queue(output_queue);
    al_destroy_timer(al_display_timer);
    exit(-1);
  }
  else if(!al_init_image_addon())
  {
    fprintf(stderr,"Failed to initialize image addon\n");
    al_destroy_event_queue(output_queue);
    al_destroy_timer(al_display_timer);
    al_destroy_timer(al_cars_timer);
    exit(-1);
  }

  else if(!(display = al_create_display(DHEIGHT,DWIDTH)))
  {
    fprintf(stderr,"Failed to initialize display\n");
    al_destroy_event_queue(output_queue);
    al_destroy_timer(al_display_timer);
    al_destroy_timer(al_cars_timer);
    al_uninstall_system();
    al_shutdown_image_addon();
    exit(-1);
  }

  al_register_event_source(output_queue, al_get_timer_event_source(al_display_timer));  // regsitro ambos timers como generadores de eventos de Allegro
  al_register_event_source(output_queue, al_get_timer_event_source(al_cars_timer));


/***********************CARGA DE BITMAPS*****************************/

  ALLEGRO_BITMAP *start_menu_bknd = NULL;   // background de menu ppal
  ALLEGRO_BITMAP *pause_menu_bknd = NULL;   // background de menu de pausa
  ALLEGRO_BITMAP *game_bknd = NULL;        // background del juego
  ALLEGRO_BITMAP *arrow = NULL:            // bitmap del pointer de opciones (o resaltamos texto????)
  ALLEGRO_BITMAP *frogBitmap = NULL;             // bitmap de la rana (SOLO UNO, no lo vamos a hacer como Lucas, NO me jodan)
  ALLEGRO_BITMAP *car1 = NULL;            // bitmap de un tipo de auto
  ALLEGRO_BITMAP *car2 = NULL;            // bitmap de otro tipo de auto
  ALLEGRO_BITMAP *truck = NULL;           // bitmap de un camión
  ALLEGRO_BITMAP *wood = NULL;            // bitmap del tronco
  ALLEGRO_BITMAP *heart_on = NULL;        // bitmap de vida de la rana
  ALLEGRO_BITMAP *heart_off = NULL        // bitmap de vida perdida de la rana

  if( !(start_menu_bknd = al_load_bitmap("start_menu_bknd.png")) )
  {
  	fprintf(stderr,"Unable to load start_menu_bknd.png\n");
  	al_uninstall_system();
  	al_shutdown_image_addon();
  	al_destroy_display(display);

  	exit(-1);
  }

  else if( !(pause_menu_bknd = al_load_bitmap("pause_menu_bknd.png")) )
  {
  	fprintf(stderr,"Unable to load pause_menu_bknd.png\n");
  	al_uninstall_system();
  	al_shutdown_image_addon();
  	al_destroy_display(display);

  	exit(-1);
  }

  else if( !(game_bknd = al_load_bitmap("game_bknd.png")) )
  {
  	fprintf(stderr,"Unable to load game_bknd.png\n");
  	al_uninstall_system();
  	al_shutdown_image_addon();
  	al_destroy_display(display);

  	exit(-1);
  }

  else if( !(arrow = al_load_bitmap("arrow.png")) )
  {
  	fprintf(stderr,"Unable to load arrow.png\n");
  	al_uninstall_system();
  	al_shutdown_image_addon();
  	al_destroy_display(display);

  	exit(-1);
  }

  else if( !(frogBitmap = al_load_bitmap("frog.png")) )
  {
  	fprintf(stderr,"Unable to load frog.png\n");
  	al_uninstall_system();
  	al_shutdown_image_addon();
  	al_destroy_display(display);

  	exit(-1);
  }

  else if( !(car1 = al_load_bitmap("car1.png")) )
  {
  	fprintf(stderr,"Unable to load car1.png\n");
  	al_uninstall_system();
  	al_shutdown_image_addon();
  	al_destroy_display(display);

  	exit(-1);
  }

  else if( !(car2 = al_load_bitmap("car2.png")) )
  {
  	fprintf(stderr,"Unable to load car2.png\n");
  	al_uninstall_system();
  	al_shutdown_image_addon();
  	al_destroy_display(display);

  	exit(-1);
  }

  else if( !(truck = al_load_bitmap("truck.png")) )
  {
  	fprintf(stderr,"Unable to load truck.png\n");
  	al_uninstall_system();
  	al_shutdown_image_addon();
  	al_destroy_display(display);

  	exit(-1);
  }

  else if( !(wood = al_load_bitmap("wood.png")) )
  {
  	fprintf(stderr,"Unable to load wood.png\n");
  	al_uninstall_system();
  	al_shutdown_image_addon();
  	al_destroy_display(display);

  	exit(-1);
  }

  else if( !(heart_on = al_load_bitmap("heart_on.png")) )
  {
    fprintf(stderr,"Unable to load heart_on.png\n");
    al_uninstall_system();
    al_shutdown_image_addon();
    al_destroy_display(display);

    exit(-1);
  }

  else if( !(wood = al_load_bitmap("heart_off.png")) )
  {
    fprintf(stderr,"Unable to load heart_off.png\n");
    al_uninstall_system();
    al_shutdown_image_addon();
    al_destroy_display(display);

    exit(-1);
  }


  /********************INICIALIZACION DISPLAY*******************************/

  al_clear_to_color(BLACK);                           //macro definida en el header
  al_flip_display();                                 //inicializo display en negro

  /******************INICICIALIZACIÓN DE JUEGO*********************/
  al_frog_t frog = {.x_pos = INIT_X, .lane = INIT_Y, .orientation = UP, .x_size = al_get_bitmap_width(frog), .y_size = al_get_bitmap_height(frog)}; // inicializo estructura rana

  al_car_t carsArray[NOFCARS];                                                  // creo arreglo de estructuras auto

  //INICIALIZAR AUTOS


  /******************THREAD - MANEJO DE ESTADOS***************************************/

  while(!pGameData->quitGame) //SERÍA CONVENIENTE PODER CERRAR EL DISPLAY Y QUE TERMINE EL JUEGO -> EVENTO DE ALLEGRO -> traducir a evento de quitGame
  {
    if( (pGameData->currentState->stateID == START_PLAY_ID || pGameData->currentState->stateID == START_QUIT_ID || pGameData->currentState->stateID == START_SCOREBOARD_ID) && !pGameData->quitGame )//START MENU
    {
      al_draw_scaled_bitmap(start_menu_bknd,
                                            0,0,al_get_bitmap_width(start_menu_bknd),al_get_bitmap_height(start_menu_bknd),
                                            0,0,al_get_display_width(display),al_get_display_height(display),NULL);           // Dibujo background menu ppal

      switch(pGameData->currentState->stateID)
      {
        case START_PLAY_ID:
        al_draw_scaled_bitmap(arrow,
                                              0,0,al_get_bitmap_width(arrow),al_get_bitmap_height(arrow),
                                              START_PLAY_X,START_PLAY_Y,al_get_display_width(display),al_get_display_height(display),NULL);           // Dibujo arrow
          break;

       case START_SCOREBOARD_ID:
       al_draw_scaled_bitmap(arrow,
                                             0,0,al_get_bitmap_width(arrow),al_get_bitmap_height(arrow),
                                             START_SCOREBOARD_X,START_SCOREBOARD_Y,al_get_display_width(display),al_get_display_height(display),NULL);           // Dibujo arrow
         break;

       case START_QUIT_ID:
       al_draw_scaled_bitmap(arrow,
                                             0,0,al_get_bitmap_width(arrow),al_get_bitmap_height(arrow),
                                             START_QUIT_X,START_QUIT_Y,al_get_display_width(display),al_get_display_height(display),NULL);           // Dibujo arrow
        break;
      }

      if(dispTimer)
      {
        al_flip_display();
        dispTimer = false;
      }// traducir a eventos de allegro
      if(displayClose)
      {
          pGameData->quitGame = true;
      }
    }

    else if( (pGameData->currentState->stateID == SCORE_BOARD_ID) && !pGameData->quitGame ) //SCOREBOARD
    {
      //SCOREBOARD

    }

    else if( (pGameData->currentState->stateID == GAME_ID) && !pGameData->quitGame )  //GAMEPLAY
    {

      al_draw_scaled_bitmap(game_bknd,
                                            0,0,al_get_bitmap_width(game_bknd),al_get_bitmap_height(game_bknd),
                                            0,0,al_get_display_width(display),al_get_display_height(display),NULL);           // Dibujo background de juego

      //drawLives(pGameData->lives); ya lo hice al final

      if(carsTimer)  // si se produce un evento de timer, muevo los autos.
      {
        carsRoutine(&carArray,&frog,NOFCARS);        // llamo a función que mueve los autos y la rana, si es necesario.
        carsTimer = false;                                        // acknowledge
      }

      if(pGameData->moveFrog.flag)
      {
        moveFrog(pGameData->moveFrog.where,&frog);
        pGameData->moveFrog.flag = false;                         //acknowledge
      }

      if(checkBitmapcollision(&carArray,&frog,NOFCARS) && frog.lane > BUFFER_LANE_Y)  // choque en la parte inferior del tablero (autos)
      {
        pGameData->lives--;                                      //si choco, decremento las vidas
        /*if(pGameData->lives--)
        {
          mostrar(calavera);
          al_flip_display;

        }*/
        if( !emit_event(pGameData->pEventQueue,COLLISION_EVENT) )   //si la rana choco, le avisa al kernel
        {
            printf("Coludn't emit COLLISION event\n");
        }
      }


      else if(!checkBitmapcollision(&carArray,&frog,NOFCARS) && (frog.lane < BUFFER_LANE_Y && frog.lane > END_LANE_Y)) // choque en la parte superior del tablero
      {
        pGameData->lives--;
        /*if(pGameData->lives--)
        {
          mostrar(calavera);
          al_flip_display;

        }*/
        if( !emit_event(pGameData->pEventQueue,COLLISION_EVENT) )   //si la rana choco, le avisa al kernel
        {
            printf("Coludn't emit COLLISION event\n");
        }
      }


      else if(frog.lane == END_LANE_Y)
      {
        if(checkBitmapcollision(&carArray,&frog,NOFCARS) == END_LANE_Y)
        {
          pGameData->lives--;
        }
        else
        {
          //vote a Stolbizer (gané)
          if( !emit_event(pGameData->pEventQueue,WIN_EVENT) )   //si la rana ganó, entonces le aviso al kernel
          {
              printf("Coludn't emit WIN event\n");
          }
        }

        //checkFrogCollision(frog.lane,&carArray,&frog,NOFCARS): return (checkBitmapcollision(&carArray,&frog,NOFCARS) && frog.lane > BUFFER_LANE_Y) || (!checkBitmapcollision(&carArray,&frog,NOFCARS) && (frog.lane < BUFFER_LANE_Y && frog.lane > END_LANE_Y)) || ((frog.lane == END_LANE_Y) && (checkBitmapcollision(&carArray,&frog,NOFCARS) == END_LANE_Y)
      }

      if(dispTimer)                                           // imprimo tablero
      {
        /**************************** DIBUJO BACKGROUND ********************************************/
        al_clear_to_color(BLACK);                             // borro display (backbuffer)
        al_draw_scaled_bitmap(game_bknd,
                                              0,0,al_get_bitmap_width(game_bknd),al_get_bitmap_height(game_bknd),
                                              0,0,al_get_display_width(display),al_get_display_height(display),NULL);           // Dibujo background de juego
        /**************************** DIBUJO AUTOS ********************************************/
        int i;
        for(i=0 ; i<NOFCARS ; i++)
        {
          switch(carsArray->type)
          {
            case CAR1:
              al_draw_scaled_bitmap(car1,
                                                    al_get_bitmap_width(car1)/2,al_get_bitmap_height(car1)/2,al_get_bitmap_width(car1),al_get_bitmap_height(car1),
                                                    (carsArray+i)->x_pos,(carsArray+i)->lane,al_get_display_width(display),al_get_display_height(display),NULL);
              break;

            case CAR2:
              al_draw_scaled_bitmap(car2,
                                                    al_get_bitmap_width(car2)/2,al_get_bitmap_height(car2)/2,al_get_bitmap_width(car2),al_get_bitmap_height(car2),
                                                    (carsArray+i)->x_pos,(carsArray+i)->lane,al_get_display_width(display),al_get_display_height(display),NULL);
              break;

            case TRUCK:
              al_draw_scaled_bitmap(truck,
                                                    al_get_bitmap_width(truck)/2,al_get_bitmap_height(truck)/2,al_get_bitmap_width(truck),al_get_bitmap_height(truck),
                                                    (carsArray+i)->x_pos,(carsArray+i)->lane,al_get_display_width(display),al_get_display_height(display),NULL);
              break;

            case WOOD:
              al_draw_scaled_bitmap(wood,
                                                    al_get_bitmap_width(wood)/2,al_get_bitmap_height(wood)/2,al_get_bitmap_width(wood),al_get_bitmap_height(wood),
                                                    (carsArray+i)->x_pos,(carsArray+i)->lane,al_get_display_width(display),al_get_display_height(display),NULL);
              break;
          }
        }

        /**************************** DIBUJO RANA ********************************************/
        al_draw_scaled_bitmap(frogBitmap,
                                              al_get_bitmap_width(frogBitmap)/2,al_get_bitmap_height(frogBitmap)/2,al_get_bitmap_width(frogBitmap),al_get_bitmap_height(frogBitmap),
                                              frog->x_pos,frog->lane,al_get_display_width(display),al_get_display_height(display),NULL);
// orientación?
        /**************************** DIBUJO VIDAS ********************************************/
        switch(pGameData->lives)
        {
          case 1: // live1 ON; live2 OFF; live3 OFF
            al_draw_scaled_bitmap(heart_on,
                                                  al_get_bitmap_width(heart_on)/2,al_get_bitmap_height(heart_on)/2,al_get_bitmap_width(heart_on),al_get_bitmap_height(heart_on),
                                                  LIVE1_X,LIVES_Y,al_get_display_width(display),al_get_display_height(display),NULL);
            al_draw_scaled_bitmap(heart_off,
                                                  al_get_bitmap_width(heart_off)/2,al_get_bitmap_height(heart_off)/2,al_get_bitmap_width(heart_off),al_get_bitmap_height(heart_off),
                                                  LIVE2_X,LIVES_Y,al_get_display_width(display),al_get_display_height(display),NULL);

            al_draw_scaled_bitmap(heart_off,
                                                  al_get_bitmap_width(heart_off)/2,al_get_bitmap_height(heart_off)/2,al_get_bitmap_width(heart_off),al_get_bitmap_height(heart_off),
                                                  LIVE3_X,LIVES_Y,al_get_display_width(display),al_get_display_height(display),NULL);
            break;

          case 2: // live1 ON; live2 ON; live3 OFF
            al_draw_scaled_bitmap(heart_on,
                                                  al_get_bitmap_width(heart_on)/2,al_get_bitmap_height(heart_on)/2,al_get_bitmap_width(heart_on),al_get_bitmap_height(heart_on),
                                                  LIVE1_X,LIVES_Y,al_get_display_width(display),al_get_display_height(display),NULL);
            al_draw_scaled_bitmap(heart_off,
                                                  al_get_bitmap_width(heart_on)/2,al_get_bitmap_height(heart_on)/2,al_get_bitmap_width(heart_on),al_get_bitmap_height(heart_on),
                                                  LIVE2_X,LIVES_Y,al_get_display_width(display),al_get_display_height(display),NULL);

            al_draw_scaled_bitmap(heart_off,
                                                  al_get_bitmap_width(heart_off)/2,al_get_bitmap_height(heart_off)/2,al_get_bitmap_width(heart_off),al_get_bitmap_height(heart_off),
                                                  LIVE3_X,LIVES_Y,al_get_display_width(display),al_get_display_height(display),NULL);
            break;

          case 3: // live1 ON; live2 ON; live3 ON
            al_draw_scaled_bitmap(heart_on,
                                                  al_get_bitmap_width(heart_on)/2,al_get_bitmap_height(heart_on)/2,al_get_bitmap_width(heart_on),al_get_bitmap_height(heart_on),
                                                  LIVE1_X,LIVES_Y,al_get_display_width(display),al_get_display_height(display),NULL);
            al_draw_scaled_bitmap(heart_off,
                                                  al_get_bitmap_width(heart_on)/2,al_get_bitmap_height(heart_on)/2,al_get_bitmap_width(heart_on),al_get_bitmap_height(heart_on),
                                                  LIVE2_X,LIVES_Y,al_get_display_width(display),al_get_display_height(display),NULL);

            al_draw_scaled_bitmap(heart_off,
                                                  al_get_bitmap_width(heart_on)/2,al_get_bitmap_height(heart_on)/2,al_get_bitmap_width(heart_on),al_get_bitmap_height(heart_on),
                                                  LIVE3_X,LIVES_Y,al_get_display_width(display),al_get_display_height(display),NULL);
            break;
        }


        /**************************** MIRROR DEL BACKBUFFER ********************************************/
        al_flip_display();                          // mirror del backbuffer
        dispTimer = false;                          // acknowledge
      }
    }

    else if( (pGameData->currentState->stateID == PAUSE_RESUME_ID || pGameData->currentState->stateID == PAUSE_RESTART_ID) && !pGameData->quitGame ) // En menú de pausa
    {
      al_draw_scaled_bitmap(pause_bknd,
                                            0,0,al_get_bitmap_width(pause_bknd),al_get_bitmap_height(pause_bknd),
                                            0,0,al_get_display_width(display),al_get_display_height(display),NULL);           // Dibujo background de menu de pausa

        if(pGameData->currentState->stateID == PAUSE_RESUME_ID)
        {
          al_draw_scaled_bitmap(arrow,
                                                0,0,al_get_bitmap_width(arrow),al_get_bitmap_height(arrow),
                                                PAUSE_RESUME_ID_X,PAUSE_RESUME_ID_Y,al_get_display_width(display),al_get_display_height(display),NULL);    // Dibujo arrow
        }

        else if(pGameData->currentState->stateID == PAUSE_RESTART_ID)
        {
          al_draw_scaled_bitmap(arrow,
                                                0,0,al_get_bitmap_width(arrow),al_get_bitmap_height(arrow),
                                                PAUSE_RESTART_ID_X,PAUSE_RESTART_ID_Y,al_get_display_width(display),al_get_display_height(display),NULL);    // Dibujo arrow
        }

        if(dispTimer)
        {
          al_flip_display();
          dispTimer = false;
        }
    }

    else if( (pGameData->currentState->stateID == SAVE_SCORE_ID) && !pGameData->quitGame) // Terminó el juego y mi puntaje entró en el scoreboard
    {
        // guardar puntaje en scoreboard (misma funcion que en rpi)

    }

    if(al_get_next_event(output_queue,&event))
    {
      if(event.type == ALLEGRO_EVENT_TIMER)
      {
        if(event.timer.source == al_cars_timer)
        {
          carsTimer = true;
        }
        else if(event.timer.source == al_display_timer)
        {
          dispTimer = true;
        }
      }

      if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
      {
        pGameData->quitGame = true;                                             // cierro el juego
      }

    }

  }

} // End of output_thread()





































/*************************FUNCIONES AUXILIARES******************************/

/********************************************************************************
FUNCION checkBitmapcollision()
Esta función chequea si existe superposición en los bitmaps de los autos y el de la rana,
es decir, si existe una colisión en el juego.

RECIBE:
  + puntero void a arreglo de autos.
  + puntero void a estructura de la rana.
  + número de autos que están en el arreglo

DEVUELVE:
  + int carril si existe colisión
  + int 0 si no existe colisión

********************************************************************************/

int checkBitmapcollision(void *Cpointer, void *Fpointer, int NofCars) // agregar proteccion contra bordes !!!!!!!!!!!!!!!!!!!!!!!1
{
	al_car_t *p2carslist = Cpointer;
	al_frog_t *p2frog = Fpointer;
	uint8_t i,j;

	for(i=0 ; i<NofCars ; i++) // barrido de la lista de autos
	{
		if(p2frog->lane == (p2carslist+i)->lane) // si la rana y el auto están en el mismo carril...
		{
			for(j = ((p2carslist+i)->x_pos -(((p2carslist+i)->x_size)/2)) ; j <= ((p2carslist+i)->x_pos + (((p2carslist+i)->x_size)/2)) ; j++)
			{
				if( j == ((p2frog->x_frog)+((p2frog->x_size)/2)) || j == ((p2frog->x_frog)-((p2frog->x_size)/2))) // si alguno de los bordes de la rana están dentro del bitmap del auto...
				{
          return ((p2carslist+i)->lane); // devuelvo las coordenadas del carril donde hubo colisión
				}
			}
		}
	}

  return 0: // devuelvo 0 si no hubo colisión
}


/********************************************************************************
FUNCION carsRoutine()
Esta función se encarga de administrar el movimiento de los autos, o bien subir la velocidad
de movimiento de los mismos (en función a como se invoque)

RECIBE:
  + puntero void a arreglo de autos. (Si recibe NULL, entonces hay que subir la velocidad de los autos)
  + puntero void a estructura de la rana.
  + número de autos que están en el arreglo

DEVUELVE:
  + int carril si existe colisión
  + int 0 si no existe colisión

********************************************************************************/
void carsRoutine(void *Cpointer, void *Fpointer, int NofCars)
{

  static al_lane_t dividers[NOFLANES] = {
    {START_LANE_Y,0,0,0},
    {LANE1_Y,10,10,LEFT},
    {LANE2_Y,15,15,RIGHT},
    {LANE3_Y,40,40,LEFT},
    {LANE4_Y,10,10.RIGHT},
    {LANE5_Y,35,35,LEFT},
    {LANE6_Y,45,45,RIGHT},
    {BUFFER_LANE_Y,0,0,0},
    {LANE7_Y,30,30,LEFT},
    {LANE8_Y,10,10,RIGHT},
    {LANE9_Y,14,14,LEFT},
    {LANE10_Y,12,12,RIGHT},
    {LANE11_Y,30,30,LEFT},
    {LANE12_Y,20,20,RIGHT},
    {END_LANE_Y,0,0,0}
  };

  if(!Cpointer) // la llamaron para level up
  {
    int i;
    for(i=0 ; i<NOFLANES ; i++)
    {
      if(dividers[i].dividerMax > 1)
      {
        dividers[i].dividerMax--; // decremento dividers maximos
      }
    }
  }

  else
  {
    for(i=0 ; i<NOFLANES ; i++)
    {
      if(dividers[i].divider)
      {
        dividers[i].divider--; // decremento dividers maximos
      }
      else
      {
        moveCars(Cpointer,Fpointer,dividers[i].way,NofCars,dividers[i].lane);
      }
    }
  }
}






/********************************************************************************
FUNCION moveCars()
Esta función se encarga de simular el movimiento de los autos en los carriles, y
eventualmente mueve a la rana si asi se dan las condiciones.

el auto avanza por el carril hasta que desaparace completamente, por lo que las posiciones que se asignen
pueden quedar fuera del tablero. En ese sentido, esta función no realiza control alguno.
(la funcion que imprima el tablero se debe encargar de colocar correctamente los bitmaps)

RECIBE:
  + puntero void a arreglo de autos.
  + puntero void a estructura de la rana.
  + número de autos que están en el arreglo
  + carril que se desea mover
  + sentido de circulación del carril

DEVUELVE:
  + nada


  suponemos orientacion de display:

  0..........................>x
  .
  .
  .            DISPLAY
  .
  \/
  y

********************************************************************************/

void moveCars(void *Cpointer, void *Fpointer,int way, int NofCars, int lane)
{

  al_car_t *p2carslist = Cpointer;
	al_frog_t *p2frog = Fpointer;
  al_lane_t *p2lane = Lpointer;
  int i,j;

if(lane == checkBitmapcollision(&p2carslist,&p2frog,NofCars) && lane < BUFFER_LANE_Y)                             // si la rana colisiona con el auto, y estamos en la parte superior del tablero
{
  if(lane == LEFT)
  {
    if((p2frog->x_pos)-((p2frog->x_size)/2) <= FROG_X_MIN)                                                       //si la rana está en el borde izquierdo...
    {
      p2frog->x_pos == (FROG_X_MIN+((p2frog->x_size)/2));                                                        //se queda en su posición
    }

    else
    {
      p2frog->xpos--                                                                                               //muevo la rana a la izquierda
    }
  }

  else    // entonces el carril se mueve a la derecha
  {
    if((p2frog->x_pos)+((p2frog->x_size)/2) >= FROG_X_MAX)                                //si la rana está en el borde derecho...
    {
      p2frog->x_pos == (FROG_X_MAX-((p2frog->x_size)/2));                                                        //se queda en su posición
    }

    else
    {
      p2frog->xpos++                                                                    //muevo la rana a la derecha
    }
  }

}

for(i=0 ; i<NofCars ; i++)                                                      // verifico cada uno de los autos
{
  if(way == LEFT && ((p2carslist+i)->lane == lane))                                         // si el auto está en el carril que quiero mover
  {
    if(((p2carslist->x_pos)+((p2carslist->x_size)/2)) <= FROG_X_MIN)                       // si el bitmap salio completamente del display por la izquierda, aparece por la derecha
    {
      (p2carslist+i)->x_pos == (FROG_X_MAX + ((p2carslist->x_size)/2));
    }

    else
    {
      (p2carslist+i)->x_pos--;                                                    // muevo el auto hacia la izquierda
    }

  }

  else if((p2carslist+i)->way == RIGHT && ((p2carslist+i)->lane == lane))            // si el auto está en el carril que quiero mover
  {
    if(((p2carslist->x_pos)-((p2carslist->x_size)/2)) >= FROG_X_MAX)                       // si el bitmap salio completamente del display por la derecha, aparece por la izquierda.
    {
      (p2carslist+i)->x_pos == (FROG_X_MIN - ((p2carslist->x_size)/2));
    }

    else
    {
      (p2carslist+i)->x_pos++;                                                    // muevo el auto hacia la derecha
    }
  }


  /*if(checkBitmapcollision(&p2carslist,&p2frog,NofCars) && (p2frog->lane > BUFFER_LANE_Y))  // si la rana colisiona con el auto, y estamos en la parte superior del tablero
  {
    if(getLaneWay(p2frog->lane) == LEFT)
    {
      if((p2frog->x_pos)-((p2frog->x_size)/2) <= FROG_X_MIN)                                                       //si la rana está en el borde izquierdo...
      {
        p2frog->x_pos == (FROG_X_MIN+((p2frog->x_size)/2));                                                        //se queda en su posición
      }

      else
      {
        p2frog->xpos--                                                                    //muevo la rana a la izquierda
      }
    }

    else    // entonces el carril se mueve a la derecha
    {
      if((p2frog->x_pos)+((p2frog->x_size)/2) >= FROG_X_MAX)                                //si la rana está en el borde derecho...
      {
        p2frog->x_pos == (FROG_X_MAX-((p2frog->x_size)/2));                                                        //se queda en su posición
      }

      else
      {
        p2frog->xpos++                                                                    //muevo la rana a la derecha
      }
    }

  }

  for(i=0 ; i<NofCars ; i++)                                                      // verifico cada uno de los autos
  {
    if((p2carslist+i)->way == LEFT)
    {
      if(((p2carslist->x_pos)+((p2carslist->x_size)/2)) <= FROG_X_MIN)                       // si el bitmap salio completamente del display por la izquierda, aparece por la derecha
      {
        (p2carslist+i)->x_pos == (FROG_X_MAX + ((p2carslist->x_size)/2));
      }

      else
      {
        (p2carslist+i)->x_pos--;                                                    // muevo el auto hacia la izquierda
      }

    }

    else if((p2carslist+i)->way == RIGHT)
    {
      if(((p2carslist->x_pos)-((p2carslist->x_size)/2)) >= FROG_X_MAX)                       // si el bitmap salio completamente del display por la derecha, aparece por la izquierda.
      {
        (p2carslist+i)->x_pos == (FROG_X_MIN - ((p2carslist->x_size)/2));
      }

      else
      {
        (p2carslist+i)->x_pos++;                                                    // muevo el auto hacia la derecha
      }
    }

  }*/
}

/********************************************************************************
FUNCION getLaneWay()
Esta función nos dice para que lado se mueve un determinado carril

RECIBE:
  + coordenadas del carril a consultar
  + puntero void a arrego de autos
  + número de autos que están en el arreglo

DEVUELVE:
  + constantes LEFT o RIGHT, dependiendo del sentido del carril

********************************************************************************/
int getLaneWay(void *Cpointer, int lane, int NofCars)
{
  al_car_t *p2carslist = Cpointer;
  int i,j,k;

  for(i=0 ; i<NofCars ; i++)
  {
    if((p2carslist+i)->lane == lane)
    {
      return((p2carslist+i)->way);
    }
  }
  fprintf(stderr, "No se encontró sentido para el carril solicitado\n");
  exit(-1);
}

/***************************************************
FUNCION moveFrog()
Mueve la rana en 4 direcciones, en el tablero

RECIBE:
  + constante que indica hacia donde se debe mover la rana.
  + puntero a arreglo de la arranca

DEVUELVE:
  + nada

****************************************************/
void moveFrog(uint8_t where,frog_t *frogCoords)
{
  switch(where)
  {
      case FROG_UP:
          if(frogCoords->lane - frogCoords->y_size/2 > FROG_Y_MIN)
          {
              frogCoords->lane-= FROGSTEP_Y;
          }
          else if(frogCoords->lane - frogCoords->y_size/2 < FROG_Y_MIN)
          {
              frogCoords->lane = FROG_Y_MIN;
          }
          frogCoords->orientation = UP;
          break;

      case FROG_DOWN:
          if(frogCoords->lane + frogCoords->y_size/2 < FROG_Y_MAX)
          {
              frogCoords->lane += FROGSTEP_Y;
          }
          else if(frogCoords->lane + frogCoords->y_size/2 > FROG_Y_MAX)
          {
              frogCoords->lane = FROG_Y_MAX;
          }
          frogCoords->orientation = DOWN;
          break;

      case FROG_RIGHT:
          if(frogCoords->x + frogCoords->x_size/2 < FROG_X_MAX)
          {
              frogCoords->x += FROGSTEP_X;
          }
          else if(frogCoords->x + frogCoords->x_size/2 > FROG_X_MAX)
          {
              frogCoords->x = FROG_X_MAX;
          }
          frogCoords->orientation = RIGHT;
          break;

      case FROG_LEFT:
          if(frogCoords->x - frogCoords->x_size/2 > FROG_X_MIN)
          {
              frogCoords->x -= FROGSTEP_X;
          }
          else if(frogCoords->x - frogCoords->x_size/2 < FROG_X_MIN)   //programacion defensiva
          {
              frogCoords->x = FROG_X_MIN;
          }
          frogCoords->orientation = LEFT;
          break;
   }
}

/***************************************************
FUNCION printBoard()
Imprime el estado del juego

RECIBE:
  + constante que indica hacia donde se debe mover la rana.
  + puntero a arreglo de la arranca

DEVUELVE:
  + nada

****************************************************/
