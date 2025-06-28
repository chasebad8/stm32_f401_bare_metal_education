MEMORY
{
   /* Location of FLASH memory */
   FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K

   /* Location of SRAM memory */
   SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 96K
}

SECTIONS
{
   /* Location of .isr_vector section  maps to 0x0 of FLASH
      This is where the code is initially called */
   .isr_vector :
   {
      KEEP(*(.isr_vector))
   } > FLASH

   /* Section that contains the actual instructions of our program */
   .text :
   {
      . = ALIGN(4);

      *(.text)
      *(.rodata)

      . = ALIGN(4);

      _etext = .;
   } > FLASH

   /* Data section, initialized data that is copied to SRAM at startup */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;

    *(.data)

    . = ALIGN(4);
    _edata = .;
  } > SRAM AT > FLASH

   /* BSS section, uninitialized data that is zeroed at startup */
  .bss :
  {
    . = ALIGN(4);
    _sbss = .;

    *(.bss)

    . = ALIGN(4);
    _ebss = .;
  } > SRAM
}