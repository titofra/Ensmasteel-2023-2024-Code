#ifndef MESSAGE_HPP
#define MESSAGE_HPP

typedef enum {
    OPEN_CLAWS,
    CLOSE_CLAWS
} ardtee_msg_id;

typedef struct {
    ardtee_msg_id id;
} com_ardtee;

#endif  // MESSAGE_HPP