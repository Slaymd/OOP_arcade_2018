/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#ifndef UI_EXCEPTIONS_HPP
#define UI_EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace ui {

	class UIException : public std::exception {

		public:
		explicit UIException(const std::string &_message)
		: _message(_message), _component("UILib")
		{}

		const char *what() const noexcept override
		{
			return _message.c_str();
		}

		std::string const &getComponent() const
		{
			return _component;
		}

		private:
		std::string _message;
		std::string _component;

	};

}

#endif //UI_EXCEPTIONS_HPP
