//  SPDX-FileCopyrightText: 2023 Andrei Belov <belovsmail@gmail.com>
//  SPDX-License-Identifier: GPL-3.0-or-later

#include "game.h"

handful_t	*set_green(handful_t *this, int num)
{
	this->green = num;
	return (this);
}

handful_t	*set_blue(handful_t *this, int num)
{
	this->blue = num;
	return (this);
}

handful_t	*set_red(handful_t *this, int num)
{
	this->red = num;
	return (this);
}