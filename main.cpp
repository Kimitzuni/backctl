// SPDX-License-Identifier: GPL-2.0

/***
 *    ___.                  __           __  .__   
 *    \_ |__ _____    ____ |  | __ _____/  |_|  |  
 *     | __ \\__  \ _/ ___\|  |/ // ___\   __\  |  
 *     | \_\ \/ __ \\  \___|    <\  \___|  | |  |__
 *     |___  (____  /\___  >__|_ \\___  >__| |____/
 *         \/     \/     \/     \/    \/           
 *
 * backctl - Backlight Controller
 * ============================================================================
 *
 * This was created out of frustration with 'xbacklight', however the attempt to
 * be compatible with xbacklight is here by using the same arguments/flags that
 * it does.
 *
 * ============================================================================
 *
 * main.cpp - backctl main source file
 * Copyright (C) 2024	Rebecca White <rtw@null.net>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include "config.h"

void get_backlight_value(void) {
	return;
}

void backctl_banner(void) {
	std::cout <<
"\033[1;95m___.                  __           __  .__   " << std::endl <<
"\\_ |__ _____    ____ |  | __ _____/  |_|  |  " << std::endl <<
" | __ \\\\__  \\ _/ ___\\|  |/ // ___\\   __\\  |  " << std::endl <<
" | \\_\\ \\/ __ \\\\  \\___|    <\\  \\___|  | |  |__" << std::endl <<
" |___  (____  /\\___  >__|_ \\\\___  >__| |____/" << std::endl <<
"     \\/     \\/     \\/     \\/    \\/           \033[0m" << std::endl << std::endl;
}

void show_usage(void) {
	backctl_banner();

	std::cout <<
"FLAG					DESCRIPTION" << std::endl <<
"==============================================================================" << std::endl << std::endl <<
"-inc <VALUE> | + <VALUE>	 	Increase backlight by VALUE" << std::endl <<
"-dev <VALUE> | - <VALUE>		Decrease backlight by VALUE" << std::endl <<
"-get         | -g                       Get the current backlight value" << std::endl <<
"-get-perc    | -gp			Get the current brightness as a percentage" << std::endl <<
"--help       | -h                       Show this help text" << std::endl <<
"--version    | -v                       Display the current backctl version" << std::endl;
}

void version_info(void) {
	std::cout << "backctl 1.0" << std::endl;
	return;
}

std::string get_brightness_path(void) {
	std::ifstream brightness_file;
	std::string backlight_path = "/sys/class/backlight";

	for (const auto & entry : std::filesystem::directory_iterator(backlight_path))
		return entry.path().string() + "/brightness";  
}

int get_current_brightness(void) {
	char data[4];
	std::ifstream brightness_file;

	brightness_file.open(get_brightness_path());
	brightness_file >> data;;
	brightness_file.close();

	return atoi(data);
}

void set_brightness(int new_brightness) {
	std::ofstream brightness_file;

	brightness_file.open(get_brightness_path());
	brightness_file << new_brightness;
	brightness_file.close();
}

void increase_brightness(int increase_value) {
	int current_brightness = get_current_brightness();
	int new_brightness = current_brightness + increase_value;

	if (new_brightness > MAX_BRIGHTNESS)
		return;
	else
		set_brightness(new_brightness);
}

void decrease_brightness(int decrease_value) {
	int current_brightness = get_current_brightness();
	int new_brightness = current_brightness - decrease_value;

	if (new_brightness < 0)
		new_brightness = 1;
	set_brightness(new_brightness);
}

int backlight_as_percentage(void) {
	int brightness = get_current_brightness();

	return (brightness / 2.55);
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		show_usage();
		return 0;
	}

	else {
		std::string command_flag = argv[1];
		if (command_flag == "-h" || command_flag == "--help") {
			show_usage();
			return 0;
		}

		if (command_flag == "-inc" || command_flag == "+") {
			if (argv[2] == NULL) {
				std::cout << "-inc: requires an argument" << std::endl;
				return 1;
			}

			increase_brightness(atoi(argv[2]));
			return 0;
		}

		if (command_flag == "-dec" || command_flag == "-") {
			if (argv[2] == NULL) {
				std::cout << "-dec: requires an argument" << std::endl;
				return 1;
			}

			decrease_brightness(atoi(argv[2]));
			return 0;
		} 

		if (command_flag == "-g" || command_flag == "-get") {
			int current_brightness = get_current_brightness();
			std::cout << current_brightness << std::endl;
			return 0;
		}

		if (command_flag == "-s" || command_flag == "-set") {
			if (argv[2] == NULL) {
				std::cout << "-set: requires an argument" << std::endl;
				return 1;
			}

			set_brightness(atoi(argv[2]));
			return 0;
		}

		if (command_flag == "-get-perc" || command_flag == "-gp") {
			int brightness =backlight_as_percentage();
			std::cout << brightness << std::endl;
		}
	}
	return 0;
}
