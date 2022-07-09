#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define pixel_size 10

#define x_size 3
#define y_size 3

#define x_grid_size 9
#define y_grid_size 9

uint32_t grid[x_grid_size][y_grid_size];
uint32_t background[x_grid_size][y_grid_size];



uint32_t mask_color[3][3] = {
                        {0xFFFF,0x0030,0xFFFF},
                        {0x0300,0x0030,0x0030},
                        {0xFFFF,0x0030,0xFFFF},
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



void generate_grid();
void generate_object(object2D *ptr_object ,uint8_t pos[2], bool mask_grid[x_grid_size][y_grid_size], uint32_t mask_color[x_size][y_size]);
void object2grid(object2D *ptr_object);
object2D update_object(uint8_t x0, uint8_t y0, uint32_t new_mask_color[x_size][y_size]);
void print_grid();

void update_grid(object2D *ptr_object0,object2D *ptr_object1);
bool mask_union[x_grid_size][y_grid_size];



void generate_grid(){
    for(uint8_t y=0; y<x_grid_size; y++){
        for(uint8_t x=0; x<x_grid_size; x++){
            grid[x][y] = 0xFFFF;
            background[x][y] = 0xFFFF;
        }    
    }
}

void generate_object(object2D *ptr_object ,uint8_t pos[2], bool mask_grid[x_grid_size][y_grid_size], uint32_t mask_color[x_size][y_size]){
    
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

object2D update_object(uint8_t x0, uint8_t y0, uint32_t new_mask_color[x_size][y_size]){
    object2D tempObject = {
        .mask_grid = {},
        .mask_color = {},
        .pos = {}
    };

    tempObject.pos[0] = x0;
    tempObject.pos[1] = y0;

    for(uint8_t y=0; y<y_grid_size; y++){
        for(uint8_t x=0; x<x_grid_size; x++){
            tempObject.mask_grid[x][y] = 0;
        }
    }
    
    for(uint8_t y=0; y<y_size; y++){
        for(uint8_t x=0; x<x_size; x++){
            tempObject.mask_color[x][y] = new_mask_color[x][y];
            if(tempObject.mask_color[x][y] != NULL){
                tempObject.mask_grid[x0+x][y0+y] = 1;
            }
        }
    }
    return tempObject;
}

void print_grid(){
    uint8_t col = 0;
    printf("\r\n");
    for(uint8_t y=0; y<y_grid_size; y++){
        printf("col %d    :",col);
        col++;
        for(uint8_t x=0; x<x_grid_size; x++){
            printf(" %04X ", grid[y][x]);
        }
        printf("\r\n");
    }
}

void update_grid(object2D *ptr_object0,object2D *ptr_object1){
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
                if(mask_1[x][y] != mask_union[x][y]){
                    grid[x][y] = mask_color1[x-x1][y-y1];
                }
                if(mask_union[x][y]){
                    if(grid[x][y] != mask_color1[x-x1][y-y1]){
                        grid[x][y] = mask_color1[x-x1][y-y1];
                    }
                }
            }    
        }
        
        
    }else if (flag == 0){
        for(uint8_t y=0; y<y_grid_size; y++){
            for(uint8_t x=0; x<x_grid_size; x++){
                if(mask_0[x][y] == 1){
                    grid[x][y] = background[x][y];
                }
                if (mask_1[x][y] == 1){
                    grid[x][y] = mask_color1[x-x1][y-y1];
                }
                
            }
        }
    }
}
