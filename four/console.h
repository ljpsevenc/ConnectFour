#pragma once
#include "Windows.h"
#include <string>
#include <iostream>

/**************************************************************\
 *                                                             *
 *    Change all the members of class Console to static,       *
 *                                                             *
 *     since there is really no need to instantiate it,        *
 *                                                             *
 *     and this makes it easier to call its functions.         *
 *                                                             *
 \*************************************************************/

enum color
{
	default_color, red, yellow, green, cyan, blue, magenta, white
};

class Console
{
private:
	static HANDLE hScreenBuffer;
	static CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	static void error_exit(const std::string& s);
public:
	// Change the constructor to init function.
	// No instantiating, no constructing.
	static void init(void);
	// Change the deconstructor to deinit function.
	// No instantiating, no deconstructing.
	static void deinit(void);
	static void set_title(const std::string& s); // change le titre de la barre de la fen�tre de la Console
	static void set_dimensions(unsigned int width, unsigned int height); // change les dimensions de la Console
	static void set_cursor_position(const COORD& p);
	static void set_cursor_color(color c); // change la couleur du curseur
	static void clear(); // efface tous les caract�res � l'�cran 
};