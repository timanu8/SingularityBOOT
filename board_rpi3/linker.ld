MEMORY
{
    ram : ORIGIN = 0x00000000, LENGTH = 0x3F000000
}

SECTIONS
{
    ENTRY(_start)

    .text :
    {
        __code_start__ = .;
        *(.text*)
        __code_end__ = .;
    } > ram

    .bss  :
    {
        __bss_start__ = .;
        *(.bss*)
        __bss_end__ = .;
    } > ram

	.cores_park (NOLOAD) :
	{
		/* Align at 16 byte to space the addresses */
		. = ALIGN(16);
		__core_1_park_addr__ = . ;
		. += 16;
		__core_2_park_addr__ = . ;
		. += 16;
		__core_3_park_addr__ = . ;
	} > ram

	.stack (NOLOAD) :
	{
		. = ALIGN(0x1000);
		. += 0x1000;
		__stack_pointer__ = .;
	} > ram

}
