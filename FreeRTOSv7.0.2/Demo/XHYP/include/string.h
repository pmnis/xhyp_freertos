/*
 * string.c
 *
 * Author: Pierre Morel <pmorel@mnis.fr>
 *
 * $LICENSE:
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

int strlen(const char *s);
int strnlen(const char *s, int count);
char *strchr(const char *s, int c);
char *strncpy(char *dest, const char *src, int count);
int strncmp(const char *cs, const char *ct, int count);
int strcmp(const char *cs, const char *ct);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, int count);
extern unsigned long strtoul(const char *cp, char **endp, unsigned int base);
extern long strtol(const char *cp, char **endp, unsigned int base);
unsigned long long strtoull(const char *cp, char **endp, unsigned int base);
long long strtoll(const char *cp, char **endp, unsigned int base);

