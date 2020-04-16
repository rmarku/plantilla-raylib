
#include <iostream>

#include <raylib.h>

#include "clases/Nave.h"
#include "clases/Mapa.h"

#define PHYSAC_NO_THREADS
#define PHYSAC_IMPLEMENTATION
#include <physac.h>

#if defined(PLATFORM_WEB) // Para crear HTML5
#include <emscripten/emscripten.h>
#endif
const int screenWidth = 800;
const int screenHeight = 450;

// Variables Globales
Music music;
Nave *player;
Mapa *mapa;

Camera2D camera = {0};

static void UpdateDrawFrame(void);          // Función dedicada a operar cada frame

int main() {
    // Inicialización de la ventana
    InitWindow(screenWidth, screenHeight, "raylib template - advance game");
    InitAudioDevice();              // Initialize audio device

    /// Ejemplo de utilización de audio.
    music = LoadMusicStream("resources/Cyberpunk Moonlight Sonata.mp3");

    PlayMusicStream(music);
    mapa = new Mapa("resources/mapa/mapa1.json");

    player = new Nave("resources/ship.png", mapa->player_init_pos);

    InitPhysics();
    PhysicsBody floor = CreatePhysicsBodyRectangle((Vector2) {screenWidth / 2, screenHeight}, 500, 100, 10);
    floor->enabled = false; // Disable body state to convert it to static (no dynamics, but collisions)
    PhysicsBody playerBody = CreatePhysicsBodyRectangle(player->getNavePos(), 45, 30, 10);

    // Configuro la Cámara
    camera.target = {player->getNavePos().x, player->getNavePos().y - 110}; // Número Mágico 110.
    camera.offset = (Vector2) {screenWidth / 2, screenHeight / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;


#if defined(PLATFORM_WEB)  // Para versión Web.
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    // Main loop
    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }
#endif


    // Descargar todos los resources cargados

    UnloadMusicStream(music);   // Descargo la musica de RAM
    CloseAudioDevice();         // Cierro el dispositivo de Audio
    CloseWindow();              // Cierro la ventana
    return 0;
}


/**
 *  Función dedicada a dibujar cada frame. Acá adentro se debe poner la logica necesaria para representar un nuevo frame
 *  del juego.
 */
static void UpdateDrawFrame(void) {

    // siempre hay que reproducir la musica que esta actualmente
    UpdateMusicStream(music);

    RunPhysicsStep();
    
    // Verifico Entradas de eventos.
    if (IsKeyDown(KEY_RIGHT)) {
        player->move_x(4);
        if (player->getNavePos().x > camera.target.x + 200)
            camera.target.x = player->getNavePos().x - 200;
    }
    if (IsKeyDown(KEY_LEFT)) {
        player->move_x(-4);
        if (player->getNavePos().x < camera.target.x - 200)
            camera.target.x = player->getNavePos().x + 200;
    }
    if (IsKeyDown(KEY_UP)) {
        // Saltar??
    }
    if (IsKeyDown(KEY_DOWN)) {
        // Nada
    }

    // Comienzo a dibujar
    BeginDrawing();


    BeginMode2D(camera);
    {
        // Dibujo todos los elementos del juego.
        mapa->dibujar();
        player->draw();
    }
    EndMode2D();
    DrawText("Inicio", 20, 20, 40, LIGHTGRAY);

    // Finalizo el dibujado
    EndDrawing();
}