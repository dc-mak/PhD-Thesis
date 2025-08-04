[[cerb::byte]] typedef unsigned char byte;

int main() {
    byte y = 'a';
    return 0;
}

// return code: 1
// bytes/byte_is_not_char.c:4:14: error: constraint violation:
// initializing 'byte' with an expression of incompatible type 'signed int'
//     byte y = 'a';
//              ^~~
