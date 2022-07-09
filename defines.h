#define pixel_size 10

#define x_size 8
#define y_size 8

#define x_grid_size 64
#define y_grid_size 64

typedef struct{
    uint32_t mask[x_size][y_size];
    uint8_t pos[2];
    uint8_t walk_state;
}object2D;

uint32_t grid[x_grid_size][y_grid_size];


uint32_t mask0[8][8] = {
                        {0x07FF,0x07FF,0x07FF,0x07FF,0x07FF,0x07FF,0x07FF,0x07FF},
                        {0x07FF,0x07FF,0xFE19,0xFE19,0xFE19,0xFE19,0x07FF,0x07FF},
                        {0x07FF,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0x07FF},
                        {0xFE19,0xFE19,0xFE19,0x0000,0xFE19,0x0000,0xFE19,0xFE19},
                        {0xFE19,0xFE19,0xFE19,0x0000,0xFE19,0x0000,0xFE19,0xFE19},
                        {0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19},
                        {0x07FF,0xF81F,0xFE19,0xFE19,0xFE19,0xFE19,0xF81F,0x07FF},
                        {0x07E0,0xF81F,0xF81F,0xF81F,0x07E0,0xF81F,0xF81F,0x07E0}
                      };

uint32_t mask1[8][8] = {
                        {0x07FF,0x07FF,0x07FF,0x07FF,0x07FF,0x07FF,0x07FF,0x07FF},
                        {0x07FF,0x07FF,0xFE19,0xFE19,0xFE19,0xFE19,0x07FF,0x07FF},
                        {0x07FF,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0x07FF},
                        {0xFE19,0xFE19,0xFE19,0x0000,0xFE19,0x0000,0xFE19,0xFE19},
                        {0xFE19,0xFE19,0xFE19,0x0000,0xFE19,0x0000,0xFE19,0xFE19},
                        {0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19},
                        {0x07FF,0xF81F,0xFE19,0xFE19,0xFE19,0xF81F,0xFE19,0x07FF},
                        {0x07E0,0xF81F,0xF81F,0xF81F,0x07E0,0xF81F,0xF81F,0x07E0}
                      };

uint32_t mask2[8][8] = {
                        {0x07FF,0x07FF,0x07FF,0x07FF,0x07FF,0x07FF,0x07FF,0x07FF},
                        {0x07FF,0x07FF,0xFE19,0xFE19,0xFE19,0xFE19,0x07FF,0x07FF},
                        {0x07FF,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0x07FF},
                        {0xFE19,0xFE19,0xFE19,0x0000,0xFE19,0x0000,0xFE19,0xFE19},
                        {0xFE19,0xFE19,0xFE19,0x0000,0xFE19,0x0000,0xFE19,0xFE19},
                        {0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19},
                        {0x07FF,0xFE19,0xFE19,0xF81F,0xFE19,0xF81F,0xFE19,0x07FF},
                        {0x07E0,0xF81F,0xF81F,0xF81F,0x07E0,0xF81F,0xF81F,0x07E0}
                      };

uint32_t mask3[8][8] = {
                        {0x07FF,0x07FF,0x07FF,0x07FF,0x07FF,0x07FF,0x07FF,0x07FF},
                        {0x07FF,0x07FF,0xFE19,0xFE19,0xFE19,0xFE19,0x07FF,0x07FF},
                        {0x07FF,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0x07FF},
                        {0xFE19,0xFE19,0xFE19,0x0000,0xFE19,0x0000,0xFE19,0xFE19},
                        {0xFE19,0xFE19,0xFE19,0x0000,0xFE19,0x0000,0xFE19,0xFE19},
                        {0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19,0xFE19},
                        {0x07FF,0xFE19,0xFE19,0xF81F,0xFE19,0xFE19,0xF81F,0x07FF},
                        {0x07E0,0xF81F,0xF81F,0xF81F,0x07E0,0xF81F,0xF81F,0x07E0}
                      };

enum{
    state_0,
    state_1,
    state_2,
    state_3
};
uint8_t walk_state = state_0;

void generate_grid();
void generate_struct(object2D *ptr_object ,uint8_t pos[2], uint32_t mask[x_size][y_size]);
void object2grid(object2D *ptr_object);
void print_grid();

void set_mask(object2D *ptr_object, uint32_t mask[x_size][y_size]){
    for(uint8_t y=0; y<x_size; y++){
        for(uint8_t x=0; x<x_size; x++){
            ptr_object->mask[x][y] = mask[x][y];
        }    
    }
}

void caminar(object2D *ptr_object){
    switch (ptr_object->walk_state)
    {
    case state_0:
      set_mask(ptr_object,mask0);
      ptr_object->walk_state++;
      break;
    case state_1:
      set_mask(ptr_object,mask1);
      ptr_object->walk_state++;
      break;
    case state_2:
      set_mask(ptr_object,mask2);
      ptr_object->walk_state++;
      break;
    case state_3:
      set_mask(ptr_object,mask3);
      ptr_object->walk_state = state_0;
      break;

    default:
      set_mask(ptr_object,mask0);
      break;
    }
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