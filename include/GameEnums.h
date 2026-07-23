#ifndef GAME_ENUMS_H_
#define GAME_ENUMS_H_

// стан для визначення чи відкривати меню чи гру
enum class GameState { Menu, Playing, WaitingToStart, Pause, Quit };
// стан для визначення який пунк меню було вибрано
enum MenuItem { Start, Quit };

#endif  // GAME_ENUMS_H_