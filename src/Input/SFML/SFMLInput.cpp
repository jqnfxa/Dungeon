#include "SFMLInput.hpp"
#include "GUI/Window.hpp"

SFMLInput::SFMLInput(Window &window) : window_(window)
{
}

Command *SFMLInput::command()
{
	return last_command_;
}

void SFMLInput::update()
{
	last_command_ = window_.process_input();
}
