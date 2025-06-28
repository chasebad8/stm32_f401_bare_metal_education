#include <stdint.h>

#define SRAM_START                 (0x20000000)  //Memory location for start of SRAM
#define SRAM_SIZE                  (64U * 1024U) // 64 KB  1KB == 1024 bytes
#define SRAM_END                   ((SRAM_START) + (SRAM_SIZE))
#define STACK_POINTER_INIT_ADDRESS (SRAM_END) //Stack pointer starts at the end of SRAM

#define ISR_VECTOR_SIZE_WORDS 114

/* Grab all the variables that were created in the linker script that contain the addresses of the
   different sections start/end locations */
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

void reset_handler(void);
void main(void);

/* This array will be the first 115 words (where 1 word is 32 bits) into the .isr_vector memory.
   Recall the .isr_vector is the first place in memory that will be called. The very first address
   stores the stack pointer init address */
uint32_t isr_vector[ISR_VECTOR_SIZE_WORDS] __attribute__((section(".isr_vector"))) =
{
   STACK_POINTER_INIT_ADDRESS,
   (uint32_t)&reset_handler
};

void reset_handler(void)
{
  // Copy .data from FLASH to SRAM

  /* Grab the size of the .data memory to copy */
  uint32_t data_size  = (uint32_t)&_edata - (uint32_t)&_sdata;

  /* In flash the starting address is the address e_text ended at */
  uint8_t *flash_data = (uint8_t*)&_etext;

  /* In sram the starting address is the start address of sram */
  uint8_t *sram_data  = (uint8_t*)&_sdata;

  /* literally copy data from the flash addr's to sram addr's */
  for (uint32_t reg_index = 0; reg_index < data_size; reg_index++)
  {
    sram_data[reg_index] = flash_data[reg_index];
  }

  /* initialize .bss to all 0 */
  uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
  uint8_t *bss = (uint8_t*) &_sbss;

  for (uint32_t reg_index = 0; reg_index < bss_size; reg_index++)
  {
    bss[reg_index] = 0;
  }

  main();
}
