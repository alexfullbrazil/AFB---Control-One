#include <usb_names.h>

#define MIDI_NAME {'A', 'F', 'B', ' ', '-', ' ', 'C', 'o', 'n', 't', 'r', 'o', 'l', ' ', 'O', 'n', 'e'}
#define MIDI_NAME_LEN 17

struct usb_string_descriptor_struct usb_string_product_name = {
    2 + MIDI_NAME_LEN * 2,
    3,
    MIDI_NAME};