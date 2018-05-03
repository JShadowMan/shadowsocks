#include <initializer_list>
#include "shadowsocks/ss_selector.h"


// register a socket to selector
void Ss_Selector::registerSocket(SOCKET s, SelectorEvents events) {
    for (auto event : events) {
        switch (event) {
            case SelectorEvent::SE_READABLE:
                _readable.push_back(s); break;
            case SelectorEvent ::SE_WRITABLE:
                _writable.push_back(s); break;
        }
    }
}
