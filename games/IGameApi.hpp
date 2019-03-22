/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_IGAMEAPI_HPP
#define ARCADE_IGAMEAPI_HPP

namespace arcade { class Engine; }

class IGameApi {

	public:
	~IGameApi() = default;

	virtual void init() = 0;
	virtual void tick(int) = 0;
	virtual void close() = 0;

};

#endif //ARCADE_IGAMEAPI_HPP
