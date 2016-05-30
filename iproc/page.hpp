/****************************************************************************
**
** Copyright (C) 2016 Serge Joggen.
** Contact: serge.joggen@gmail.com
**
** This file is part of Linux Memory Monitor
** Program uses /proc interface to calculate precise RAM usage for a group of processes,
** e.g. browser,database etc., excluding shared and not present(swapped out) memory pages
**
**
** Linux Memory Monitor is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.

** Linux Memory Monitor is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with Linux Memory Monitor.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/
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
