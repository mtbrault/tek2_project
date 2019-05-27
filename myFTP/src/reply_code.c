/*
** EPITECH PROJECT, 2018
** myFTP
** File description:
** reply_code table
*/

#include <stdio.h>
#include "myftp.h"

reply_t		reply_table[REPLY_SIZE] =
{
	{120, "Service ready in x minutes.\n"},
	{125, "Data connection already open; transfer starting.\n"},
	{150, "File status okay; about to open data connection.\n"},
	{200, "Command okay.\n"},
	{214, "Help message.\n"},
	{220, "Service ready for new user.\n"},
	{221, "Service closing control connection.\n"},
	{226, "Closing data connection.\n"},
	{227, "Entering Passive Mod ("},
	{230, "User logged in, proceed.\n"},
	{250, "Requested file action okay, completed.\n"},
	{257, "\"PATHNAME\" created.\n"},
	{331, "User name okay, need password.\n"},
	{332, "Need account for login.\n"},
	{425, "Use PORT or PASV first.\n"},
	{430, "Invalid username or password.\n"},
	{451, "Requested action aborted. Local error in processing.\n"},
	{500, "Unknown command.\n"},
	{503, "Login with USER first.\n"},
	{504, "Command not implemented for that parameter.\n"},
	{530, "Please login with USER and PASS.\n"},
	{550, "File or directory doesn't exist.\n"}
};

void	print_msg(int code, int fd)
{
	for (int i = 0; i < REPLY_SIZE; i++) {
		if (reply_table[i].code == code)
			dprintf(fd, "%d %s", reply_table[i].code,
				reply_table[i].message);
	}
}
