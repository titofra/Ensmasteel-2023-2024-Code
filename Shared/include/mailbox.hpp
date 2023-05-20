/**
 * @brief Simple generic non-blocking mailbox
 * @brief Mailbox can stores values, wich can be retrieve at any moment
 */

#ifndef MAILBOX_H
#define MAILBOX_H

#include <cstdint>
#include <cstdbool>
#include <cstdlib>
#include <cstdio>

class Mailbox {
    public:
        /**
         * @brief Constructor of the mailbox
         * @param size_t N_max, Macimum number of elements in the mailbox, 0 for unlimited
         * @param bool overwrite, Should we replace elements when we want to insert a new element in a full mailbox? If true, first element is removed, else the new element is not accepted (Note: useless if N_max = 0)
         */
        Mailbox (size_t N_max, bool overwrite = true);

        /**
         * @brief Add a new element to the mailbox
         * @param void* mail, The element
         * @return true if the element has been added, else false
         */
        bool send (void* mail);

        /**
         * @brief Retrieve the first element
         * @param void** mail, The first element if the mail box is not empty
         * @return bool, true if there is an element, false if not
         */
        bool retrieve (void** mail);

        /**
         * @bried Get the number of elements
         * @return The number of elements
         */
        size_t getNbMail ();
    private:
        std::vector<void*> box;
        size_t N_max;
        bool overwrite;
};

#endif  // MAILBOX_H