#include "stdafx.h"

#include "player.h"

Player::Player() :
	offensive_(true),
	choice_(-1)
{}

Player::Player(bool offsensive) :
	offensive_(offsensive),
	choice_(-1)
{}

void Player::choose(int choice)
{
	choice_ = choice;
}

bool Player::isOffensive() const
{
	return offensive_;
}

int Player::choice() const
{
	return choice_;
}

void Player::move()
{
	choose(-1);
}