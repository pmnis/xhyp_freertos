/*
 * context.h
 *
 * context definitions
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
#ifndef __CONTEXT_H
#define __CONTEXT_H

/*
** Do not change the context structure
*/
struct shadow {
	unsigned long	sp;
	unsigned long	lr;
	unsigned long	pc;
	unsigned long	spsr;
};

#define MAX_USUAL_REGS	13
struct pt_regs {
	unsigned long regs[MAX_USUAL_REGS];
};

struct context {
	struct pt_regs	regs;	/* r0 - r12 : 0 - 52 		*/
	struct shadow	sregs;	/* r13 - r15 + spsr: 52 - 64	*/
	unsigned long	cpsr;	/* cpsr: 68			*/
	unsigned long	far;	/* 72				*/
	unsigned long	dfsr;
	unsigned long	ifsr;
	unsigned long	domain;
};

extern struct context saved_regs;
extern void show_ctx(struct context *);

#endif
