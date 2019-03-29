/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_EXCEPTIONS_HPP
#define ARCADE_EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace arcade {

	class EngineException : public std::exception {

		public:
		explicit EngineException(const std::string &_message)
		: _message(_message), _component("Engine")
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

#endif //ARCADE_EXCEPTIONS_HPP
