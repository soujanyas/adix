#include <sys/idt.h>
#include <string.h>
#include <sys/isr.h>
#include <sys/irq.h>
#include <sys/timer.h>
#include <sys/keyboard.h>

extern void isr0();

/* adapted from Chris Stones, shovelos */

#define MAX_IDT 256

struct idt_t idt[MAX_IDT];

struct idtr_t {
	uint16_t size;
	uint64_t addr;
}__attribute__((packed));

static struct idtr_t idtr = {
	sizeof(idt),
	(uint64_t)idt,
};

void _x86_64_asm_lidt(struct idtr_t* idtr);
void reload_idt() {
    isrs_install();
    irq_install();
    timer_install();
    keyboard_install();

    _x86_64_asm_lidt(&idtr);
}
