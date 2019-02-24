MEMORY 
{
	ram	: ORIGIN = 0x02100000, LENGTH = 0x00700000
}

__stack_end__ = 0x02800000 - 0x10;

SECTIONS 
{
	. = 0;
	startup : { *(.startup)} >ram

	prog : 
	{
		*(.text)
		*(.rodata)
		*(.rodata*)
		*(.glue_7)
		*(.glue_7t)
		*(.plt)
	} >ram

	__end_of_text__ = .;

	.data : 
	{
		__data_beg__ = .;
		__data_beg_src__ = __end_of_text__;
		*(.data)
		__data_end__ = .;
	} >ram

	.bss : 
	{
		__bss_beg__ = .;
		*(.bss)
	} >ram

	/* Align here to ensure that the .bss section occupies space up to
	_end.  Align after .bss to ensure correct alignment even if the
	.bss section disappears because there are no input sections.  */
	. = ALIGN(32 / 8);
	_end = .;
	_bss_end__ = . ; __bss_end__ = . ; __end__ = . ;
	PROVIDE (end = .);

.note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
/DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*)  *(.note.gnu.build-id) }
}
