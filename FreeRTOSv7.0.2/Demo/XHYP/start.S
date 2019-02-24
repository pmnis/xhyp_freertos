/*
 * start.S
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

	.text
.globl _start
_start:
	/* setup stack	*/
	ldr sp, =__stack_end__

	/* Setup initial call frame */
	mov lr, #4
	mov r12, sp
	stmfd sp!, {r11-r12, lr-pc}
	sub r11, r12, #0x00000004

	/* Jump to main entry point */
	mov	r0, #0
	bl	main


do_hang:
        b      do_hang
