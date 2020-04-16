//
// Created by martin on 7/4/20.
//

#ifndef RAYLIBTEMPLATE_MAPA_H
#define RAYLIBTEMPLATE_MAPA_H


#include <string>
#include <raylib.h>
#include "../libs/tileson.hpp"

class Mapa {
    tson::Map map;
    Texture2D map_tex;
    tson::Tileset *map_tileset;

public:
    Vector2 player_init_pos;

    Mapa(std::string file);

    void dibujar();
};


#endif //RAYLIBTEMPLATE_MAPA_H
