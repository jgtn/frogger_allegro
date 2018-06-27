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
  ALLEGRO_BITMAP *vertical_frog = NULL;    // bitmap de la rana vertical
  ALLEGRO_BITMAP *side_frog = NULL         // bitmap de la rana horizontal
  ALLEGRO_BITMAP *racecar = NULL;            // bitmap de un tipo de auto
  ALLEGRO_BITMAP *electriccar = NULL;            // bitmap de otro tipo de auto
  ALLEGRO_BITMAP *tractor = NULL;             // bitmap de otro tipo de auto
  ALLEGRO_BITMAP *truck = NULL;           // bitmap de un camión
  ALLEGRO_BITMAP *long_wood = NULL;       // bitmap del tronco
  ALLEGRO_BITMAP *wood = NULL;            //
  ALLEGRO_BITMAP *short_wood = NULL;      //
  ALLEGRO_BITMAP *livefrog = NULL;        // bitmap de vida de la rana

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

  else if( !(vertical_frog = al_load_bitmap("vertical_frog.png")) )
  {
  	fprintf(stderr,"Unable to load vertical_frog.png\n");
  	al_uninstall_system();
  	al_shutdown_image_addon();
  	al_destroy_display(display);

  	exit(-1);
  }

  else if( !(side_frog = al_load_bitmap("side_frog.png")) )
  {
    fprintf(stderr,"Unable to load side_frog.png\n");
    al_uninstall_system();
    al_shutdown_image_addon();
    al_destroy_display(display);

    exit(-1);
  }

  else if( !(racecar = al_load_bitmap("racecar.png")) )
  {
  	fprintf(stderr,"Unable to load racecar.png\n");
  	al_uninstall_system();
  	al_shutdown_image_addon();
  	al_destroy_display(display);

  	exit(-1);
  }

  else if( !(electriccar = al_load_bitmap("electriccar.png")) )
  {
  	fprintf(stderr,"Unable to load electriccar.png\n");
  	al_uninstall_system();
  	al_shutdown_image_addon();
  	al_destroy_display(display);

  	exit(-1);
  }

  else if( !(tractor = al_load_bitmap("tractor.png")) )
  {
    fprintf(stderr,"Unable to load tractor.png\n");
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

  else if( !(long_wood = al_load_bitmap("long_wood.png")) )
  {
    fprintf(stderr,"Unable to load long_wood.png\n");
    al_uninstall_system();
    al_shutdown_image_addon();
    al_destroy_display(display);

    exit(-1);
  }

  else if( !(short_wood = al_load_bitmap("short_wood.png")) )
  {
    fprintf(stderr,"Unable to load short_wood.png\n");
    al_uninstall_system();
    al_shutdown_image_addon();
    al_destroy_display(display);

    exit(-1);
  }

  else if( !(livefrog = al_load_bitmap("livefrog.png")) )
  {
    fprintf(stderr,"Unable to load livefrog.png\n");
    al_uninstall_system();
    al_shutdown_image_addon();
    al_destroy_display(display);

    exit(-1);
  }


  /********************INICIALIZACION DISPLAY*******************************/

  al_clear_to_color(BLACK);                           //macro definida en el header
  al_flip_display();                                 //inicializo display en negro

  /******************INICICIALIZACIÓN DE JUEGO*********************/
  al_frog_t frog = {.x_pos = INIT_X, .lane = INIT_Y, .orientation = UP, .x_size = FROG_W, .y_size = FROG_H}; // inicializo estructura rana

  al_car_t carsArray[NOFCARS];                                                  // creo arreglo de estructuras auto

  //INICIALIZAR AUTOS


  /******************THREAD - MANEJO DE ESTADOS***************************************/

  while(!pGameData->quitGame) //SERÍA CONVENIENTE PODER CERRAR EL DISPLAY Y QUE TERMINE EL JUEGO -> EVENTO DE ALLEGRO -> traducir a evento de quitGame
  {
    if( (pGameData->currentState->stateID == START_PLAY_ID || pGameData->currentState->stateID == START_QUIT_ID || pGameData->currentState->stateID == START_SCOREBOARD_ID) && !pGameData->quitGame )//START MENU
    {
      al_draw_bitmap(start_menu_bknd,0,0,NOFLAGS);           // Dibujo background menu ppal

      switch(pGameData->currentState->stateID)
      {
        case START_PLAY_ID:
        al_draw_bitmap(arrow,ARROW_X,START_PLAY_Y,NOFLAGS);      // Dibujo arrow
          break;

       case START_SCOREBOARD_ID:
       al_draw_bitmap(arrow,ARROW_X,START_SCOREBOARD_Y,NOFLAGS);    // Dibujo arrow
         break;

       case START_QUIT_ID:
       al_draw_bitmap(arrow,ARROW_X,START_QUIT_Y,NOFLAGS);   // Dibujo arrow
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

      al_draw_bitmap(game_bknd,0,0,NOFLAGS);          // Dibujo background de juego

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
          // volver la rana a inicio.
          // escribir la rana en la posición a la que llegó.
          // sumar puntaje

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
        al_draw_bitmap(game_bknd,0,0,NOFLAGS);           // Dibujo background de juego
        /**************************** DIBUJO AUTOS ********************************************/
        int i;
        for(i=0 ; i<NOFCARS ; i++)
        {
          switch((carsArray+i)->type)
          {
            case RACECAR:
              al_draw_scaled_bitmap(racecar,
                                                    al_get_bitmap_width(racecar)/2,al_get_bitmap_height(racecar)/2,al_get_bitmap_width(racecar),al_get_bitmap_height(racecar),
                                                    (carsArray+i)->x_pos,(carsArray+i)->lane,al_get_display_width(racecar),al_get_display_height(racecar),NULL);
              break;

            case ELECTRICCAR:
              al_draw_scaled_bitmap(electriccar,
                                                    al_get_bitmap_width(electriccar)/2,al_get_bitmap_height(electriccar)/2,al_get_bitmap_width(electriccar),al_get_bitmap_height(electriccar),
                                                    (carsArray+i)->x_pos,(carsArray+i)->lane,al_get_display_width(electriccar),al_get_display_height(electriccar),NULL);
              break;

            case TRACTOR:
              al_draw_scaled_bitmap(electriccar,
                                                    al_get_bitmap_width(tractor)/2,al_get_bitmap_height(tractor)/2,al_get_bitmap_width(tractor),al_get_bitmap_height(tractor),
                                                    (carsArray+i)->x_pos,(carsArray+i)->lane,al_get_display_width(tractor),al_get_display_height(tractor),NULL);
              break;

            case TRUCK:
              al_draw_scaled_bitmap(truck,
                                                    al_get_bitmap_width(truck)/2,al_get_bitmap_height(truck)/2,al_get_bitmap_width(truck),al_get_bitmap_height(truck),
                                                    (carsArray+i)->x_pos,(carsArray+i)->lane,al_get_display_width(truck),al_get_display_height(truck),NULL);
              break;

            case WOOD:
              al_draw_scaled_bitmap(wood,
                                                    al_get_bitmap_width(wood)/2,al_get_bitmap_height(wood)/2,al_get_bitmap_width(wood),al_get_bitmap_height(wood),
                                                    (carsArray+i)->x_pos,(carsArray+i)->lane,al_get_display_width(wood),al_get_display_height(wood),NULL);
              break;

            case LONG_WOOD:
              al_draw_scaled_bitmap(wood,
                                                    al_get_bitmap_width(long_wood)/2,al_get_bitmap_height(long_wood)/2,al_get_bitmap_width(long_wood),al_get_bitmap_height(long_wood),
                                                    (carsArray+i)->x_pos,(carsArray+i)->lane,al_get_display_width(long_wood),al_get_display_height(long_wood),NULL);
              break;

            case SHORT_WOOD:
              al_draw_scaled_bitmap(wood,
                                                    al_get_bitmap_width(short_wood)/2,al_get_bitmap_height(short_wood)/2,al_get_bitmap_width(short_wood),al_get_bitmap_height(short_wood),
                                                    (carsArray+i)->x_pos,(carsArray+i)->lane,al_get_display_width(short_wood),al_get_display_height(short_wood),NULL);
              break;

          }
        }

        /**************************** DIBUJO RANA ********************************************/

        if(frog.orientation == UP || frog.orientation == DOWN)
        {
          al_draw_scaled_bitmap(vertical_frog,
                                                al_get_bitmap_width(vertical_frog)/2,al_get_bitmap_height(vertical_frog)/2,al_get_bitmap_width(vertical_frog),al_get_bitmap_height(vertical_frog),
                                                frog->x_pos,frog->lane,al_get_display_width(vertical_frog),al_get_display_height(vertical_frog),NULL);
        }

        else if(frog.orientation == LEFT || frog.orientation == RIGHT)
        {
          al_draw_scaled_bitmap(side_frog,
                                                al_get_bitmap_width(side_frog)/2,al_get_bitmap_height(side_frog)/2,al_get_bitmap_width(side_frog),al_get_bitmap_height(side_frog),
                                                frog->x_pos,frog->lane,al_get_display_width(side_frog),al_get_display_height(side_frog),NULL);
        }

        else
        {
          fprintf(stderr, "wrong frog orientation!\n");
          exit(-1);
        }


// orientación?
        /**************************** DIBUJO VIDAS ********************************************/
        switch(pGameData->lives)
        {
          case 1: // live1 ON; live2 OFF; live3 OFF
            al_draw_scaled_bitmap(livefrog,
                                                  al_get_bitmap_width(livefrog)/2,al_get_bitmap_height(livefrog)/2,al_get_bitmap_width(livefrog),al_get_bitmap_height(livefrog),
                                                  LIVE1_X,LIVES_Y,al_get_display_width(display),al_get_display_height(display),NULL);
            al_draw_scaled_bitmap(heart_off,
                                                  al_get_bitmap_width(heart_off)/2,al_get_bitmap_height(heart_off)/2,al_get_bitmap_width(heart_off),al_get_bitmap_height(heart_off),
                                                  LIVE2_X,LIVES_Y,al_get_display_width(heart_off),al_get_display_height(heart_off),NULL);

            al_draw_scaled_bitmap(heart_off,
                                                  al_get_bitmap_width(heart_off)/2,al_get_bitmap_height(heart_off)/2,al_get_bitmap_width(heart_off),al_get_bitmap_height(heart_off),
                                                  LIVE3_X,LIVES_Y,al_get_display_width(heart_off),al_get_display_height(heart_off),NULL);
            break;

          case 2: // live1 ON; live2 ON; live3 OFF
            al_draw_scaled_bitmap(livefrog,
                                                  al_get_bitmap_width(livefrog)/2,al_get_bitmap_height(livefrog)/2,al_get_bitmap_width(livefrog),al_get_bitmap_height(livefrog),
                                                  LIVE1_X,LIVES_Y,al_get_display_width(livefrog),al_get_display_height(livefrog),NULL);
            al_draw_scaled_bitmap(livefrog,
                                                  al_get_bitmap_width(livefrog)/2,al_get_bitmap_height(livefrog)/2,al_get_bitmap_width(livefrog),al_get_bitmap_height(livefrog),
                                                  LIVE2_X,LIVES_Y,al_get_display_width(livefrog),al_get_display_height(livefrog),NULL);

            al_draw_scaled_bitmap(heart_off,
                                                  al_get_bitmap_width(heart_off)/2,al_get_bitmap_height(heart_off)/2,al_get_bitmap_width(heart_off),al_get_bitmap_height(heart_off),
                                                  LIVE3_X,LIVES_Y,al_get_display_width(heart_off),al_get_display_height(heart_off),NULL);
            break;

          case 3: // live1 ON; live2 ON; live3 ON
            al_draw_scaled_bitmap(livefrog,
                                                  al_get_bitmap_width(livefrog)/2,al_get_bitmap_height(livefrog)/2,al_get_bitmap_width(livefrog),al_get_bitmap_height(livefrog),
                                                  LIVE1_X,LIVES_Y,al_get_display_width(livefrog),al_get_display_height(livefrog),NULL);
            al_draw_scaled_bitmap(livefrog,
                                                  al_get_bitmap_width(livefrog)/2,al_get_bitmap_height(livefrog)/2,al_get_bitmap_width(livefrog),al_get_bitmap_height(livefrog),
                                                  LIVE2_X,LIVES_Y,al_get_display_width(livefrog),al_get_display_height(livefrog),NULL);

            al_draw_scaled_bitmap(livefrog,
                                                  al_get_bitmap_width(livefrog)/2,al_get_bitmap_height(livefrog)/2,al_get_bitmap_width(livefrog),al_get_bitmap_height(livefrog),
                                                  LIVE3_X,LIVES_Y,al_get_display_width(livefrog),al_get_display_height(livefrog),NULL);
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

if(lane == isInside(&p2carslist,&p2frog,NofCars) && lane < BUFFER_LANE_Y)                             // si la rana colisiona con el auto, y estamos en la parte superior del tablero
{
  if(way == LEFT)
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
FUNCION isInside()
Esta función consulta si el bitmap de la rana se encuentra TOTALMENTE DENTRO del bitmap
de algun auto en un carril determinado.

RECIBE:
  + puntero void a arreglo de autos.
  + puntero void a estructura de la rana.
  + número de autos que están en el arreglo

DEVUELVE:
  + carril en donde se encuentra la rana
  + int 0 caso contrario

********************************************************************************/

int isInside(void *Cpointer, void *Fpointer, int NofCars) // agregar proteccion contra bordes !!!!!!!!!!!!!!!!!!!!!!!1
{
	al_car_t *p2carslist = Cpointer;
	al_frog_t *p2frog = Fpointer;
  uint8_t frogedge1 = (p2frog->x_pos)+0.5*(p2frog->x_size);
  uint8_t frogedge2 = (p2frog->x_pos)-0.5*(p2frog->x_size);
	uint8_t i;

	for(i=0 ; i<NofCars ; i++) // barrido de la lista de autos
	{
		if(p2frog->lane == (p2carslist+i)->lane) // si la rana y el auto están en el mismo carril...
		{
      caredgeMIN = (((p2carslist+i)->x_pos)-0.5*((p2carslist+i)->x_size)); // asigno bordes del tronco
      caredgeMAX = (((p2carslist+i)->x_pos)+0.5*((p2carslist+i)->x_size)); // para mejor lectura del argumento del condicional

			if((frogedge1 >= caredgeMIN )&&(frogedge1 <= caredgeMAX)&&(frogedge2 >= caredgeMIN)&&(frogedge2 <= caredgeMAX))
      {
        return (p2frog->lane); // si ambos bordes de la rana están contenidos en el tronco, entonces la misma está posicionada totalmente encima del bitmap tronco.
      }
		}
	}

  return 0: // devuelvo 0 si la rana no está contenida en un tronco
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
          if(frogCoords->lane > END_LANE_Y)
          {
              frogCoords->lane-= FROGSTEP_Y;
          }
          else if(frogCoords->lane <= END_LANE_Y)
          {
              frogCoords->lane = END_LANE_Y;
          }
          frogCoords->orientation = UP;
          break;

      case FROG_DOWN:
          if(frogCoords->lane < START_LANE_Y)
          {
              frogCoords->lane += FROGSTEP_Y;
          }
          else if(frogCoords->lane >= START_LANE_Y)
          {
              frogCoords->lane = START_LANE_Y;
          }
          frogCoords->orientation = DOWN;
          break;

      case FROG_RIGHT:
          if(frogCoords->x + frogCoords->x_size < FROG_X_MAX)
          {
              frogCoords->x += FROGSTEP_X;
          }
          else if(frogCoords->x + frogCoords->x_size/2 > FROG_X_MAX)
          {
              frogCoords->x = (FROG_X_MAX - frogCoords->x_size/2);
          }
          frogCoords->orientation = RIGHT;
          break;

      case FROG_LEFT:
          if(frogCoords->x - frogCoords->x_size > FROG_X_MIN)
          {
              frogCoords->x -= FROGSTEP_X;
          }
          else if(frogCoords->x - frogCoords->x_size/2 < FROG_X_MIN)   //programacion defensiva
          {
              frogCoords->x = (FROG_X_MIN + frogCoords->x_size/2);
          }
          frogCoords->orientation = LEFT;
          break;
   }
}
