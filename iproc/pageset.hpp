#ifndef PAGESET_H
#define PAGESET_H

#include <cstdint>


namespace iproc{

typedef struct Pageset{

    uint_least64_t address_from = 0;
    uint_least64_t address_to = 0;

    /* if we need we can utize other properties present in map/smaps files*/

    //    std::string Flags,
    //                Offset,
    //                Device,
    //                Inode,
    //                Path;
    //
    //    uint32_t    Size = 0,
    //                Rss = 0,
    //                Pss = 0,
    //                Shared_Clean = 0,
    //                Shared_Dirty = 0,
    //                Private_Clean = 0,
    //                Private_Dirty = 0,
    //                Referenced = 0,
    //                Anonymous = 0,
    //                AnonHugePages = 0,
    //                Swap = 0,
    //                KernelPageSize = 0,
    //                MMUPAgeSize = 0,
    //                Locked = 0;
    //

} pageset;

}
#endif // PAGESET_H
