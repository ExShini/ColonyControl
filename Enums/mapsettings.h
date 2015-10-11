#ifndef MAPSETTINGS_H
#define MAPSETTINGS_H

#define MAP_WIDTH 17
#define MAP_HEIGHT 17

#define CELL_MAP_WIDTH 128
#define CELL_MAP_HEIGHT 128

/*
 * optimization macroses
 * should correlate with CELL_MAP_WIDTH and CELL_MAP_HEIGHT
 */
#define GET_MAP_X(realX) (realX >> 7)
#define GET_MAP_Y(realY) (realY >> 7)
#define GET_REAL_X(mapX) (mapX << 7)
#define GET_REAL_Y(mapY) (mapY << 7)
#define CONVERT_SECTORS_TO_PXL(sec) (sec * CELL_MAP_WIDTH)
#define CONVERT_PXL_TO_SECTORS(pxl) ((float)pxl / CELL_MAP_WIDTH)



#endif // MAPSETTINGS_H
