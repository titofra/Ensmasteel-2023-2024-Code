#include <mailbox.hpp>

void Mailbox::Mailbox (size_t N_max, bool overwrite): 
    N_max (N_max),
    overwrite (overwrite) {
}

bool Mailbox::send (void* mail) {
    if (box.size () < N_max || N_max == 0) {
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

bool Mailbox::retrieve (void** mail) {
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

size_t Mailbox::getNbMail () {
    return box.size ();
}