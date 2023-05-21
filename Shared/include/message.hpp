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
    NOTHING,
    HERE,
    FOR,
    THE,
    MOMENT,
    TODO
} esptee_msg_id;

typedef struct {
    esptee_msg_id id;
} msg_esptee;

#endif  // MESSAGE_HPP