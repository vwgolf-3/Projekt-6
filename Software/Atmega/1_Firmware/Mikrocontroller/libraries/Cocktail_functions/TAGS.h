/*
 * RFID.h
 *
 * Created: 25.06.2020 20:45:50
 *  Author: kimsc
 */


#ifndef RFID_H_
#define RFID_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************************************************************/
struct rfid_tag {                                           // Struckt f�r RFID-Tags in der Maschine (wird 12 Mal initialisiert)
    char * cocktail_name;                                   // Pointer auf den Speicher f�r hinterlegten Cocktail
    uint8_t tag_nummer;                                     // Speicher f�r Systemnummer der Tags
    uint8_t tag_ID;                                         // Speicher f�r ID des Tags
    struct rfid_tag * next;                                 // Pointer auf den zurvor eingef�gten Tag
    struct rfid_tag * prev;                                 // Pointer auf das danach eingef�gten Tag
};
typedef struct rfid_tag rfid_tag_t;                         // Typedef f�r Struct rfid_tag_t

rfid_tag_t * aktueller_tag;                                 // Pointer auf aktuelln Tag
rfid_tag_t * head_tag;                                      // Pointer auf zuletzt in die Liste eingef�gten Tag
rfid_tag_t * tail_tag;                                      // Pointer auf erstes in die Liste eingef�gten Tag
/******************************************************************************************************************************/
void RFID_init(void);
rfid_tag_t *insert_tag_at_head(rfid_tag_t **head_tag, rfid_tag_t *tag_to_insert);
rfid_tag_t *create_new_tag(char * cocktail_name, uint8_t tag_nummer, uint8_t tag_ID);

#endif /* RFID_H_ */