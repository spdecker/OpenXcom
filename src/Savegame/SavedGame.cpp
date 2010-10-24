/*
 * Copyright 2010 Daniel Albano
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "SavedGame.h"
#include "../Engine/RNG.h"
#include "GameTime.h"
#include "Country.h"
#include "Base.h"
#include "Region.h"
#include "Ufo.h"
#include "Waypoint.h"

/**
 * Initializes a brand new saved game according to the specified difficulty.
 * @param diff Game difficulty.
 */
SavedGame::SavedGame(GameDifficulty diff) : _diff(diff), _funds(0), _countries(), _regions(), _bases(), _ufos(), _craftId(), _waypoints(), _ufoId(1), _waypointId(1)
{
	_time = new GameTime(6, 1, 1, 1999, 12, 0, 0);
	RNG::init();
}

/** 
 * Deletes the game content from memory.
 */
SavedGame::~SavedGame()
{
	for (std::map<LangString, Country*>::iterator i = _countries.begin(); i != _countries.end(); i++)
	{
		delete i->second;
	}
	for (std::map<LangString, Region*>::iterator i = _regions.begin(); i != _regions.end(); i++)
	{
		delete i->second;
	}
	for (std::vector<Base*>::iterator i = _bases.begin(); i != _bases.end(); i++)
	{
		delete *i;
	}
	for (std::vector<Ufo*>::iterator i = _ufos.begin(); i != _ufos.end(); i++)
	{
		delete *i;
	}
	for (std::vector<Waypoint*>::iterator i = _waypoints.begin(); i != _waypoints.end(); i++)
	{
		delete *i;
	}
}

/**
 * Returns the player's current funds.
 * @return Current funds.
 */
int SavedGame::getFunds()
{
	return _funds;
}

/**
 * Changes the player's funds to a new value.
 * @param funds New funds.
 */
void SavedGame::setFunds(int funds)
{
	_funds = funds;
}

/**
 * Gives the player his monthly funds, taking in account
 * all maintenance and profit costs.
 */
void SavedGame::monthlyFunding()
{
	_funds += getCountryFunding() - getBaseMaintenance();
}

/**
 * Returns the current time of the game.
 * @return Pointer to the game time.
 */
GameTime *SavedGame::getTime()
{
	return _time;
}

/**
 * Returns the list of countries in the game world.
 * @return Pointer to country list.
 */
std::map<LangString, Country*> *SavedGame::getCountries()
{
	return &_countries;
}

/**
 * Adds up the monthly funding of all the countries.
 * @return Total funding.
 */
int SavedGame::getCountryFunding()
{
	int total = 0;
	for (std::map<LangString, Country*>::iterator i = _countries.begin(); i != _countries.end(); i++)
	{
		total += i->second->getFunding();
	}
	return total;
}

/**
 * Returns the list of world regions.
 * @return Pointer to region list.
 */
std::map<LangString, Region*> *SavedGame::getRegions()
{
	return &_regions;
}

/**
 * Returns the list of player bases.
 * @return Pointer to base list.
 */
std::vector<Base*> *SavedGame::getBases()
{
	return &_bases;
}

/**
 * Adds up the monthly maintenance of all the bases.
 * @return Total maintenance.
 */
int SavedGame::getBaseMaintenance()
{
	int total = 0;
	for (std::vector<Base*>::iterator i = _bases.begin(); i != _bases.end(); i++)
	{
		total += (*i)->getMonthlyMaintenace();
	}
	return total;
}

/**
 * Returns the latest craft IDs for each type.
 * @return Pointer to ID list.
 */
std::map<LangString, int> *SavedGame::getCraftIds()
{
	return &_craftId;
}

/**
 * Returns the list of alien UFOs.
 * @return Pointer to UFO list.
 */
std::vector<Ufo*> *SavedGame::getUfos()
{
	return &_ufos;
}

/**
 * Returns the latest ufo ID.
 * @return Pointer to ID value.
 */
int *SavedGame::getUfoId()
{
	return &_ufoId;
}

/**
 * Returns the latest waypoint ID.
 * @return Pointer to ID value.
 */
int *SavedGame::getWaypointId()
{
	return &_waypointId;
}

/**
 * Returns the list of craft waypoints.
 * @return Pointer to waypoint list.
 */
std::vector<Waypoint*> *SavedGame::getWaypoints()
{
	return &_waypoints;
}
