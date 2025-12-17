#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
// � Structure pour stocker l'état de l'app
struct AppState {

 SDL_Window* window = nullptr;
 SDL_Renderer* renderer = nullptr;
 int frame_count = 0;
};
// � Initialisation (appelée une fois au démarrage)
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
 if (!SDL_Init(SDL_INIT_VIDEO)) {
 SDL_Log( "Erreur SDL_Init: %s" , SDL_GetError());
 return SDL_APP_FAILURE;
 }
 // Crée notre état d'application
 AppState* state = new AppState();
 *appstate = state;
 // Crée la fenêtre
 state->window = SDL_CreateWindow(
 "SDL3 Moderne � ",
 800, 600,
 SDL_WINDOW_RESIZABLE
 );
 if (!state->window) {
 SDL_Log( "Erreur fenêtre: %s" , SDL_GetError());
 return SDL_APP_FAILURE;
 }
 // Crée le renderer
 state->renderer = SDL_CreateRenderer(state->window, nullptr);
 if (!state->renderer) {
 SDL_Log( "Erreur renderer: %s" , SDL_GetError());
 return SDL_APP_FAILURE;
 }
 SDL_Log("App initialisée ! ✨ ");
 return SDL_APP_CONTINUE;
}
// � Boucle principale (appelée à chaque frame)
SDL_AppResult SDL_AppIterate(void* appstate) {
 AppState* state = static_cast<AppState*>(appstate);
 // Gestion des événements
 SDL_Event event;
 while (SDL_PollEvent(&event)) {
 if (event.type == SDL_EVENT_QUIT) {
 return SDL_APP_SUCCESS; // Termine proprement
 }
 }
 // Change la couleur en fonction du temps (arc-en-ciel !)
 state->frame_count++;

 Uint8 r = static_cast<Uint8>((SDL_sin(state->frame_count * 0.01f) + 1) *
127);
 Uint8 g = static_cast<Uint8>((SDL_sin(state->frame_count * 0.02f) + 1) *
127);
 Uint8 b = static_cast<Uint8>((SDL_sin(state->frame_count * 0.03f) + 1) *
127);
 SDL_SetRenderDrawColor(state->renderer, r, g, b, 255);
 SDL_RenderClear(state->renderer);
 SDL_RenderPresent(state->renderer);
 return SDL_APP_CONTINUE; // Continue la boucle
}
// � Nettoyage (appelé à la fermeture)
void SDL_AppQuit(void* appstate) {
 AppState* state = static_cast<AppState*>(appstate);
 if (state) {
 if (state->renderer) SDL_DestroyRenderer(state->renderer);
 if (state->window) SDL_DestroyWindow(state->window);
 delete state;
 }
 SDL_Quit();
 SDL_Log("Au revoir ! � ");
}
int SDL_main() {
    return SDL_APP_SUCCESS;
}