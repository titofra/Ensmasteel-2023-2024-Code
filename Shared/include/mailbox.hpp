/**
 * @brief Simple generic non-blocking mailbox
 * @brief Mailbox can stores values, wich can be retrieve at any moment
 */

#ifndef MAILBOX_HPP
#define MAILBOX_HPP

#ifdef USE_ARDUINO_STD_VECTOR
    #include "arduino_std_vector.hpp"
#else
    #include <vector>   // we are using teensy, where vector's library is available
#endif


/* SPECIFICATION */

template <typename T>
class Mailbox {
    public:
        /**
         * @brief Constructor of the mailbox
         * @param int N_max, Maximum number of elements in the mailbox, 0 for unlimited
         * @param bool overwrite, Should we replace elements when we want to insert a new element in a full mailbox? If true, first element is removed, else the new element is not accepted (Note: useless if N_max = 0)
         */
        Mailbox (int N_max, bool overwrite = true);

        /**
         * @brief Add a new element to the mailbox
         * @param void* mail, The element
         * @return true if the element has been added, else false
         */
        bool send (T mail);

        /**
         * @brief Retrieve the first element
         * @param void** mail, The first element if the mail box is not empty
         * @return bool, true if there is an element, false if not
         */
        bool retrieve (T *mail);

        /**
         * @bried Get the number of elements
         * @return The number of elements
         */
        int getNbMail ();
    private:
        std::vector<T> box;
        int N_max;
        bool overwrite;
};


/* IMPLEMENTATION */

template <typename T>
Mailbox<T>::Mailbox (int N_max, bool overwrite): 
    N_max (N_max),
    overwrite (overwrite) {
}

template <typename T>
bool Mailbox<T>::send (T mail) {
    if ((int) box.size () < N_max || N_max == 0) {
        // The box is not full, let's add the mail
        box.push_back (mail);
    } else {
        if (overwrite) {
            // The box is full, let's remove the first mail and add the new one
            for (int i = 0; i < (int) box.size () - 1; i++) {
                box [i] = box [i + 1];
            }
            box.back () = mail;
        } else {
            // The mail cannot be stored
            return false;
        }
    }
    return true;
}

template <typename T>
bool Mailbox<T>::retrieve (T *mail) {
    if (box.size () > 0) {
        // There is at least one mail, let's remove it
        *mail = box [0];
        for (int i = 0; i < (int) box.size () - 1; i++) {
            box [i] = box [i + 1];
        }
        box.pop_back ();
        return true; // The mail is out of the box
    } else {
        // There is no mail
        return false;
    }
}

template <typename T>
int Mailbox<T>::getNbMail () {
    return (int) box.size ();
}

#endif  // MAILBOX_HPP