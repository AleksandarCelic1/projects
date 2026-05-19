#include "constants.hpp"

std::map<std::pair<SDL_Keycode, bool>, char> SDL_KEYS =
{
  // Letters
  {{SDLK_a, false}, 'a'}, {{SDLK_a, true}, 'A'},
  {{SDLK_b, false}, 'b'}, {{SDLK_b, true}, 'B'},
  {{SDLK_c, false}, 'c'}, {{SDLK_c, true}, 'C'},
  {{SDLK_d, false}, 'd'}, {{SDLK_d, true}, 'D'},
  {{SDLK_e, false}, 'e'}, {{SDLK_e, true}, 'E'},
  {{SDLK_f, false}, 'f'}, {{SDLK_f, true}, 'F'},
  {{SDLK_g, false}, 'g'}, {{SDLK_g, true}, 'G'},
  {{SDLK_h, false}, 'h'}, {{SDLK_h, true}, 'H'},
  {{SDLK_i, false}, 'i'}, {{SDLK_i, true}, 'I'},
  {{SDLK_j, false}, 'j'}, {{SDLK_j, true}, 'J'},
  {{SDLK_k, false}, 'k'}, {{SDLK_k, true}, 'K'},
  {{SDLK_l, false}, 'l'}, {{SDLK_l, true}, 'L'},
  {{SDLK_m, false}, 'm'}, {{SDLK_m, true}, 'M'},
  {{SDLK_n, false}, 'n'}, {{SDLK_n, true}, 'N'},
  {{SDLK_o, false}, 'o'}, {{SDLK_o, true}, 'O'},
  {{SDLK_p, false}, 'p'}, {{SDLK_p, true}, 'P'},
  {{SDLK_q, false}, 'q'}, {{SDLK_q, true}, 'Q'},
  {{SDLK_r, false}, 'r'}, {{SDLK_r, true}, 'R'},
  {{SDLK_s, false}, 's'}, {{SDLK_s, true}, 'S'},
  {{SDLK_t, false}, 't'}, {{SDLK_t, true}, 'T'},
  {{SDLK_u, false}, 'u'}, {{SDLK_u, true}, 'U'},
  {{SDLK_v, false}, 'v'}, {{SDLK_v, true}, 'V'},
  {{SDLK_w, false}, 'w'}, {{SDLK_w, true}, 'W'},
  {{SDLK_x, false}, 'x'}, {{SDLK_x, true}, 'X'},
  {{SDLK_y, false}, 'y'}, {{SDLK_y, true}, 'Y'},
  {{SDLK_z, false}, 'z'}, {{SDLK_z, true}, 'Z'},

  // Numbers row
  {{SDLK_0, false}, '0'}, {{SDLK_0, true}, ')'},
  {{SDLK_1, false}, '1'}, {{SDLK_1, true}, '!'},
  {{SDLK_2, false}, '2'}, {{SDLK_2, true}, '@'},
  {{SDLK_3, false}, '3'}, {{SDLK_3, true}, '#'},
  {{SDLK_4, false}, '4'}, {{SDLK_4, true}, '$'},
  {{SDLK_5, false}, '5'}, {{SDLK_5, true}, '%'},
  {{SDLK_6, false}, '6'}, {{SDLK_6, true}, '^'},
  {{SDLK_7, false}, '7'}, {{SDLK_7, true}, '&'},
  {{SDLK_8, false}, '8'}, {{SDLK_8, true}, '*'},
  {{SDLK_9, false}, '9'}, {{SDLK_9, true}, '('},

  // Space
  {{SDLK_SPACE, false}, ' '}, {{SDLK_SPACE, true}, ' '},

  // Special characters
  {{SDLK_BACKSPACE, false}, '\b'},   {{SDLK_BACKSPACE, true}, '\b'},
  {{SDLK_MINUS, false}, '-'},        {{SDLK_MINUS, true}, '_'},
  {{SDLK_EQUALS, false}, '='},       {{SDLK_EQUALS, true}, '+'},
  {{SDLK_LEFTBRACKET, false}, '['},  {{SDLK_LEFTBRACKET, true}, '{'},
  {{SDLK_RIGHTBRACKET, false}, ']'}, {{SDLK_RIGHTBRACKET, true}, '}'},
  {{SDLK_BACKSLASH, false}, '\\'},   {{SDLK_BACKSLASH, true}, '|'},
  {{SDLK_SEMICOLON, false}, ';'},    {{SDLK_SEMICOLON, true}, ':'},
  {{SDLK_QUOTE, false}, '\''},       {{SDLK_QUOTE, true}, '"'},
  {{SDLK_COMMA, false}, ','},        {{SDLK_COMMA, true}, '<'},
  {{SDLK_PERIOD, false}, '.'},       {{SDLK_PERIOD, true}, '>'},
  {{SDLK_SLASH, false}, '/'},        {{SDLK_SLASH, true}, '?'},
  {{SDLK_BACKQUOTE, false}, '`'},    {{SDLK_BACKQUOTE, true}, '~'},

  // Enter
  {{SDLK_RETURN, false}, '\n'},      {{SDLK_RETURN, true}, '\n'}
};