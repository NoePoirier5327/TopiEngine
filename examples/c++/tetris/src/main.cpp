#include <topi/topi.hpp>
#include "game/game.hpp"
#include "scoreboard/scoreboard.hpp"

enum class GameScreen {
  home,
  game,
  score
};

int main() {
  topi::TopiEngine app = topi::TopiEngine("Tetris", 640, 640);

  GameScreen current_screen = GameScreen::game;
  Scoreboard scoreboard = Scoreboard("./res/scoreboard.txt");
  Game game;

  app.setup([]() {});

  app.update([&game, &scoreboard, &current_screen](double dt) {
    // On a selectionné le fait de jouer et on peut jouer.
    if (!game.game_is_over() && current_screen == GameScreen::game) {
      game.handle_inputs();
      game.update();
    }

    // On a perdu et est sur l'écran avec le tableau des scores.
    if (game.game_is_over()) {
      current_screen = GameScreen::score;
      scoreboard.set_edit_mode();
      scoreboard.set_score_to_add(game.get_score());
    }

    // Si on est sur l'écran du score,
    // alors, on lance sa logique.
    if (current_screen == GameScreen::score) scoreboard.update();
  });

  app.display([&game, &scoreboard, &current_screen](topi::render::RenderManager *renderer) {
    if (current_screen == GameScreen::game) game.display(renderer);
    if (current_screen == GameScreen::score) scoreboard.display(renderer);
  });

  app.run();
}
