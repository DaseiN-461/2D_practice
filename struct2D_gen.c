#include <stdio.h>
#include <stdint.h>

#define x_size 3
#define y_size 3

#define x_grid_size 9
#define y_grid_size 9

uint8_t grid[x_grid_size][y_grid_size];

uint8_t pos[2] = {1,2};

uint8_t mask[3][3] = {
                        {0xFF,0xFF,0xFF},
                        {0xFF,0xFF,0xFF},
                        {0xFF,0xFF,0xFF},
                    };

typedef struct{
    uint8_t mask[x_size][y_size];
    uint8_t pos[2];
}object2D;

object2D myObject = {
    .mask = {},
    .pos = {}
};

void generate_grid();
void generate_struct();
void object2grid(object2D *ptr_object);
void print_grid();




void main(){
    generate_grid();

    generate_struct(&myObject, pos, mask);


    object2grid(&myObject);


    print_grid();
    

}


void generate_grid(){
    for(uint8_t y=0; y<x_grid_size; y++){
        for(uint8_t x=0; x<x_grid_size; x++){
            grid[x][y] = 0x00;
        }    
    }
}

void generate_struct(object2D *ptr_object ,uint8_t pos[2], uint8_t mask[x_size][y_size]){
    
    ptr_object -> pos[0] = pos[0];
    ptr_object -> pos[1] = pos[1];
    
    for(uint8_t y=0; y<y_size; y++){
        for(uint8_t x=0; x<x_size; x++){
            ptr_object -> mask[x][y] = mask[x][y];
        }
    }
}

void object2grid(object2D *ptr_object){
    uint8_t x_pos = ptr_object->pos[0];
    uint8_t y_pos = ptr_object->pos[1];

    for(uint8_t y=0; y<y_size; y++){
        for(uint8_t x=0; x<x_size; x++){
            grid[x_pos + x][y_pos + y] = ptr_object -> mask[x][y];
        }
    }
}

void print_grid(){
    uint8_t col = 0;
    printf("\r\n");
    for(uint8_t y=0; y<y_grid_size; y++){
        printf("col %d    :",col);
        col++;
        for(uint8_t x=0; x<x_grid_size; x++){
            printf(" %02X ", grid[x][y]);
        }
        printf("\r\n");
    }
}