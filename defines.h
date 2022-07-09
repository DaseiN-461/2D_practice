#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define pixel_size 10

#define x_size 8
#define y_size 8

#define x_grid_size 64
#define y_grid_size 64

uint32_t grid[x_grid_size][y_grid_size];
uint32_t background[x_grid_size][y_grid_size] = {{0XFF,0XFF,0XFF,                                                    0XFF,0XFF,0XFF,
                                                 0XFF,0XFF,0XFF},
                                                {0XFF,0XFF,0XFF,                     0XFF,0XFF,0XFF,
                                                 0XFF,0XFF,0XFF},
                                                {0XFF,0XFF,0XFF,                     0XFF,0XFF,0XFF,
                                                 0XFF,0XFF,0XFF},
                                                {0XFF,0XFF,0XFF,                     0XFF,0XFF,0XFF,
                                                 0XFF,0XFF,0XFF},
                                                {0XFF,0XFF,0XFF,                     0XFF,0XFF,0XFF,
                                                 0XFF,0XFF,0XFF},
                                                {0XFF,0XFF,0XFF,                     0XFF,0XFF,0XFF,
                                                 0XFF,0XFF,0XFF},
                                                {0XFF,0XFF,0XFF,                     0XFF,0XFF,0XFF,
                                                 0XFF,0XFF,0XFF},
                                                {0XFF,0XFF,0XFF,                     0XFF,0XFF,0XFF,
                                                 0XFF,0XFF,0XFF},
                                                {0XFF,0XFF,0XFF,                     0XFF,0XFF,0XFF,
                                                 0XFF,0XFF,0XFF}
};



uint32_t mask_color[3][3] = {
                        {0x00,0x01,0x02},
                        {0x10,0x11,0x12},
                        {0x20,0x21,0x22},
                    };

uint8_t pos0[2] = {3,3};
bool mask_0[9][9] = {
                        {0,0,0,0,0,0,0,0,0}, //0
                        {0,0,0,0,0,0,0,0,0}, //1 
                        {0,0,0,0,0,0,0,0,0}, //2
                        {0,0,0,1,1,1,0,0,0}, //3
                        {0,0,0,1,1,1,0,0,0}, //4
                        {0,0,0,1,1,1,0,0,0}, //5
                        {0,0,0,0,0,0,0,0,0}, //6
                        {0,0,0,0,0,0,0,0,0}, //7
                        {0,0,0,0,0,0,0,0,0}  //8
                    };

uint8_t pos1[2] = {5,2};
bool mask_1[9][9] = {
                        {0,0,0,0,0,0,0,0,0}, //0
                        {0,0,0,0,0,0,0,0,0}, //1
                        {0,0,0,0,0,1,1,1,0}, //2
                        {0,0,0,0,0,1,1,1,0}, //3
                        {0,0,0,0,0,1,1,1,0}, //4
                        {0,0,0,0,0,0,0,0,0}, //5
                        {0,0,0,0,0,0,0,0,0}, //6
                        {0,0,0,0,0,0,0,0,0}, //7
                        {0,0,0,0,0,0,0,0,0}  //8
                    };



typedef struct{
    bool mask_grid[x_grid_size][y_grid_size];
    uint32_t mask_color[x_size][y_size];
    uint8_t pos[2];
    uint8_t walk_state; 
}object2D;

object2D myObject0 = {
    .mask_grid = {},
    .mask_color = {},
    .pos = {}
};

object2D myObject1 = {
    .mask_grid = {},
    .mask_color = {},
    .pos = {}
};
enum{
    state_0,
    state_1,
    state_2,
    state_3
};
uint8_t walk_state = state_0;

void generate_grid();
void generate_struct(object2D *ptr_object ,uint8_t pos[2], bool mask_grid[x_grid_size][y_grid_size], uint32_t mask_color[x_size][y_size]);
void object2grid(object2D *ptr_object);
void print_grid();

void object_update(object2D *ptr_object0,object2D *ptr_object1);
bool mask_union[x_grid_size][y_grid_size];



void generate_grid(){
    for(uint8_t y=0; y<x_grid_size; y++){
        for(uint8_t x=0; x<x_grid_size; x++){
            grid[x][y] = 0xFFFF;
        }    
    }
}

void generate_struct(object2D *ptr_object ,uint8_t pos[2], bool mask_grid[x_grid_size][y_grid_size], uint32_t mask_color[x_size][y_size]){
    
    ptr_object -> pos[0] = pos[0];
    ptr_object -> pos[1] = pos[1];
    
    for(uint8_t y=0; y<y_grid_size; y++){
        for(uint8_t x=0; x<x_grid_size; x++){
            ptr_object -> mask_grid[x][y] = mask_grid[x][y];
        }
    }
    for(uint8_t y=0; y<y_size; y++){
        for(uint8_t x=0; x<x_size; x++){
            ptr_object -> mask_color[x][y] = mask_color[x][y];
        }
    }
}

void object2grid(object2D *ptr_object){
    uint8_t x0 = ptr_object->pos[0];
    uint8_t y0 = ptr_object->pos[1];
    
    uint32_t mask_color[x_size][y_size];

    for(uint8_t y=0; y<y_size; y++){
        for(uint8_t x=0; x<x_size; x++){
            mask_color[x][y] = ptr_object-> mask_color[x][y];
            grid[x0 + x][y0 + y] = ptr_object -> mask_color[x][y];
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
            printf(" %04X ", grid[x][y]);
        }
        printf("\r\n");
    }
}

void object_update(object2D *ptr_object0,object2D *ptr_object1){
    bool mask_0[x_grid_size][y_grid_size]; 
    bool mask_1[x_grid_size][y_grid_size];
    
    uint32_t mask_color0[x_size][y_size];
    uint32_t mask_color1[x_size][y_size];
    
    uint8_t x0 = ptr_object0 -> pos[0];
    uint8_t y0 = ptr_object0 -> pos[1];
    
    uint8_t x1 = ptr_object1 -> pos[0];
    uint8_t y1 = ptr_object1 -> pos[1];
    
    bool flag = 0;
    
    for(uint8_t y=0; y<y_grid_size; y++){
            for(uint8_t x=0; x<x_grid_size; x++){
                mask_0[x][y] = ptr_object0 -> mask_grid[x][y];
                mask_1[x][y] = ptr_object1 -> mask_grid[x][y];
            }    
    }
    
    for(uint8_t y=0; y<y_size; y++){
            for(uint8_t x=0; x<x_size; x++){
                mask_color0[x][y] = ptr_object0 -> mask_color[x][y];
                mask_color1[x][y] = ptr_object1 -> mask_color[x][y];
            }    
    }
    
    for(uint8_t y=0; y<y_grid_size; y++){
        for(uint8_t x=0; x<x_grid_size; x++){
            if(mask_0[x][y] && mask_1[x][y]){
                if(flag == 0){
                    flag = 1;
                }
                mask_union[x][y] = 1;
            }else{
                mask_union[x][y] = 0;
            }
        }
    }

    if(flag == 1){
        for(uint8_t y=0; y<y_grid_size; y++){
            for(uint8_t x=0; x<x_grid_size; x++){
                if(mask_0[x][y] != mask_union[x][y]){
                    grid[x][y] = background[x][y];
                }
            }    
        }
        
        
        for(uint8_t y=0; y<y_grid_size; y++){
            for(uint8_t x=0; x<x_grid_size; x++){
                if(mask_1[x][y] != mask_union[x][y]){
                    grid[x][y] = mask_color1[x-x0][y-y0+1];
                }
            }    
        }
        
    }
}

