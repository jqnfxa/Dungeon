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

  static constexpr int32_t screen_width_ = 1366;
  static constexpr int32_t screen_height_ = 768;
  const std::string root = "../../resources/";
  const std::string icon_path = root + "icon.png";
  const std::string font_path = root + "arial.ttf";
  const std::string main_menu_path = root + "assets/main_theme.png";
  const std::string play_menu_path = root + "assets/play_menu.png";

  sf::Image icon_;
  sf::Font font_;
  std::vector<sf::Texture> textures_;
  std::vector<RenderSlave *> slaves_;
  std::unordered_map<std::type_index, int32_t> suitable_for_state_;

  sf::Image load_image(const std::string &path);
  sf::Font load_font(const std::string &path);
  sf::Texture load_texture(const std::string &path);
  void load_data();
  void destroy();
 public:
  explicit SfmlRenderer(SfmlInput &input);
  ~SfmlRenderer() override;
  void render(const GameEngine &game) override;
  Command *retrieve_input(GameState *game_state);
};
