#ifndef MESSAGE_HPP
#define MESSAGE_HPP

typedef enum {
    OPEN_CLAWS,
    CLOSE_CLAWS
} ardtee_msg_id;

typedef struct {
    ardtee_msg_id id;
} msg_ardtee;

typedef enum {
    LCD_PRINT,
    LCD_CLEAR
} esptee_msg_id;

typedef struct {
    esptee_msg_id id;
    char data [32];
} msg_esptee;

#endif  // MESSAGE_HPP