#include <cstdint>
#include <topi/topi.hpp>

using namespace topi;
using namespace topi::type;
using namespace topi::toolkit;

const size_t WINDOW_WIDTH = 1000;
const size_t WINDOW_HEIGHT = 1000;

const size_t NB_BALL = 20;
const int MAX_SPEED = 500;
const int MIN_SPEED = -500;

const double BALL_RADIUS = 30;

int main() {
  TopiEngine app = TopiEngine("Example - Bouncing shapes", WINDOW_WIDTH, WINDOW_HEIGHT);

  vector::Vector2d balls_speed[NB_BALL];
  vector::Vector2d balls_pos[NB_BALL];
  color::RGBAColor balls_color[NB_BALL];

  app.setup([&balls_pos, &balls_speed, &balls_color]() {
    // On initialise les balles à des positions aléatoires,
    // des vecteurs vitesses aléatoires et des couleurs aléatoires.
    for (size_t i = 0; i < NB_BALL; ++i) {
      int speed = random::randrange(MIN_SPEED, MAX_SPEED);
      balls_speed[i] = vector::Vector2d(speed, speed);

      balls_pos[i] = vector::Vector2d(
        static_cast<double>(random::randrange(BALL_RADIUS, WINDOW_WIDTH - BALL_RADIUS)),
        static_cast<double>(random::randrange(BALL_RADIUS, WINDOW_HEIGHT - BALL_RADIUS))
      );

      balls_color[i] = color::RGBAColor {
        static_cast<uint8_t>(random::randrange(0, 255)),
        static_cast<uint8_t>(random::randrange(0, 255)),
        static_cast<uint8_t>(random::randrange(0, 255)),
        255
      };
    }
  });

  app.update([&balls_pos, &balls_speed](double dt) {
    for (size_t i = 0; i < NB_BALL; ++i) {
      balls_pos[i].x += balls_speed[i].x * dt;
      balls_pos[i].y += balls_speed[i].y * dt;

      if (balls_pos[i].x < BALL_RADIUS || balls_pos[i].x > WINDOW_WIDTH - BALL_RADIUS)
        balls_speed[i].x *= -1;
    
      if (balls_pos[i].y < BALL_RADIUS || balls_pos[i].y > WINDOW_HEIGHT - BALL_RADIUS)
        balls_speed[i].y *= -1;
    }
  });

  app.display([&balls_pos, &balls_color](render::RenderManager *renderer) {
    for (size_t i = 0; i < NB_BALL; ++i) {
      renderer->set_draw_color(balls_color[i]);
      renderer->draw_colored_filled_circle(static_cast<int>(balls_pos[i].x), static_cast<int>(balls_pos[i].y), BALL_RADIUS);
    }
  });

  app.run();

  return 0;
}
