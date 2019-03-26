/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_EVENTS_HPP
#define ARCADE_EVENTS_HPP

namespace arcade {

	namespace event {
		enum Key {
			A = 'A',
			B = 'B',
			C = 'C',
			D = 'D',
			E = 'E',
			F = 'F',
			G = 'G',
			H = 'H',
			I = 'I',
			J = 'J',
			K = 'K',
			L = 'L',
			M = 'M',
			N = 'N',
			O = 'O',
			P = 'P',
			Q = 'Q',
			R = 'R',
			S = 'S',
			T = 'T',
			U = 'U',
			V = 'V',
			W = 'W',
			X = 'X',
			Y = 'Y',
			Z = 'Z',
			ARROW_DOWN,
			ARROW_UP,
			ARROW_LEFT,
			ARROW_RIGHT,
			ENTER,
			SPACE,
			BACKSPACE,
			ESCAPE,
			UNKNOWN,
		};

		struct event_t {
			Key key;
			int base;
		};

//		typedef struct event_x {
//
//		} event_t;
	}
}

#endif //ARCADE_EVENTS_HPP
