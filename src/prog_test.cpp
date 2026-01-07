#include "../src/SDL3/SDL.h"
#include "../src/SDL3/SDL_main.h"

//structure pour stocker l'etat de l'application
struct AppState {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    int frame_count = 0;
};

//intitialisation appelle a chaque fois au demarrage
SDL_AppResult SDL_APPInit (void** appstate, int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Erreur de SDL_Init: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    //creation d'un nouvel etat de l'application
    AppState* state = new AppState;
    *appstate = state;

    //creation de la fentre
    state->window = SDL_CreateWindow("Programme de test de la SDL3 moderne👨‍🏫", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!state->window) {
        SDL_Log("Erreur de creation de la fenetre: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    //creation du noteur de rendu
    state->renderer = SDL_CreateRenderer(state->window, nullptr);
    if (!state->renderer) {
        SDL_Log("Erreur de creation du moteur de rendu: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_Log("APP initialisée! 👍");
    return SDL_APP_CONTINUE;
}
//boucle principale
SDL_AppResult SDL_APPIterate(void* appstate) {
    AppState* state = static_cast<AppState*> (appstate);

    //gestion des evenements
    SDL_Event event;
    while (SDL_PollEvent (&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            return SDL_APP_CONTINUE; // se ternmine proprement
        }
    }
    state->frame_count++;
    Uint8 r = static_cast<Uint8>((SDL_sin(state->frame_count * 0.01) +1));
    Uint8 g = static_cast<Uint8>((SDL_sin(state->frame_count * 0.02) +1));
    Uint8 b = static_cast<Uint8>((SDL_sin(state->frame_count * 0.03) +1));

    SDL_SetRenderDrawColor(state->renderer, r, g, b, 255);
    SDL_RenderClear(state->renderer);
    SDL_RenderPresent(state->renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appState) {
    AppState* state = static_cast<AppState*>(appState);
    if (state) {
        if (state->renderer) SDL_DestroyRenderer(state->renderer);
        if (state->window) SDL_DestroyWindow(state->window);
        delete state;
    }
    SDL_Quit();
    SDL_Log("Au revoir !!😎");
}