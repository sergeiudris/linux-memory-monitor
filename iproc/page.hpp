#ifndef PAGE_H
#define PAGE_H

#include <cstdint>


namespace iproc{

typedef struct Page{
    Page(){}
    Page(uint_least64_t& address,uint_least64_t& bits,uint_least64_t& pfn)
        :address(address),bits( bits), pfn(pfn) {}
    bool operator==(const Page& rhs) const{
        return (pfn == rhs.pfn);
    }
    bool operator<(const Page& rhs) const{
        return (pfn < rhs.pfn);
    }

    uint_least64_t address = 0;

    /* 64 bits that describe frame in memory - we get them from pagemap using page address as offset into pagemap */
    uint_least64_t bits = 0;

    /* first 55 bits of those bits contain PAGE FRAME NUMBER */
    uint_least64_t pfn = 0;


} page;

}

#endif // PAGE_H
