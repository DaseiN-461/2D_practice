#include <Arduino.h>
#include <TFT_eSPI.h>

#define pixel_size 10

#define x_size 8
#define y_size 8

#define x_grid_size 64
#define y_grid_size 64

TFT_eSPI tft = TFT_eSPI();


uint32_t grid[x_grid_size][y_grid_size];

uint8_t pos1[2] = {1,2};
uint8_t pos2[2] = {10,10};

uint32_t mask[8][8] = {
                        {0x07FF,0x07FF,0x07FF,0x07FF,0x07FF,0x07FF,0x07FF,0x07FF},
                        {0x07FF,0x07FF,0xFE19,0xFE19,0xFE19,0xFE19,0x07FF,0x07FF},
                        {0x07FF,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0x07FF},
                        {0xFE19,0xFE19,0xFE19,0x0000,0xFE19,0x0000,0xFE19,0xFE19},
                        {0xFE19,0xFE19,0xFE19,0x0000,0xFE19,0x0000,0xFE19,0xFE19},
                        {0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19},
                        {0x07FF,0xF81F,0xFE19,0xFE19,0xFE19,0xFE19,0xF81F,0x07FF},
                        {0x07E0,0xF81F,0xF81F,0xF81F,0x07E0,0xF81F,0xF81F,0x07E0}
                      };


typedef struct{
    uint32_t mask[x_size][y_size];
    uint8_t pos[2];
}object2D;

object2D myObject1 = {
    .mask = {},
    .pos = {}
};

object2D myObject2 = {
    .mask = {},
    .pos = {}
};

void generate_grid();
void generate_struct(object2D *ptr_object ,uint8_t pos[2], uint32_t mask[x_size][y_size]);
void object2grid(object2D *ptr_object);
void print_grid();


void tft_print_grid(){
  uint8_t h = pixel_size;
  for(uint8_t y=0; y<y_grid_size; y++){
    for(uint8_t x=0; x<x_grid_size; x++){
      tft.fillRect(x*h, y*h, h, h, grid[x][y]);
    }
  }
}

void setup() {
  tft.begin();
  tft.fillScreen(TFT_BLACK);

  generate_grid();

  generate_struct(&myObject1,pos1,mask);
  generate_struct(&myObject2,pos2,mask);

  object2grid(&myObject1);
  object2grid(&myObject2);

  tft_print_grid();
}

void loop() {
  // put your main code here, to run repeatedly:
}



void generate_grid(){
    for(uint8_t y=0; y<x_grid_size; y++){
        for(uint8_t x=0; x<x_grid_size; x++){
            grid[x][y] = 0x0000;
        }    
    }
}

void generate_struct(object2D *ptr_object ,uint8_t pos[2], uint32_t mask[x_size][y_size]){
    
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
            printf(" %04X ", grid[x][y]);
        }
        printf("\r\n");
    }
}