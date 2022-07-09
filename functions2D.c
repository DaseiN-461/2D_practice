#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "defines.h"



void main(){
    generate_grid();
    
    //generate_object(&myObject0 , pos0, mask_0, mask_color);
    //object2grid(&myObject0);
    //print_grid();

    //object2D new_object = update_object(3,6,mask_color);

    //update_grid(&myObject0,&new_object);
    //print_grid();

    object2D last_object = myObject0;
    object2D new_object = update_object(3,6,mask_color);
    for(uint8_t i=0; i<7; i++){
        new_object = update_object(3,6-i,mask_color);
    

        update_grid(&last_object, &new_object);
        last_object = new_object;
        print_grid();
        printf("\r\n-----\r\n");
    }


}










