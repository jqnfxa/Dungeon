#pragma once

#include <typeindex>
#include <SFML/Graphics.hpp>
#include "../Interface/Interface.hpp"
#include "Game/State/GameState.hpp"
#include "RenderSlave.hpp"
#include "Input/SFML/SfmlInput.hpp"

class SfmlRenderer : public Renderer {
  sf::RenderWindow window_;
  SfmlInput &input_;

  sf::Image icon_;
  sf::Font font_;
  std::vector<sf::Texture> textures_;
  std::vector<RenderSlave *> slaves_;
  std::unordered_map<std::type_index, int32_t> suitable_for_state_;

  void load_data();
  void destroy();
  void init_slaves();
 public:
  explicit SfmlRenderer(SfmlInput &input);
  ~SfmlRenderer() override;
  void render(const GameEngine &game) override;
  Command *retrieve_input(GameState *game_state);
};
