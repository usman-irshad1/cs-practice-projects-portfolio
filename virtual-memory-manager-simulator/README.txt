================================================================================
              VIRTUAL MEMORY MANAGEMENT SIMULATOR
================================================================================

OVERVIEW
--------
This project simulates the complete virtual-to-physical memory translation
pipeline found in modern operating systems. It models a TLB (Translation
Lookaside Buffer), a Page Table with dirty and valid bits, byte-addressable
RAM, and a hard disk backing store for dirty page write-backs.

The simulator reads a stream of hexadecimal virtual addresses, translates
each one through the TLB -> Page Table -> RAM hierarchy, applies a chosen
replacement policy when physical memory is full, and reports detailed
performance statistics at the end.


ARCHITECTURE
------------
The address translation follows this path:

  Virtual Address
       |
  Split into VPN (Virtual Page Number) + Offset
       |
  +----v-----+
  |   TLB    |  (small fast cache, 4 entries by default)
  +--+----+--+
   Hit|    |Miss
     |    |
  +--v----v--------+
  |   Page Table    |  (full VPN-to-Frame mapping)
  |  FIFO/LRU/OPT  |
  +---------+-------+
            |  Frame number
  +---------v-----------+
  |        RAM          |  (memory[frame][offset])
  +---------+-----------+
            |  Dirty eviction
  +---------v-----------+
  |    HardDisk.txt     |  (backing store)
  +---------------------+


PAGE REPLACEMENT ALGORITHMS
----------------------------
The simulator runs three algorithms sequentially on the same address trace
so their results can be compared directly.

1. FIFO (First-In, First-Out)
   - Evicts the oldest page in memory (the one loaded first).
   - Uses a simple queue (std::list) to track insertion order.
   - Eviction events are logged to FIFO_logging.txt.

2. LRU (Least Recently Used)
   - Evicts the page that has not been accessed for the longest time.
   - Uses an unordered_map paired with a doubly-linked list for O(1) lookups
     and recency updates.
   - On every access the referenced page is moved to the front of the queue.
   - Eviction events are logged to log.txt.

3. OPT (Optimal / Belady's Algorithm)
   - Evicts the page that will not be used for the longest time in the future.
   - Pre-computes a lookahead buffer of all future VPN references before the
     simulation begins.
   - On eviction, scans forward from the current index to find the page with
     the farthest (or no) future use.
   - Serves as the theoretical lower bound and benchmark for FIFO and LRU.
   - Eviction events are logged to OPT_logging.


PROJECT STRUCTURE
-----------------
OS_project.cpp                Main entry point. Runs FIFO, LRU, and OPT
                              in sequence.

Virtual_Memory_manager.h/cpp  Manager class with three methods:
                                Walker()   -> runs FIFO simulation
                                Runner()   -> runs LRU simulation
                                SPRINTER() -> runs OPT simulation

TLB_table.h/cpp               TLB cache with FIFO and LRU insertion,
                              lookup, eviction, and performance metrics
                              (hit rate, EAT calculation).

Page_frame.h/cpp              Page table with all three replacement
                              policies, dirty-bit tracking, disk
                              write-back on eviction, and final shutdown
                              sync (flushes remaining dirty pages).

Ram_memory.h/cpp              Physical RAM modeled as a 2D char array
                              (memory[frame][offset]) with read/write
                              operations. Also defines Page_frame_node
                              with dirty_bit, valid_bit, and frame number.

FileConfiguration.h/cpp       Reads simulation parameters from
                              Parameters.json using jsoncpp. Parses
                              hex addresses from addresses.txt. Provides
                              helper functions for VPN extraction and
                              offset calculation via bitwise operations.

Parameters.json               Configuration file with physical memory
                              size, page size, TLB size, virtual address
                              space size, and RAM latency.

addresses.txt                 Input file containing one hex virtual
                              address per line.


CONFIGURATION
-------------
All simulation parameters are set in Parameters.json:

  physical_size   Total physical memory in bytes.
                  Default: 40960 (40 KB, which gives 10 frames at 4 KB each)

  page_size       Size of each page/frame in bytes.
                  Default: 4096 (4 KB)

  TLB_size        Number of entries in the TLB cache.
                  Default: 4

  virtual_size    Upper bound of the virtual address space.
                  Default: 18446744073709551615 (full 64-bit range)

  latency         RAM access latency in nanoseconds.
                  Default: 10 ns

Changing physical_size or TLB_size will directly affect hit rates and
Effective Access Time, making it easy to study memory pressure effects.


INPUT FORMAT
------------
The file addresses.txt should contain one hexadecimal virtual address per
line, for example:

  0x00003a
  0x000041
  0x000058
  0x0000FF

Every 5th address is treated as a write operation (W). All others are
read operations (R).


PERFORMANCE METRICS
-------------------
After each algorithm completes, the simulator prints:

  Total Requests       Number of address translations processed
  TLB Hit Rate         TLB_hits / total_requests * 100
  RAM Reads            Total page loads from disk into RAM
  RAM Writes           Total write operations within RAM
  Dirty Evictions      Pages written back to disk upon eviction
  Effective Access     Weighted average access time per request
  Time (EAT)

The EAT formula accounts for:
  - TLB lookup cost:         1 ns per request
  - Page table walk penalty: 10 ns per TLB miss
  - RAM read cost:           latency ns per read
  - RAM write cost:          latency * 2 ns per write
  - Disk write-back cost:    1000 ns per dirty eviction


HOW IT WORKS
------------
1. Initialization
   FileConfiguration parses Parameters.json for memory sizes and latency,
   then loads all hex addresses from addresses.txt into a vector.

2. Address Decomposition
   Each virtual address is split into a Virtual Page Number (VPN) and an
   Offset using bit-shifting based on the page size.

3. TLB Lookup
   The VPN is searched in the TLB.
     Hit  -> The physical frame is retrieved directly and the page is
             promoted in the recency queue (for LRU/OPT modes).
     Miss -> Proceed to the Page Table.

4. Page Table Lookup
   The VPN is searched in the page table.
     Found     -> The frame number is returned and the TLB is updated.
     Not Found -> A page fault occurs. If a free frame exists it is
                  allocated. Otherwise eviction occurs using the active
                  replacement policy.

5. Eviction
   When physical memory is full:
     a. The victim page is selected by the active algorithm.
     b. If the victim's dirty bit is set, its frame contents are written
        to HardDisk.txt (simulating a disk write-back).
     c. The victim is removed from both the Page Table and the TLB.
     d. The new page is loaded into the freed frame.

6. Shutdown Sync
   When the Page_table object is destroyed, all remaining dirty pages are
   flushed to HardDisk.txt, simulating a clean system shutdown.


OUTPUT FILES
------------
  log.txt              LRU eviction trace
  FIFO_logging.txt     FIFO eviction trace
  OPT_logging          OPT eviction trace
  HardDisk.txt         Simulated disk with dirty page write-backs

================================================================================
