#ifndef KEYBOARD
#define KEYBOARD

#define RELEASED 0x80

enum SPECIAL_KEYS
{
	None,
	ESC,
	Backspace,
	Delete,
	Enter
};

typedef struct 
{
	unsigned char alt : 1;
	unsigned char strg : 1;
	unsigned char shift : 1;
	unsigned char capslock : 1;
	unsigned char altgr : 1;
	unsigned char strg_right : 1;
	unsigned char shift_right : 1;
} modifiers_t;

typedef void (*key_event)(char, enum SPECIAL_KEYS, modifiers_t*);

unsigned char keyboard_state;

void init_keyboard();

int register_key_pressed_callback(key_event event);
void delete_key_pressed_callback(int index);

#endif