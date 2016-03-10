#include <iostream>
#include <uuid/uuid.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <cstring>

#define PDI_MAGIC_METADATA 0x7E20

#define res (64 - (sizeof(short)*2 + sizeof(uuid_t)))

struct header {
    header (uint16_t mag, uint16_t ver)
        : magic(mag), version(ver)
    {
        uuid_generate (uuid);
    }

    header ()
    {
    }
    
    uint16_t magic;
    uint16_t version;
    char reserved[res];
    uuid_t uuid;
};

int main(void)
{
    FILE *fp = fopen("/usr/pic1/sandbox/abc/cube.abc", "r");
    header h;
    std::cout << "Size is: " << sizeof(header) << std::endl;
    fread (&h, sizeof(header), 1, fp);
    if (uuid_is_null(h.uuid)) {
        std::cout << "UUID is null" << std::endl;
    } else {
        char buf[37];
        uuid_unparse(h.uuid, buf);
        std::cout << "UUid is " << buf << std::endl;
    }

    std::cout << "----- boost --------------------" << std::endl;
    boost::uuids::uuid u;
    ::memcpy(&u, h.uuid, 16);

    for (auto i: u) {
        std::cout << i << std::endl;
    }

    std::cout << "uint16_t: " << sizeof(uint16_t) << std::endl;
    std::cout << "uuid_t: " << sizeof(uuid_t) << std::endl;
    std::cout << "Res: " << res << std::endl;
    
    std::cout << "Size: " << u.size() << std::endl;
    std::cout << "Variant: " << u.variant() << std::endl;
    std::cout << "Version: " << u.version() << std::endl;
    std::cout << u << std::endl;
    std::cout << "Hello uuid" << std::endl;
}


